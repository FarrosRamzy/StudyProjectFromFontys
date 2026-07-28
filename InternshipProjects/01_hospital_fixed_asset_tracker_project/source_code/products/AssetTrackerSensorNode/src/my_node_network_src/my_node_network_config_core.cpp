/**
 * @file my_node_network_config_core.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief Construct a new My Node Network Config:: My Node Network Config object
 *
 */
MyNodeNetworkConfig::MyNodeNetworkConfig()
    : my_web_server(MY_WEB_SERVER_PORT),
      my_setup_mode(false),
      my_restart_at_ms(0),
      my_restart_pending(false)
{
    // Bootstrap config
    my_bootstrap_config.device_id = "";
    my_bootstrap_config.wifi_ssid = "";
    my_bootstrap_config.wifi_password = "";
    my_bootstrap_config.is_configured = false;

    // Remote config
    my_remote_config.role = "";
    my_remote_config.hospital_name = "";
    my_remote_config.room_name = "";
    my_remote_config.mqtt_host = MY_NET_MQTT_BROKER_TEST;
    my_remote_config.mqtt_port = MY_NET_MQTT_PORT_TEST;
    my_remote_config.is_provisioned = false;
}

/**
 * @brief Destroy the My Node Network Config:: My Node Network Config object
 *
 */
MyNodeNetworkConfig::~MyNodeNetworkConfig()
{
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::beginMyNetConfig()
{
    bool fs_start_ok = LittleFS.begin(true);

    if (!fs_start_ok)
    {
        Serial.println("[NETCFG] LittleFS mount failed.");
    }
    else
    {
        Serial.println("[NETCFG] LittleFS mounted.");
    }

    loadConfig();

    if (my_bootstrap_config.is_configured &&
        my_bootstrap_config.device_id.length() > 0 &&
        my_bootstrap_config.wifi_ssid.length() > 0)
    {
        my_setup_mode = false;
        Serial.println("[NETCFG] saved config found.");
        return;
    }

    Serial.println("[NETCFG] No valid config found. Entering setup mode.");
    my_setup_mode = true;

    startAccessPoint();
    startWebServer();
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::loopMyNetConfig()
{
    if (!my_setup_mode)
    {
        return;
    }

    my_web_server.handleClient();

    if (my_restart_pending)
    {
        uint32_t now = millis();
        if ((int32_t)(now - my_restart_at_ms) >= 0)
        {
            Serial.println("[NETCFG] Restarting ESP after result page delay...");
            ESP.restart();
        }
    }
}
