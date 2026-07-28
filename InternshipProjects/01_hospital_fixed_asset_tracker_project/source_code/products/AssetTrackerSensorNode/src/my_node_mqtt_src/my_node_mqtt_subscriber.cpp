/**
 * @file my_node_mqtt_subscriber.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_mqtt_lib/my_node_mqtt.h"


/**
 * @brief 
 * 
 * @param my_net_topic 
 * @return true 
 * @return false 
 */
bool MyNodeMQTT::subscribeToMyNodeNetMQTT(const char *my_net_topic)
{
    if (my_net_topic == nullptr || my_net_topic[0] == '\0')
    {
        Serial.println("[MQTT] Subscribe failed: topic is empty.");
        return false;
    }

    if (!my_node_mqtt_client.connected())
    {
        Serial.println("[MQTT] Subscribe failed: MQTT is not connected.");
        return false;
    }

    bool ok = my_node_mqtt_client.subscribe(my_net_topic);

    if (!ok)
    {
        Serial.print("[MQTT] Subscribe failed. MQTT state = ");
        Serial.println(my_node_mqtt_client.state());
    }

    return ok;
}

/**
 * @brief
 *
 * @param my_net_topic
 */
void MyNodeMQTT::unsubscribeMyNodeNetMQTT(const char *my_net_topic)
{
    my_node_mqtt_client.unsubscribe(my_net_topic);
}
