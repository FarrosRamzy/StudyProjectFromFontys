/**
 * @file node_mqtt_command_ack.cpp
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
 * @param command
 * @param status
 */
void NodeManager::publishCommandAck(const char *command, const char *status, const char* id)
{
    char topic[SIZE_OF_TOPIC] = {0};
    char payload[SIZE_OF_PAYLOAD] = {0};

    int topic_len = snprintf(
        topic,
        sizeof(topic),
        "%s/%s/%s/%s/%s/%s",
        MQTT_TOPIC_ROOT,
        my_hospital_id.c_str(),
        MQTT_TOPIC_NODES,
        my_node_id.c_str(),
        MQTT_TOPIC_COMMANDS,
        MQTT_TOPIC_COMMAND_ACK);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Command ACK topic is too long.");
        return;
    }

    JsonDocument doc;
    doc["command"] = command;
    doc["status"] = status;
    doc["command_id"] = id ? id : "";
    doc["device_id"] = my_node_id;
    doc["hospital_id"] = my_hospital_id;

    size_t written = serializeJson(doc, payload, sizeof(payload));

    if (written == 0 || written >= sizeof(payload))
    {
        Serial.println("[MQTT] Command ACK payload build failed.");
        return;
    }

    my_node_mqtt.publishToMyNodeNetMQTT(topic, payload);
}
