#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "cJSON.h"
#include "device_utils.h"
#include "esp_http_client.h"
#include <string.h>

#define STACK_SIZE 2048

static const char *TAG = "LED";

extern int local_ids;


cJSON * led_create_state(int current_val)
{
    cJSON *state_root;
	state_root = cJSON_CreateArray();

    cJSON *state_element = cJSON_CreateObject();
    cJSON_AddStringToObject(state_element, "name", "on");
    cJSON_AddStringToObject(state_element, "type", "bool");
    cJSON *element;
    if(current_val)
    {
        element = cJSON_CreateTrue();
    } else 
    {
        element = cJSON_CreateFalse();
    }
    cJSON_AddItemToObject(state_element, "value", element);

    cJSON_AddItemToArray(state_root, state_element);

    return state_root;
}

void set_led(device_def_t * device, cJSON * params)
{
    //ESP_LOGI(TAG, "Spinlock addr = %p", device->state->dev_spinlock);

    //taskENTER_CRITICAL(device->state->dev_spinlock);

    // Parse params to get the new state
    int new_led_state = cJSON_IsTrue(params);
    gpio_set_level(device->pins[0], new_led_state);

    cJSON_Delete(device->state->device_data);
    device->state->device_data = led_create_state(new_led_state);

    device->state->updated = true;

    //taskEXIT_CRITICAL(device->state->dev_spinlock);
}

void init_led(int pins[], device_def_t* device_def)
{
    printf("pins: %d", pins[0]);
    gpio_reset_pin(pins[0]);
    gpio_set_direction(pins[0], GPIO_MODE_OUTPUT);

    // Create device_state JSON object
    device_def->state = (device_state_t * ) malloc(sizeof(device_state_t));
    device_def->state->updated = false;

    device_def->state->device_data = led_create_state(false);

    char * cur_state = cJSON_Print(device_def->state->device_data);
    printf("LED STATE: \n%s\n", cur_state);
    free(cur_state);

    // Init device lock
    portMUX_TYPE *spinlock = malloc(sizeof(portMUX_TYPE));
    portMUX_INITIALIZE(spinlock);

    device_def->state->dev_spinlock = spinlock;

    //printf("Spinlock addr = %p", spinlock);
}

void vLedTask(void * pvParameters)
{
    ESP_LOGI(TAG, "Entered Task");;
    device_def_t * device = (device_def_t *) pvParameters;

    ESP_LOGI(TAG, "Pin %d, %d", device->pins[0], device->pins[1]);
    while (1) {
        // This task actually doesn't need to do anything
        //ESP_LOGI(TAG, "Spinlock addr = %p", device->state->dev_spinlock);

        //taskENTER_CRITICAL(device->state->dev_spinlock);

        //taskEXIT_CRITICAL(device->state->dev_spinlock);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void start_led_task(int pins[], device_def_t * device) {
    TaskHandle_t xHandle = NULL;
    xTaskCreate( vLedTask, "LED DRIVER", STACK_SIZE, device, tskIDLE_PRIORITY, &xHandle );
    
    device->dev_task_handle = xHandle;
}

static device_func_t set_func = {
    .func_name = "set",
    .func = &set_led
};

static device_driver_t driver_funcs = {
    .driver_id = 1,
    .n_pins = 1,
    .init_func = &init_led,
    .start_task = &start_led_task,
    .functions = NULL,
    .num_functions = 1
};

driver_t * gen_led_driver(int pins[])
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

    driver.driver->functions = malloc(sizeof(device_func_t *) * driver.driver->num_functions);
    driver.driver->functions[0] = &set_func;

    driver_t * out = (driver_t *) malloc(sizeof(driver_t));
    memcpy(out, &driver, sizeof(driver_t));

    return out;
}