#ifndef MY_ROBOT_MQTT_HPP
#define MY_ROBOT_MQTT_HPP

#include <PubSubClient.h>
#include "IMyNetworkConnector.hpp"

class MyRobotMQTT : public IMyNetworkConnector
{
private:
    PubSubClient my_mqtt_client;
    Client &esp_client;
    const char *my_server;
    int my_net_port;
    const char *my_id;

public:
    MyRobotMQTT *next;
    MyRobotMQTT(Client &, const char *, int, const char *);
    ~MyRobotMQTT();
    
    void setServer(const char *) override;
    void setPort(int) override;
    void myCallBackFunction(MQTT_CALLBACK_SIGNATURE) override;
    void connectToMyNetwork() override;
    void myNetLoop() override;
    void unsubscribeTheNetwork(const char *) override;

    bool amIconnected() override;
    bool subscribeToMyNetwork(const char *) override;
    bool publishToMyNetwork(const char *, const char *);
};

#endif