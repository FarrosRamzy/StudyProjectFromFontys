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
    return my_node_mqtt_client.subscribe(my_net_topic);
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