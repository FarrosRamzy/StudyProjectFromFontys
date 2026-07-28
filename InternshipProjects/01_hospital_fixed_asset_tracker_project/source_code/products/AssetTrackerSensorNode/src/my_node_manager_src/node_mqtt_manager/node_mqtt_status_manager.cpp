/**
 * @file node_mqtt_status_manager.cpp
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
 */
void NodeManager::handleHeartbeat()
{
    uint32_t now = my_clock.millisNow();

    if ((uint32_t)(now - last_heartbeat_time) < heartbeat_interval)
    {
        return;
    }

    char time_stamp[32] = {0};

    if (!prepareMQTTTimestamp(time_stamp, sizeof(time_stamp)))
    {
        Serial.println("[MQTT] Heartbeat publish failed: MQTT is not connected.");
        return;
    }

    String room_name = checkRole(my_node_role);

    bool ok = my_node_mqtt.publishHeartbeat(
        my_hospital_id.c_str(),
        my_node_hospital.c_str(),
        my_node_id.c_str(),
        room_name.c_str(),
        time_stamp);

    if (ok)
    {
        last_heartbeat_time = now;
    }
    else
    {
        Serial.println("[MQTT] Heartbeat publish failed.");
    }
}

/**
 * @brief
 *
 */
void NodeManager::sayHello()
{
    my_node_msg = MY_DEFAULT_GREET_IN_MSG;
    my_node_stat = MY_ONLINE_STAT;
    handleGreetings(my_node_msg.c_str(), my_node_stat.c_str());
}

/**
 * @brief
 *
 */
void NodeManager::sayGoodbye()
{
    my_node_msg = MY_DEFAULT_GREET_OUT_MSG;
    my_node_stat = MY_OFFLINE_STAT;
    handleGreetings(my_node_msg.c_str(), my_node_stat.c_str());
}

/**
 * @brief
 *
 * @param msg
 * @param stat
 */
void NodeManager::handleGreetings(const char *msg, const char *stat)
{
    char time_stamp[32] = {0};

    if (!prepareMQTTTimestamp(time_stamp, sizeof(time_stamp)))
    {
        Serial.println("[MQTT] Status publish failed: MQTT is not connected.");
        return;
    }

    String room_name = checkRole(my_node_role);

    bool ok = my_node_mqtt.publishGreeting(
        my_hospital_id.c_str(),
        my_node_hospital.c_str(),
        my_node_id.c_str(),
        room_name.c_str(),
        msg,
        stat,
        time_stamp);

    if (!ok)
    {
        Serial.println("[MQTT] Status publish failed.");
    }
}
