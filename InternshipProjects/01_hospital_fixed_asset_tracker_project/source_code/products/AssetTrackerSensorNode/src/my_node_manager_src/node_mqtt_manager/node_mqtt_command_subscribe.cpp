/**
 * @file node_mqtt_command_subscribe.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

void NodeManager::subscribeToCommandTopics()
{
    if (my_commands_subscribed)
    {
        return;
    }

    if (!my_node_mqtt.amIConnected())
    {
        Serial.println("[MQTT] Command subscribe skipped: MQTT is not connected.");
        return;
    }

    if (my_hospital_id.length() == 0 || my_node_id.length() == 0)
    {
        Serial.println("[MQTT] Command subscribe skipped: hospital ID or node ID is empty.");
        return;
    }

    char topic[SIZE_OF_TOPIC] = {0};

    int topic_len = snprintf(
        topic,
        sizeof(topic),
        "%s/%s/%s/%s/%s/%s",
        MQTT_TOPIC_ROOT,
        my_hospital_id.c_str(),
        MQTT_TOPIC_NODES,
        my_node_id.c_str(),
        MQTT_TOPIC_COMMANDS,
        MQTT_TOPIC_COMMAND_BLINK);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Command topic is too long.");
        return;
    }

    bool ok = my_node_mqtt.subscribeToMyNodeNetMQTT(topic);

    Serial.print("[MQTT] Subscribe command topic: ");
    Serial.print(topic);
    Serial.print(" -> ");
    Serial.println(ok ? "OK" : "FAILED");

    my_commands_subscribed = ok;
}
