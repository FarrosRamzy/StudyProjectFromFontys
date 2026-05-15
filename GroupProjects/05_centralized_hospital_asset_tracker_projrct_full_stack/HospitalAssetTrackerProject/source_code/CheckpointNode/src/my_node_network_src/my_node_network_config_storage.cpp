/**
 * @file my_node_network_config_storage.cpp
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
 * @brief
 *
 */
void MyNodeNetworkConfig::loadConfig()
{
    my_preferences.begin("nodecfg", true);

    my_bootstrap_config.device_id = my_preferences.getString("devid", "");
    my_bootstrap_config.wifi_ssid = my_preferences.getString("ssid", "");
    my_bootstrap_config.wifi_password = my_preferences.getString("pass", "");
    my_bootstrap_config.is_configured = my_preferences.getBool("cfgd", false);

    my_remote_config.role = my_preferences.getString("role", "");
    my_remote_config.hospital_name = my_preferences.getString("hospital", "");
    my_remote_config.room_name = my_preferences.getString("name", "");
    my_remote_config.mqtt_host = my_preferences.getString("mqtt", MY_NET_MQTT_BROKER_TEST);
    my_remote_config.mqtt_port = my_preferences.getUShort("mport", MY_NET_MQTT_PORT_TEST);
    my_remote_config.is_provisioned = my_preferences.getBool("provd", false);

    my_preferences.end();

    if (my_bootstrap_config.device_id.length() == 0)
    {
        /* code */
        my_bootstrap_config.device_id = generateDeviceId();
        saveConfig();

        Serial.print("[NETCFG] device ID generated as ");
        Serial.print(my_bootstrap_config.device_id);
        Serial.println(" and saved.");
    }

    Serial.println("[NETCFG] Config loaded.");
    Serial.print("[NETCFG] configured = ");
    Serial.println(my_bootstrap_config.is_configured ? "true" : "false");
    Serial.print("[NETCFG] device_id = ");
    Serial.println(my_bootstrap_config.device_id);
    Serial.print("[NETCFG] wifi_ssid = ");
    Serial.println(my_bootstrap_config.wifi_ssid);

    Serial.print("[NETCFG] provisioned = ");
    Serial.println(my_remote_config.is_provisioned ? "true" : "false");
    Serial.print("[NETCFG] room_name = ");
    Serial.println(my_remote_config.room_name);
    Serial.print("[NETCFG] mqtt_host = ");
    Serial.println(my_remote_config.mqtt_host);
    Serial.print("[NETCFG] mqtt_port = ");
    Serial.println(my_remote_config.mqtt_port);
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::saveConfig()
{
    my_preferences.begin("nodecfg", false);

    // Bootstrap config
    my_preferences.putString("devid", my_bootstrap_config.device_id);
    my_preferences.putString("ssid", my_bootstrap_config.wifi_ssid);
    my_preferences.putString("pass", my_bootstrap_config.wifi_password);
    my_preferences.putBool("cfgd", my_bootstrap_config.is_configured);

    // Remote config
    my_preferences.putString("role", my_remote_config.role);
    my_preferences.putString("hospital", my_remote_config.hospital_name);
    my_preferences.putString("name", my_remote_config.room_name);
    my_preferences.putString("mqtt", my_remote_config.mqtt_host);
    my_preferences.putUShort("mport", my_remote_config.mqtt_port);
    my_preferences.putBool("provd", my_remote_config.is_provisioned);

    my_preferences.end();

    Serial.println("[NETCFG] config saved.");
}

void MyNodeNetworkConfig::setRemoteConfig(const String &role, const String &hospital_name, const String &room_name,
                                          const String &mqtt_host, uint16_t mqtt_port,
                                          bool is_provisioned)
{
    my_remote_config.role = role;
    my_remote_config.hospital_name = hospital_name;
    my_remote_config.room_name = room_name;
    my_remote_config.mqtt_host = mqtt_host;
    my_remote_config.mqtt_port = mqtt_port;
    my_remote_config.is_provisioned = is_provisioned;

    saveConfig();

    Serial.println("[NETCFG] Remote config updated and saved.");
}