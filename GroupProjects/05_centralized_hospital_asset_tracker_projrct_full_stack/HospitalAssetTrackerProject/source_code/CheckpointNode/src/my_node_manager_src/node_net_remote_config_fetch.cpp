/**
 * @file node_net_remote_config_fetch.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool NodeManager::fetchRemoteConfig()
{
    if (!my_node_wi_fi.amIConnected())
    {
        Serial.println("[PROVISION] WiFi not connected.");
        return false;
    }

    const myNodeBootstrapConfig &boot_cfg = my_node_net_config.getBootstrapConfig();

    if (boot_cfg.device_id.length() == 0)
    {
        Serial.println("[PROVISION] device_id is empty.");
        return false;
    }

    HTTPClient http;
    WiFiClientSecure secure_client;
    secure_client.setInsecure(); // TODO: replace with a pinned CA certificate for production deployments.

    String url = String(MY_BOOTSTRAP_BASE_URL) + "/nodes/provision";
    Serial.print("[PROVISION] URL = ");
    Serial.println(url);

    // http.begin(url);

    if (!http.begin(secure_client, url))
    {
        /* code */
        Serial.println("[PROVISION] HTTP begin failed.");
        return false;
    }

    http.setTimeout(10000);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> request_doc;
    request_doc["device_id"] = boot_cfg.device_id;

    String request_body;
    serializeJson(request_doc, request_body);

    Serial.println("[PROVISION] Sending request...");
    Serial.println(request_body);

    int http_code = http.POST(request_body);

    if (http_code != 200)
    {
        Serial.print("[PROVISION] HTTP POST failed, code = ");
        Serial.println(http.errorToString(http_code));

        http.end();
        return false;
    }

    String response_body = http.getString();
    http.end();

    Serial.println("[PROVISION] Response received:");
    Serial.println(response_body);

    StaticJsonDocument<384> response_doc;
    DeserializationError err = deserializeJson(response_doc, response_body);

    if (err)
    {
        Serial.print("[PROVISION] JSON parse failed: ");
        Serial.println(err.c_str());
        return false;
    }

    bool is_provisioned = response_doc["is_provisioned"] | false;

    if (!is_provisioned)
    {
        Serial.println("[PROVISION] Node not provisioned yet.");
        return false;
    }

    // You need a mutable way to write remote config.
    // Best approach: add a setter function in MyNodeNetworkConfig.
    String role = response_doc["role"] | "";
    String hospital_name = response_doc["hospital_name"] | "";
    String room_name = response_doc["room_name"] | "";
    String mqtt_host = response_doc["mqtt_host"] | "";
    uint16_t mqtt_port = response_doc["mqtt_port"] | 1883;

    bool remote_config_valid =
        role.length() > 0 &&
        hospital_name.length() > 0 &&
        mqtt_host.length() > 0 &&
        mqtt_port > 0;

    if (!remote_config_valid)
    {
        Serial.println("[PROVISION] Remote config incomplete.");
        return false;
    }

    if (role == MY_ROLE_IS_CHECKPOINT && room_name.length() == 0)
    {
        Serial.println("[PROVISION] Checkpoint node needs room_name.");
        return false;
    }

    my_node_net_config.setRemoteConfig(
        role,
        hospital_name,
        room_name,
        mqtt_host,
        mqtt_port,
        true);
    return true;
}