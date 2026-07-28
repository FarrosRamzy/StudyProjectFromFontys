/**
 * @file i_my_node_network_config.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "my_node_network_lib/structs/my_node_network_types.h"

class IMyNodeNetworkConfig
{
public:
    virtual ~IMyNodeNetworkConfig() {}

    virtual void beginMyNetConfig() = 0;
    virtual void loopMyNetConfig() = 0;

    virtual bool isConfigured() const = 0;
    virtual bool isSetupMode() const = 0;

    virtual const myNodeBootstrapConfig &getBootstrapConfig() const = 0;
    virtual const myNodeRemoteConfig &getRemoteConfig() const = 0;

    virtual void setRemoteConfig(const String &, const String &, const String &, const String &, uint16_t, bool) = 0;

    virtual void resetConfiguration() = 0;
};
