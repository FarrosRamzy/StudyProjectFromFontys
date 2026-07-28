/**
 * @file my_node_remote_config_validator.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <string.h>

#include "my_node_core_lib/my_node_remote_config_validator.h"

static bool textEquals(const char *left, const char *right)
{
    return left != nullptr && right != nullptr && strcmp(left, right) == 0;
}

bool hasCoreText(const char *value)
{
    return value != nullptr && value[0] != '\0';
}

bool isCheckpointRole(const char *role)
{
    return textEquals(role, "CHECKPOINT");
}

bool isRegistrationRole(const char *role)
{
    return textEquals(role, "REGISTRATION");
}

bool isProvisionedConfigValid(const MyNodeRemoteConfigLite &config)
{
    if (!config.is_provisioned)
    {
        return false;
    }

    if (!hasCoreText(config.role) || !hasCoreText(config.hospital_name))
    {
        return false;
    }

    if (!hasCoreText(config.mqtt_host) || config.mqtt_port == 0)
    {
        return false;
    }

    if (isCheckpointRole(config.role))
    {
        return hasCoreText(config.room_name);
    }

    return isRegistrationRole(config.role);
}
