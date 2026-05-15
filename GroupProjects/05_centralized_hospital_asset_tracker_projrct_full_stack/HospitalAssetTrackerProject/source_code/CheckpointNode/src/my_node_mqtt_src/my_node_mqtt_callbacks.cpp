/**
 * @file my_node_mqtt_callbacks.cpp
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
 * @param cb
 */
void MyNodeMQTT::setMessageCallback(void (*cb)(char *, uint8_t *, unsigned int))
{
    my_mqtt_callback = cb;
}

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void MyNodeMQTT::myMQTTCallbackRouter(char *topic, uint8_t *payload, unsigned int length)
{
    if (my_active_instance != nullptr)
    {
        my_active_instance->myNodeCallbackFunction(topic, payload, length);
    }
}

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void MyNodeMQTT::myNodeCallbackFunction(char *topic, uint8_t *payload, unsigned int length)
{
    if (my_mqtt_callback != nullptr)
    {
        my_mqtt_callback(topic, payload, length);
    }
}