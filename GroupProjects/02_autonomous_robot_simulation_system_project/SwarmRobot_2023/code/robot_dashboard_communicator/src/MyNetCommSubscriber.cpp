#include "MyRobotMQTT.hpp"

bool MyRobotMQTT::subscribeToMyNetwork(const char *net_topic)
{
    return my_mqtt_client.subscribe(net_topic);
}

void MyRobotMQTT::unsubscribeTheNetwork(const char *net_topic)
{
    my_mqtt_client.unsubscribe(net_topic);
}