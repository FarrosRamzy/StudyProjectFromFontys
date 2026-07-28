/**
 * @file my_node_mqtt_payload_topics.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdio.h>
#include <string.h>

#include "node_config.h"
#include "my_node_mqtt_lib/my_node_mqtt_payload_builder.h"

bool topicWasBuilt(int topic_len, size_t topic_size);

static bool buildNodeTopic(
    const char *hospital_id,
    const char *device_id,
    const char *suffix_1,
    const char *suffix_2,
    char *topic,
    size_t topic_size)
{
    if (!hasRequiredText(hospital_id) ||
        !hasRequiredText(device_id) ||
        !hasRequiredText(suffix_1) ||
        topic == nullptr)
    {
        return false;
    }

    int len = 0;

    if (hasRequiredText(suffix_2))
    {
        len = snprintf(
            topic,
            topic_size,
            "%s/%s/%s/%s/%s/%s",
            MQTT_TOPIC_ROOT,
            hospital_id,
            MQTT_TOPIC_NODES,
            device_id,
            suffix_1,
            suffix_2);
    }
    else
    {
        len = snprintf(
            topic,
            topic_size,
            "%s/%s/%s/%s/%s",
            MQTT_TOPIC_ROOT,
            hospital_id,
            MQTT_TOPIC_NODES,
            device_id,
            suffix_1);
    }

    return topicWasBuilt(len, topic_size);
}

bool buildDetectionTopic(const char *hospital_id, const char *device_id, char *topic, size_t topic_size)
{
    return buildNodeTopic(hospital_id, device_id, MQTT_TOPIC_RFID, MQTT_TOPIC_DETECTION, topic, topic_size);
}

bool buildRegistrationTopic(const char *hospital_id, const char *device_id, char *topic, size_t topic_size)
{
    return buildNodeTopic(hospital_id, device_id, MQTT_TOPIC_RFID, MQTT_TOPIC_REGISTRATION_SCAN, topic, topic_size);
}

bool buildHeartbeatTopic(const char *hospital_id, const char *device_id, char *topic, size_t topic_size)
{
    return buildNodeTopic(hospital_id, device_id, MQTT_TOPIC_HEARTBEAT, nullptr, topic, topic_size);
}

bool buildStatusTopic(const char *hospital_id, const char *device_id, char *topic, size_t topic_size)
{
    return buildNodeTopic(hospital_id, device_id, MQTT_TOPIC_STATUS, nullptr, topic, topic_size);
}

bool buildCommandBlinkTopic(const char *hospital_id, const char *device_id, char *topic, size_t topic_size)
{
    return buildNodeTopic(hospital_id, device_id, MQTT_TOPIC_COMMANDS, MQTT_TOPIC_COMMAND_BLINK, topic, topic_size);
}