/**
 * @file i_my_node_mqtt_connector.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <PubSubClient.h>
#include "i_my_node_mqtt_publisher.h"
#include "i_my_node_mqtt_subscriber.h"

class IMyNodeMQTTConnector : public IMyNodeMQTTSubscriber, public IMyNodeMQTTPublisher
{
public:
    virtual ~IMyNodeMQTTConnector() {};

    virtual void setNodeMQTTServer(const char *) = 0;
    virtual void setNodeMQTTPort(int) = 0;
    virtual void setNodeMQTTClientId(const char *) = 0;

    virtual void myNodeCallbackFunction(char *, uint8_t *, unsigned int) = 0;
    virtual void setMessageCallback(void (*cb)(char *, uint8_t *, unsigned int)) = 0;

    virtual void startMyMQTT() = 0;
    virtual void connectToMyNodeNetwork() = 0;
    virtual void reconnectToMyMQTT() = 0;
    virtual void updateServerConfig() = 0;
    virtual void myNodeMQTTLoop() = 0;

    virtual bool amIConnected() = 0;

    virtual bool publishDetection(const char *, const char *, const char *, const char *, const char *, const char *) = 0;
    virtual bool publishRegistration(const char *, const char *, const char *, const char *, const char *) = 0;
    virtual bool publishHeartbeat(const char *, const char *, const char *, const char *, const char *) = 0;
    virtual bool publishGreeting(const char *, const char *, const char *, const char *, const char *, const char *, const char *) = 0;
};