/**
 * @file node_manager_core_loop.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 */
void NodeManager::runNodeSystem()
{
    handleConfigResetButton();

    if (my_node_net_config.isSetupMode())
    {
        static uint32_t last_print = 0;
        uint32_t now = my_clock.millisNow();
        if ((uint32_t)(now - last_print) > 2000)
        {
            Serial.println("[SYSTEM] setup loop running...");
            last_print = now;
        }

        my_node_net_config.loopMyNetConfig();
        return;
    }

    my_node_wi_fi.loopNetWiFi();

    if (my_node_wi_fi.amIConnected())
    {
        updateTimeSync();
    }

    if (my_node_wi_fi.amIConnected() && !my_node_is_provisioned)
    {
        static uint32_t last_try = 0;
        uint32_t now = my_clock.millisNow();

        if ((uint32_t)(now - last_try) > NET_RECONNECT_INTERVAL_MS)
        {
            Serial.println("[SYSTEM] Attempting provisioning...");

            if (fetchRemoteConfig())
            {
                applyRemoteConfig();

                my_node_rfid.beginMyNodeRFID(RFID_BAUDRATE);
                my_node_rfid.clearBuffer();
                my_node_rfid.configureRFID();
            }

            last_try = now;
        }

        my_node_status_led.setGreenConnected(false);
        my_node_status_led.updateMyLEDstate();
        return;
    }

    checkRemoteConfigPeriodically();

    bool mqtt_connected_now = false;

    if (my_node_wi_fi.amIConnected() && my_node_is_provisioned)
    {
        if (my_hospital_id.length() == 0 || my_node_id.length() == 0)
        {
            Serial.println("[MQTT] Skipped: missing hospital ID or node ID.");
        }
        else
        {
            my_node_mqtt.reconnectToMyMQTT();

            mqtt_connected_now = my_node_mqtt.amIConnected();

            if (mqtt_connected_now)
            {
                my_node_mqtt.myNodeMQTTLoop();
            }

            if (!last_mqtt_connected && mqtt_connected_now)
            {
                Serial.println("[MQTT] Reconnected. Resetting command subscription state.");
                my_commands_subscribed = false;
                last_command_subs_attempt = 0;
                sayHello();
            }

            if (mqtt_connected_now && !my_commands_subscribed)
            {
                uint32_t now = my_clock.millisNow();

                if ((uint32_t)(now - last_command_subs_attempt) >= 1000)
                {
                    last_command_subs_attempt = now;
                    subscribeToCommandTopics();
                    my_node_mqtt.myNodeMQTTLoop();
                }
            }
        }
    }

    last_mqtt_connected = mqtt_connected_now;
    if (!mqtt_connected_now)
    {
        my_commands_subscribed = false;
        last_command_subs_attempt = 0;
    }

    my_node_status_led.setGreenConnected(my_node_mqtt.amIConnected());

    if (mqtt_connected_now)
    {
        handleRFID();
        handleHeartbeat();
    }

    my_node_status_led.updateMyLEDstate();
}
