/**
 * @file my_node_mqtt_connection.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_mqtt_lib/my_node_mqtt.h"

/**
 * @brief
 *
 */
void MyNodeMQTT::connectToMyNodeNetwork()
{
    if (my_node_net_server == nullptr || my_node_net_server[0] == '\0')
    {
        Serial.println("[MQTT] Connect skipped: broker host is empty.");
        return;
    }

    if (my_node_net_id == nullptr || my_node_net_id[0] == '\0')
    {
        Serial.println("[MQTT] Connect skipped: client ID is empty.");
        return;
    }

    Serial.print("[MQTT] Connecting to ");
    Serial.print(my_node_net_server);
    Serial.print(":");
    Serial.print(my_node_net_port);
    Serial.print(" as ");
    Serial.println(my_node_net_id);

    bool ok = my_node_mqtt_client.connect(my_node_net_id);

    if (ok)
    {
        Serial.println("[MQTT] Connected.");
    }
    else
    {
        Serial.print("[MQTT] Connect failed, state = ");
        Serial.println(my_node_mqtt_client.state());
    }
}

/**
 * @brief
 *
 */
void MyNodeMQTT::myNodeMQTTLoop()
{
    my_node_mqtt_client.loop();
}

/**
 * @brief
 *
 */
void MyNodeMQTT::reconnectToMyMQTT()
{
    if (amIConnected())
    {
        return;
    }

    uint32_t now = millis();

    if ((uint32_t)(now - last_reconnect_attempt) < reconnect_interval)
    {
        return;
    }

    last_reconnect_attempt = now;
    connectToMyNodeNetwork();
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeMQTT::amIConnected()
{
    return my_node_mqtt_client.connected();
}
