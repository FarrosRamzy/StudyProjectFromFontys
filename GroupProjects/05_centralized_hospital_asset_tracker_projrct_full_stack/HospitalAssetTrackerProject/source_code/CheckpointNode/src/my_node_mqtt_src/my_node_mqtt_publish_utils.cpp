/**
 * @file my_node_mqtt_publish_utils.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_mqtt_lib/my_node_mqtt.h"

bool MyNodeMQTT::hasRequiredText(const char *value)
{
    return value != nullptr && value[0] != '\0';
}

bool MyNodeMQTT::topicWasBuilt(int topic_len, size_t topic_size)
{
    return topic_len > 0 && topic_len < (int)topic_size;
}

bool MyNodeMQTT::buildJsonPayload(JsonDocument &doc, char *payload, size_t payload_size)
{
    size_t written = serializeJson(doc, payload, payload_size);
    return written > 0 && written < payload_size;
}