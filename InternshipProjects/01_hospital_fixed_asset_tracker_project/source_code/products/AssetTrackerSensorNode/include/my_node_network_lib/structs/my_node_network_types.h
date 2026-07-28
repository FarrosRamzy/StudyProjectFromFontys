/**
 * @file my_node_network_types.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "node_config.h"

struct myNodeBootstrapConfig
{
    String device_id;
    String wifi_ssid;
    String wifi_password;
    bool is_configured;
};

struct myNodeRemoteConfig
{
    String role;
    String hospital_name;
    String room_name;
    String mqtt_host;
    uint16_t mqtt_port;
    bool is_provisioned;
};
