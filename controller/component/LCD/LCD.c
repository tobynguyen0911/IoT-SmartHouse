#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "cJSON.h"
#include "device_utils.h"
#include "esp_http_client.h"
#include <string.h>

#include "HD44780.h"

#define STACK_SIZE 2048

#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 2

static const char *TAG = "LCD";

extern int local_ids;

cJSON * LCD_create_state(char * value)
{
    cJSON *state_root;
	state_root = cJSON_CreateArray();

    cJSON *state_element = cJSON_CreateObject();
    cJSON_AddStringToObject(state_element, "name", "text");
    cJSON_AddStringToObject(state_element, "type", "str");

    //Copy value
    char * val = (char *) malloc(strlen(value));
    strcpy(val, value);

    cJSON_AddStringToObject(state_element, "value", val);

    cJSON_AddItemToArray(state_root, state_element);

    return state_root;
}

void set_LCD(device_def_t * device, cJSON * params)
{
    //ESP_LOGI(TAG, "Spinlock addr = %p", device->state->dev_spinlock);

    //taskENTER_CRITICAL(device->state->dev_spinlock);

    // Parse params to get the new state
    char * new_lcd_state = cJSON_GetStringValue(params);

    // Set the LCD
    LCD_home();
    LCD_clearScreen();
    LCD_writeStr("----- 20x2 LCD -----");

    cJSON * new_state = LCD_create_state(new_lcd_state);
    cJSON_Delete(device->state->device_data);
    device->state->device_data = new_state;
    device->state->updated = true;

    //taskEXIT_CRITICAL(device->state->dev_spinlock);
}

void init_LCD(int pins[], device_def_t* device_def)
{

    // Setup pins
    //SDA_PIN = pins[0]
    //SCL_PIN = pins[1]
    //LCD_COLS = 20?
    //LCD_ROWS = 2
    printf("\nStarting LCD\n");
    LCD_init(LCD_ADDR, pins[0], pins[1], LCD_COLS, LCD_ROWS);

    LCD_home();
    LCD_clearScreen();
    LCD_writeStr("----- 20x2 LCD -----");

    // Create device_state JSON object
    device_def->state = (device_state_t * ) malloc(sizeof(device_state_t));
    device_def->state->updated = false;

    device_def->state->device_data = LCD_create_state("Init");

    // Init device lock
    portMUX_TYPE *spinlock = malloc(sizeof(portMUX_TYPE));
    portMUX_INITIALIZE(spinlock);

    device_def->state->dev_spinlock = spinlock;

    //printf("Spinlock addr = %p", spinlock);
}

void vLCDTask(void * pvParameters)
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

void start_LCD_task(int pins[], device_def_t * device) {
    TaskHandle_t xHandle = NULL;
    xTaskCreate( vLCDTask, "LCD DRIVER", STACK_SIZE, device, tskIDLE_PRIORITY, &xHandle );
    
    device->dev_task_handle = xHandle;
}

device_func_t set_func = {
    .func_name = "set",
    .func = &set_LCD
};

device_driver_t driver_funcs = {
    .driver_id = 16,
    .n_pins = 2,
    .init_func = &init_LCD,
    .start_task = &start_LCD_task,
    .functions = NULL,
    .num_functions = 1
};

driver_t * gen_LCD_driver(int pins[])
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