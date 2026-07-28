/**
 * @file my_node_network_config_status.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief
 *
 * @return String
 */
String MyNodeNetworkConfig::generateDeviceId() const
{
    uint64_t chip_id = ESP.getEfuseMac();

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "%s-%04X%08X", MY_DEFAULT_DEVICE_ID_FORMAT,
             (uint16_t)(chip_id >> 32), (uint32_t)chip_id);

    return String(buffer);
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeNetworkConfig::isConfigured() const
{
    return my_bootstrap_config.is_configured;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeNetworkConfig::isSetupMode() const
{
    return my_setup_mode;
}

/**
 * @brief
 *
 * @return const myNodeBootstrapConfig&
 */
const myNodeBootstrapConfig &MyNodeNetworkConfig::getBootstrapConfig() const
{
    return my_bootstrap_config;
}

/**
 * @brief
 *
 * @return const myNodeRemoteConfig&
 */
const myNodeRemoteConfig &MyNodeNetworkConfig::getRemoteConfig() const
{
    return my_remote_config;
}
