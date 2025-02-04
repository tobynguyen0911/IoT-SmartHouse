#include "device_utils.h"

driver_t * gen_smoke_driver(int pins[]);
driver_t * gen_pir_driver(int pins[]);
driver_t * gen_fan_driver(int pins[]);
driver_t * gen_photo_driver(int pins[]);
driver_t * gen_steam_driver(int pins[]);
driver_t * gen_soil_driver(int pins[]);
driver_t * gen_water_driver(int pins[]);
driver_t * gen_pump_btn_driver(int pins[]);
driver_t * gen_dht_driver(int pins[]);