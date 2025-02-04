idf_component_register(SRCS "led_driver.c" "led_btn_driver.c"
                        INCLUDE_DIRS "include"
                        PRIV_REQUIRES json device_utils esp_http_client esp_driver_gpio)