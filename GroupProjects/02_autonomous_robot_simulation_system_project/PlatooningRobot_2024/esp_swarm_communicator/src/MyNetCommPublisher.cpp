/**
 * @file MyNetCommPublisher.cpp
 * @author farros ramzy (424848@student.fontys.nl)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "MyRobotMQTT.hpp"

bool MyRobotMQTT::publishToMyNetwork(const char *net_topic, const char *net_message)
{
    return my_mqtt_client.publish(net_topic, net_message);
}