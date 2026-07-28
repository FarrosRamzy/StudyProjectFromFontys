#pragma once

#include <stdint.h>

struct MyNodeRemoteConfigLite
{
    const char *role;
    const char *hospital_name;
    const char *room_name;
    const char *mqtt_host;
    uint16_t mqtt_port;
    bool is_provisioned;
};

bool hasCoreText(const char *value);
bool isCheckpointRole(const char *role);
bool isRegistrationRole(const char *role);
bool isProvisionedConfigValid(const MyNodeRemoteConfigLite &config);
