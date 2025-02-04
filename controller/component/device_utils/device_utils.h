#ifndef DEVICE_UTILS_H
#define DEVICE_UTILS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "cJSON.h"


// Each device instatiated has one state object
// This keeps track of its state and if it needs updating
typedef struct device_state_t {
    int updated;
    cJSON * device_data;

    // This protects access to the other two fields
    // It should always be aquired when reading/writing to from the others
    // except during the init sequence (and released after!)
    portMUX_TYPE * dev_spinlock;
} device_state_t;


// This defines an individual device
typedef struct device_def_t {
    int device_local_id;
    char * device_id;
    int * pins;
    TaskHandle_t dev_task_handle;
    device_state_t * state;
} device_def_t;


// This encapsulates a function used by a device
typedef struct device_func_t {
    char * func_name;
    void (*func)(device_def_t * device, cJSON * parameters);
} device_func_t;


// This defines the driver for a device
// This will be shared across instances if multiple
// of the same device are connected
typedef struct device_driver_t {
    int driver_id;
    int n_pins;
    // This should initialize the GPIO pins and create the device_state_t struct
    // It should also initialize the cJSON struct data
    void (*init_func)(int pins[], device_def_t* device_state);
    // This function should take a pin map, a device_state_t address, and a spinlock
    // And should start the device driver's task with those parameters
    void (*start_task)(int pins[], device_def_t * device);
    device_func_t ** functions;
    int num_functions;
} device_driver_t;


// This defines the controller
typedef struct controller_def_t {
    int controller_local_id;
    int devices_n;
    device_def_t** devices;
} controller_def_t;


// This stores the driver code and device definition
// For a single device
typedef struct driver_t {
    device_def_t * definition;
    device_driver_t * driver;
} driver_t;

int convert_analog_pin(int pin);

#endif

// Approximate startup sequence:

/*
MAIN_INIT:
- hardcoded: device_driver_t
- foreach device_driver_t
    - malloc a device_state_t struct
    - run init_func
    - create device_def_t
- foreach device_driver_t
    - start_task
    - store task handle in device_def_t
MAIN_LOOP:
- foreach device_def_t
    - aquire spinlock for state
    - check updated
    - if true, send POST to server
    - release spinlock

TASK:
- check state
- acquire spinlock
- compare new state
- set update and update state struct if necessary
- release spinlock
*/