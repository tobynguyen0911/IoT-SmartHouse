idf_component_register(SRCS "wifi_setup.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES esp_netif driver esp_wifi vfs nvs_flash)
