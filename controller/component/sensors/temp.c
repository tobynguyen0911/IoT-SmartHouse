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
#include "rom/ets_sys.h"
#include "esp_timer.h"

const static char *TAG = "DHT SENSOR";

#define STACK_SIZE 2048

extern int local_ids;

cJSON * dht_create_state(int temp, int humidity)
{
    cJSON *state_root;
	state_root = cJSON_CreateArray();

    cJSON *state_element = cJSON_CreateObject();
    cJSON_AddStringToObject(state_element, "name", "temp");
    cJSON_AddStringToObject(state_element, "type", "int");
    cJSON_AddNumberToObject(state_element, "value", (double) temp);

    cJSON_AddItemToArray(state_root, state_element);

    state_element = cJSON_CreateObject();
    cJSON_AddStringToObject(state_element, "name", "humidity");
    cJSON_AddStringToObject(state_element, "type", "int");
    cJSON_AddNumberToObject(state_element, "value", (double) humidity);

    cJSON_AddItemToArray(state_root, state_element);

    return state_root;
}


void init_dht_sensor(int pins[], device_def_t* device_def)
{
    gpio_reset_pin(pins[0]);

    // Create device_state JSON object
    device_def->state = (device_state_t * ) malloc(sizeof(device_state_t));
    device_def->state->updated = false;

    device_def->state->device_data = dht_create_state(0, 0);

    // Init device lock
    portMUX_TYPE *spinlock = malloc(sizeof(portMUX_TYPE));
    portMUX_INITIALIZE(spinlock);

    device_def->state->dev_spinlock = spinlock;
}

enum dht11_status {
    DHT11_CRC_ERROR = -2,
    DHT11_TIMEOUT_ERROR,
    DHT11_OK
};

static int _waitOrTimeout(uint16_t microSeconds, int level, int pin) {
    int micros_ticks = 0;
    while(gpio_get_level(pin) == level) { 
        if(micros_ticks++ > microSeconds) 
            return DHT11_TIMEOUT_ERROR;
        ets_delay_us(1);
    }
    return micros_ticks;
}

static int _checkCRC(uint8_t data[]) {
    if(data[4] == (data[0] + data[1] + data[2] + data[3]))
        return DHT11_OK;
    else
        return DHT11_CRC_ERROR;
}

static void _sendStartSignal(int pin) {
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, 0);
    ets_delay_us(20 * 1000);
    gpio_set_level(pin, 1);
    ets_delay_us(40);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
}

static int _checkResponse(int pin) {
    /* Wait for next step ~80us*/
    if(_waitOrTimeout(80, 0, pin) == DHT11_TIMEOUT_ERROR)
        return DHT11_TIMEOUT_ERROR;

    /* Wait for next step ~80us*/
    if(_waitOrTimeout(80, 1, pin) == DHT11_TIMEOUT_ERROR) 
        return DHT11_TIMEOUT_ERROR;

    return DHT11_OK;
}

void vTaskDHTSensor(void * pvParameters)
{
    ESP_LOGI(TAG, "Entered Task: DHT11");
    device_def_t * device = (device_def_t *) pvParameters;

    while (1) {
        //ESP_LOGI(TAG, "Spinlock addr = %p", device->state->dev_spinlock);

        //taskENTER_CRITICAL(device->state->dev_spinlock);
        int pin = device->pins[0];

        uint8_t data[5] = {0,0,0,0,0};

        _sendStartSignal(pin);

        if(_checkResponse(pin) == DHT11_TIMEOUT_ERROR)
            printf("\ntimeout error\n");
        
        /* Read response */
        for(int i = 0; i < 40; i++) {
            /* Initial data */
            if(_waitOrTimeout(50, 0, pin) == DHT11_TIMEOUT_ERROR)
                printf("\ntimeout error\n");
                    
            if(_waitOrTimeout(70, 1, pin) > 28) {
                /* Bit received was a 1 */
                data[i/8] |= (1 << (7-(i%8)));
            }
        }

        if(_checkCRC(data) != DHT11_CRC_ERROR) {
            device->state->device_data = dht_create_state(data[2], data[0]);
            device->state->updated = true;
        } else {
            printf("\ndhterror\n");
        }



        //taskEXIT_CRITICAL(device->state->dev_spinlock);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void start_dht_task(int pins[], device_def_t * device) {
    TaskHandle_t xHandle = NULL;
    xTaskCreate( vTaskDHTSensor, "DHT Sensor", STACK_SIZE, device, tskIDLE_PRIORITY, &xHandle );
    
    device->dev_task_handle = xHandle;
}

static device_driver_t driver_funcs = {
    .driver_id = 10,
    .n_pins = 1,
    .init_func = &init_dht_sensor,
    .start_task = &start_dht_task,
    .functions = NULL,
    .num_functions = 0
};

driver_t * gen_dht_driver(int pins[])
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
