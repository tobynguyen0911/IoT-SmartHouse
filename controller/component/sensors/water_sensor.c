#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "cJSON.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "device_utils.h"
#include <string.h>

const static char *TAG = "water SENSOR";
extern adc_oneshot_unit_handle_t adc1_handle;
extern int adc_setup;

#define STACK_SIZE 2048

extern int local_ids;

cJSON * water_create_state(int current_val)
{
    cJSON *state_root;
	state_root = cJSON_CreateArray();

    cJSON *state_element = cJSON_CreateObject();
    cJSON_AddStringToObject(state_element, "name", "value");
    cJSON_AddStringToObject(state_element, "type", "int");
    cJSON_AddNumberToObject(state_element, "value", (double) current_val);

    cJSON_AddItemToArray(state_root, state_element);

    return state_root;
}


void init_water_sensor(int pins[], device_def_t* device_def)
{
    gpio_reset_pin(pins[0]);

    if (!adc_setup)
    {
        adc_oneshot_unit_init_cfg_t init_config1 = {
            .unit_id = ADC_UNIT_1,
            .ulp_mode = ADC_ULP_MODE_DISABLE,
        };
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
        adc_setup = true;
    }

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, convert_analog_pin(pins[0]), &config));

    // Create device_state JSON object
    device_def->state = (device_state_t * ) malloc(sizeof(device_state_t));
    device_def->state->updated = false;

    device_def->state->device_data = water_create_state(0);

    // Init device lock
    portMUX_TYPE *spinlock = malloc(sizeof(portMUX_TYPE));
    portMUX_INITIALIZE(spinlock);

    device_def->state->dev_spinlock = spinlock;
}

void vTaskwaterSensor(void * pvParameters)
{
    ESP_LOGI(TAG, "Entered Task: water Detector");
    device_def_t * device = (device_def_t *) pvParameters;

    while (1) {
        //ESP_LOGI(TAG, "Spinlock addr = %p", device->state->dev_spinlock);

        //taskENTER_CRITICAL(device->state->dev_spinlock);

        int out_raw;
        adc_oneshot_read(adc1_handle, convert_analog_pin(device->pins[0]), &out_raw);
        ESP_LOGI(TAG, "water output: %d", out_raw);

        device->state->device_data = water_create_state(out_raw);
        device->state->updated = true;

        //taskEXIT_CRITICAL(device->state->dev_spinlock);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void start_water_task(int pins[], device_def_t * device) {
    TaskHandle_t xHandle = NULL;
    xTaskCreate( vTaskwaterSensor, "water Sensor", STACK_SIZE, device, tskIDLE_PRIORITY, &xHandle );
    
    device->dev_task_handle = xHandle;
}

static device_driver_t driver_funcs = {
    .driver_id = 8,
    .n_pins = 1,
    .init_func = &init_water_sensor,
    .start_task = &start_water_task,
    .functions = NULL,
    .num_functions = 0
};

driver_t * gen_water_driver(int pins[])
{
    device_def_t def = {
        .device_local_id = local_ids++,
        .device_id = NULL,
        .pins = pins,
        .dev_task_handle = NULL,
        .state = NULL
    };
    device_def_t * def_ptr = malloc(sizeof(device_def_t));
    memcpy(def_ptr, &def, sizeof(device_def_t));
    
    driver_t driver = {
        .driver = &driver_funcs,
        .definition = def_ptr
    };

    driver_t * out = (driver_t *) malloc(sizeof(driver_t));
    memcpy(out, &driver, sizeof(driver_t));

    return out;
}
