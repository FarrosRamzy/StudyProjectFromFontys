/**
 * @file MyNetCommSubscriber.cpp
 * @author farros ramzy (424848@student.fontys.nl)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "MyRobotMQTT.hpp"

bool MyRobotMQTT::subscribeToMyNetwork(const char *net_topic)
{
    return my_mqtt_client.subscribe(net_topic);
}

void MyRobotMQTT::unsubscribeTheNetwork(const char *net_topic)
{
    my_mqtt_client.unsubscribe(net_topic);
}