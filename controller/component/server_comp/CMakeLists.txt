idf_component_register(SRCS "server.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES esp_netif driver esp_wifi vfs nvs_flash esp-tls esp_http_client)