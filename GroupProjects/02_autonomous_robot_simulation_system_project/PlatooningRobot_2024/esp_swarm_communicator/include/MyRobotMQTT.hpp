/**
 * @file MyRobotMQTT.hpp
 * @author farros ramzy (424848@student.fontys.nl)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

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
