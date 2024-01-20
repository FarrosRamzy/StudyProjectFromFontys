#include "../include/remoteController/MyRemoteMQTT.hpp"

bool MyRemoteMQTT::subscribeToMyNetwork(const char *net_topic)
{
    return my_mqtt_client.subscribe(net_topic);
}

void MyRemoteMQTT::unsubscribeTheNetwork(const char *net_topic)
{
    my_mqtt_client.unsubscribe(net_topic);
}