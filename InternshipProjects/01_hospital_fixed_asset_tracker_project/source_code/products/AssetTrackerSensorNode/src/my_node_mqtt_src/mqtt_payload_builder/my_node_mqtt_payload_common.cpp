/**
 * @file my_node_mqtt_payload_common.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-03
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <ArduinoJson.h>
#include <stdio.h>
#include <string.h>

#include "node_config.h"
#include "my_node_mqtt_lib/my_node_mqtt_payload_builder.h"

bool hasRequiredText(const char *value)
{
    return value != nullptr && value[0] != '\0';
}

bool topicWasBuilt(int topic_len, size_t topic_size)
{
    return topic_len > 0 && topic_len < (int)topic_size;
}

bool buildJsonPayload(JsonDocument &doc, char *payload, size_t payload_size)
{
    if (payload == nullptr || payload_size == 0)
    {
        return false;
    }

    size_t written = serializeJson(doc, payload, payload_size);
    return written > 0 && written < payload_size;
}