idf_component_register(SRCS "smoke_sensor.c" "fan.c" "photo_sensor.c" "steam_sensor.c" "adc.c" "water_sensor.c" "soil_sensor.c" "water_pump.c" "temp.c"
                        INCLUDE_DIRS "include"
                        PRIV_REQUIRES json esp_adc device_utils esp_timer esp_driver_gpio)