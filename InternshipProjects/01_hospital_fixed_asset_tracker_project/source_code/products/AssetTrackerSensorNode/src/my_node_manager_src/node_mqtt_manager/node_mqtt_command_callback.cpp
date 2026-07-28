/**
 * @file node_mqtt_command_callback.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void NodeManager::myNodeMQTTCallback(char *topic, uint8_t *payload, unsigned int length)
{
    if (active_instance != nullptr)
    {
        active_instance->handleMqttMessage(topic, payload, length);
    }
}

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void NodeManager::handleMqttMessage(char *topic, uint8_t *payload, unsigned int length)
{
    if (topic == nullptr || payload == nullptr || length == 0)
    {
        return;
    }

    char expected_topic[SIZE_OF_TOPIC] = {0};

    snprintf(
        expected_topic,
        sizeof(expected_topic),
        "%s/%s/%s/%s/%s/%s",
        MQTT_TOPIC_ROOT,
        my_hospital_id.c_str(),
        MQTT_TOPIC_NODES,
        my_node_id.c_str(),
        MQTT_TOPIC_COMMANDS,
        MQTT_TOPIC_COMMAND_BLINK);

    if (strcmp(topic, expected_topic) == 0)
    {
        handleBlinkCommand(topic, (const char *)payload, length);
        return;
    }

    Serial.print("[MQTT] Ignored command topic: ");
    Serial.println(topic);
}
