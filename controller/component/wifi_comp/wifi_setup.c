#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

#define EXAMPLE_ESP_MAXIMUM_RETRY 5

#define HARDCODED_SSID "CaseRegistered"
#define HARDCODED_PWD "Xg*TPPNuX#"

static const char *TAG = "wifi station";

static EventGroupHandle_t os_wifi_event_group;
static int s_retry_num = 0;

static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            printf("Retry connection!");
        } else {
            xEventGroupSetBits(os_wifi_event_group, WIFI_FAIL_BIT);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        s_retry_num = 0;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(os_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_station_init(void)
{
    printf("Initiating WiFi\n");
    os_wifi_event_group = xEventGroupCreate();

    esp_netif_init();

    printf("initiated netif\n");

    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    printf("created event loop\n");

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    printf("config wifi\n");

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    esp_event_handler_instance_register(WIFI_EVENT,
                                        ESP_EVENT_ANY_ID,
                                        &event_handler,
                                        NULL,
                                        &instance_any_id);

    esp_event_handler_instance_register(IP_EVENT,
                                        IP_EVENT_STA_GOT_IP,
                                        &event_handler,
                                        NULL,
                                        &instance_got_ip);


    wifi_config_t wifi_config = {
        .sta = {
            .ssid = HARDCODED_SSID,
            //.password = HARDCODED_PWD,
            //.threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD;
            //.sae_pwe_h2e = ESP_WIFI_SAE_MODE;
            //.sae_h2e_identifier = EXAMPLE_H2E_IDENTIFIER;
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    printf("Started WiFi\n");

    EventBits_t bits = xEventGroupWaitBits(os_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);
    if (bits & WIFI_CONNECTED_BIT) {
        printf("Connected to...");
        
    } else if (bits & WIFI_FAIL_BIT) {
        printf("Failed to connect");
    }
}
