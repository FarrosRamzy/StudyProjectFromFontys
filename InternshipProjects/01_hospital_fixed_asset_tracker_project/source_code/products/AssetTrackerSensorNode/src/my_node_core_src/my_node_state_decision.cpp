/**
 * @file my_node_state_decision.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_core_lib/my_node_state_decision.h"

MyNodeAction decideNextNodeAction(
    bool wifi_connected,
    bool provisioned,
    bool mqtt_connected,
    bool heartbeat_due)
{
    if (!wifi_connected)
    {
        return ACTION_TRY_WIFI;
    }

    if (!provisioned)
    {
        return ACTION_TRY_PROVISION;
    }

    if (!mqtt_connected)
    {
        return ACTION_TRY_MQTT;
    }

    if (heartbeat_due)
    {
        return ACTION_PUBLISH_HEARTBEAT;
    }

    return ACTION_READ_RFID;
}
