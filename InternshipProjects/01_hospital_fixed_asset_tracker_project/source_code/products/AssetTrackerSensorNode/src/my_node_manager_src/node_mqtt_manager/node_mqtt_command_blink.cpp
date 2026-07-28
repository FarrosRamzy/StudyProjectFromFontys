/**
 * @file node_mqtt_command_blink.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <ArduinoJson.h>
#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void NodeManager::handleBlinkCommand(const char *topic, const char *payload, unsigned int length)
{
    (void)topic;

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload, length);

    const char *command = doc["command"] | "";
    const char *command_id = doc["command_id"] | "";

    if (error)
    {
        Serial.print("[MQTT] Invalid blink command JSON: ");
        Serial.println(error.c_str());
        publishCommandAck("blink", "invalid_json", "");
        return;
    }

    if (strcmp(command, "blink") != 0)
    {
        Serial.println("[MQTT] Ignored command because command is not blink.");
        publishCommandAck("blink", "ignored", command_id);
        return;
    }

    uint8_t blink_count = doc["blink_count"] | IDENTIFY_BLINK_COUNT;
    uint32_t interval_ms = doc["interval_ms"] | IDENTIFY_BLINK_INTERVAL_MS;

    if (blink_count == 0)
    {
        blink_count = IDENTIFY_BLINK_COUNT;
    }

    if (blink_count > 20)
    {
        blink_count = 20;
    }

    if (interval_ms < 50)
    {
        interval_ms = IDENTIFY_BLINK_INTERVAL_MS;
    }

    if (interval_ms > 2000)
    {
        interval_ms = 2000;
    }

    Serial.print("[MQTT] Blink command accepted. Count: ");
    Serial.print(blink_count);
    Serial.print(", interval: ");
    Serial.println(interval_ms);

    my_node_status_led.startIdentifyBlink(blink_count, interval_ms);
    publishCommandAck("blink", "accepted", command_id);
}
