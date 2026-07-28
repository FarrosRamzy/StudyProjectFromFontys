/**
 * @file my_node_network_config_reset.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::resetConfiguration()
{
    clearBootstrapConfig(true);
    clearRemoteConfig();

    Serial.println("[NETCFG] Config cleared!");
}

/**
 * @brief
 *
 * @param keep_device_id
 */
void MyNodeNetworkConfig::clearBootstrapConfig(bool keep_device_id)
{
    my_preferences.begin("nodecfg", false);
    if (!keep_device_id)
    {
        my_preferences.remove("devid");
        my_bootstrap_config.device_id = "";
    }

    my_preferences.remove("ssid");
    my_preferences.remove("pass");
    my_preferences.remove("cfgd");

    my_preferences.end();

    my_bootstrap_config.wifi_ssid = "";
    my_bootstrap_config.wifi_password = "";
    my_bootstrap_config.is_configured = false;

    Serial.println("[NETCFG] Bootstrap config cleared!");
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::clearRemoteConfig()
{
    my_preferences.begin("nodecfg", false);

    my_preferences.remove("role");
    my_preferences.remove("hospital");
    my_preferences.remove("name");
    my_preferences.remove("mqtt");
    my_preferences.remove("mport");
    my_preferences.remove("provd");

    my_preferences.end();

    my_remote_config.role = "";
    my_remote_config.hospital_name = "";
    my_remote_config.room_name = "";
    my_remote_config.mqtt_host = MY_NET_MQTT_BROKER_TEST;
    my_remote_config.mqtt_port = MY_NET_MQTT_PORT_TEST;
    my_remote_config.is_provisioned = false;

    Serial.println("[NETCFG] Bootstrap config cleared!");
}
