/**
 * @file node_net_remote_config_apply.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 */
void NodeManager::applyRemoteConfig()
{
    const myNodeRemoteConfig &cfg_remote = my_node_net_config.getRemoteConfig();

    my_node_role = cfg_remote.role;
    my_node_hospital = cfg_remote.hospital_name;
    my_node_is_provisioned = cfg_remote.is_provisioned;

    my_hospital_id = hospitalNameToID(my_node_hospital);

    // Check role and apply the room requirement
    if (my_node_role == MY_ROLE_IS_REGISTRATION)
    {
        my_node_room = "";
    }
    else
    {
        my_node_room = cfg_remote.room_name;
    }

    // Keeping client ID stable and technical.
    my_node_client_id = my_node_id;

    my_node_mqtt.setNodeMQTTClientId(my_node_client_id.c_str());
    my_node_mqtt.setNodeMQTTServer(cfg_remote.mqtt_host.c_str());
    my_node_mqtt.setNodeMQTTPort((int)cfg_remote.mqtt_port);
    my_node_mqtt.updateServerConfig();
    my_node_mqtt.startMyMQTT();

    Serial.println("[PROVISION] Remote config saved.");

    Serial.print("[SYSTEM] role = ");
    Serial.println(my_node_role);
    Serial.print("[SYSTEM] hospital = ");
    Serial.println(my_node_hospital);
    Serial.print("[SYSTEM] hospital_ID = ");
    Serial.println(my_hospital_id);
    Serial.print("[SYSTEM] room = ");
    Serial.println(my_node_room);

    Serial.println("[SYSTEM] Remote config applied.");
}