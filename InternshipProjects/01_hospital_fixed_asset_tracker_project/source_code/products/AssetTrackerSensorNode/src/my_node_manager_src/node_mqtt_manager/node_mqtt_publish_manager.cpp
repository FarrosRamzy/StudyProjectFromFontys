/**
 * @file node_mqtt_publish_manager.cpp
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
 * @param tag_id
 */
void NodeManager::publishCheckpoint(const char *tag_id)
{
    char time_stamp[32] = {0};

    if (!prepareMQTTTimestamp(time_stamp, sizeof(time_stamp)))
    {
        Serial.println("[MQTT] Detection publish failed: MQTT is not connected.");
        return;
    }

    String room_name = checkRole(my_node_role);

    bool ok = my_node_mqtt.publishDetection(
        my_hospital_id.c_str(),
        my_node_hospital.c_str(),
        my_node_id.c_str(),
        room_name.c_str(),
        tag_id,
        time_stamp);

    if (!ok)
    {
        Serial.println("[MQTT] Detection publish failed.");
    }
}

/**
 * @brief
 *
 * @param tag_id
 */
void NodeManager::publishRegistration(const char *tag_id)
{
    char time_stamp[32] = {0};

    if (!prepareMQTTTimestamp(time_stamp, sizeof(time_stamp)))
    {
        Serial.println("[MQTT] Registration publish failed: MQTT is not connected.");
        return;
    }

    bool ok = my_node_mqtt.publishRegistration(
        my_hospital_id.c_str(),
        my_node_hospital.c_str(),
        my_node_id.c_str(),
        tag_id,
        time_stamp);

    if (!ok)
    {
        Serial.println("[MQTT] Registration publish failed.");
    }
}
