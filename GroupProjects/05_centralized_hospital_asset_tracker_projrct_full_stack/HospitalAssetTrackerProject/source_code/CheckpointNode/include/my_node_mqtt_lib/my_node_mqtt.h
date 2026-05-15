/**
 * @file my_node_mqtt.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <stdint.h>
#include "interfaces/i_my_node_mqtt_connector.h"

class MyNodeMQTT : public IMyNodeMQTTConnector
{
private:
    PubSubClient my_node_mqtt_client;
    WiFiClient &node_esp_client;
    const char *my_node_net_server;
    int my_node_net_port;
    const char *my_node_net_id;
    void (*my_mqtt_callback)(char *, uint8_t *, unsigned int);
    uint32_t last_reconnect_attempt;
    uint32_t reconnect_interval;

    static MyNodeMQTT *my_active_instance;

public:
    MyNodeMQTT(WiFiClient &, const char *, int, const char *, void (*my_mqtt_callback)(char *, uint8_t *, unsigned int));
    ~MyNodeMQTT() override;

    void startMyMQTT() override;
    
    void setNodeMQTTServer(const char *) override;
    void setNodeMQTTPort(int) override;
    void setNodeMQTTClientId(const char *) override;
    
    void myNodeCallbackFunction(char *, uint8_t *, unsigned int) override;
    void setMessageCallback(void (*cb)(char *, uint8_t *, unsigned int)) override;

    void connectToMyNodeNetwork() override;
    void myNodeMQTTLoop() override;

    void unsubscribeMyNodeNetMQTT(const char *) override;

    void updateServerConfig() override;

    void reconnectToMyMQTT() override;

    bool amIConnected() override;

    bool subscribeToMyNodeNetMQTT(const char *) override;

    bool publishToMyNodeNetMQTT(const char *, const char *) override;
    bool publishDetection(const char *, const char *, const char *, const char *, const char *, const char *) override;
    bool publishRegistration(const char *, const char *, const char *, const char *, const char *) override;
    bool publishHeartbeat(const char *, const char *, const char *, const char *, const char *) override;
    bool publishGreeting(const char *, const char *, const char *, const char *, const char *, const char *, const char *) override;

private:
    static void myMQTTCallbackRouter(char *, uint8_t *, unsigned int);
    static bool hasRequiredText(const char *);
    static bool topicWasBuilt(int, size_t);
    static bool buildJsonPayload(JsonDocument &, char *, size_t);
};