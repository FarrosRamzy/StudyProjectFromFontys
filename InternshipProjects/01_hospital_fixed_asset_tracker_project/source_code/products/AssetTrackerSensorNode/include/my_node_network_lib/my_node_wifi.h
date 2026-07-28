/**
 * @file my_node_wifi.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <WiFi.h>
#include <stdint.h>
#include "my_node_network_lib/interfaces/i_my_node_wifi.h"
#include "node_config.h"

class MyNodeWiFi : public IMyNodeWiFi
{
private:
    String ssid;
    String password;
    uint32_t last_reconnect_attempt;
    uint32_t reconnect_interval;

public:
    MyNodeWiFi();
    ~MyNodeWiFi() override;

    void setCredentials(const char *, const char *) override;
    bool hasCredentials() const override;

    void startWiFi() override;
    void loopNetWiFi() override;
    bool amIConnected() override;
    void reconnectWiFi() override;
    void disconnectWiFi() override;
};
