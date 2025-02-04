ESP-IDF app: IoT Smart Home
====================

Architecture:

Main:
    Starts component tasks
    Monitors status
Components:
    wifi_comp:
        Manages wifi connections
    server_comp:
        Makes requests and parses response from server.