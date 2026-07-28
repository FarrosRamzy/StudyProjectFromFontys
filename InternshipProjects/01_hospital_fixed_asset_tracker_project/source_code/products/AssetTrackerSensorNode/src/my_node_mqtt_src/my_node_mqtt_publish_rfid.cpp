/**
 * @file my_node_mqtt_publish_rfid.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <ArduinoJson.h>
#include "my_node_mqtt_lib/my_node_mqtt.h"
#include "my_node_mqtt_lib/my_node_mqtt_payload_builder.h"

/**
 * @brief
 *
 * @param hospital_id
 * @param hospital_name
 * @param device_id
 * @param room_name
 * @param tag_id
 * @param timestamp
 * @return true
 * @return false
 */
bool MyNodeMQTT::publishDetection(const char *hospital_id, const char *hospital_name, const char *device_id,
                                  const char *room_name, const char *tag_id,
                                  const char *timestamp)
{
    if (!hasRequiredText(hospital_id) || !hasRequiredText(device_id) ||
        !hasRequiredText(tag_id))
    {
        Serial.println("[MQTT] Detection publish skipped: required data is missing.");
        return false;
    }

    char topic[SIZE_OF_TOPIC];
    int topic_len = snprintf(topic, sizeof(topic),
                             "%s/%s/%s/%s/%s/%s",
                             MQTT_TOPIC_ROOT,
                             hospital_id,
                             MQTT_TOPIC_NODES,
                             device_id,
                             MQTT_TOPIC_RFID,
                             MQTT_TOPIC_DETECTION);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Detection topic overflow.");
        return false;
    }

    char payload[SIZE_OF_PAYLOAD];
    JsonDocument doc;
    doc["tag_id"] = tag_id;
    doc["room_name"] = room_name ? room_name : "";
    doc["device_id"] = device_id;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["timestamp"] = timestamp ? timestamp : "";

    if (!buildJsonPayload(doc, payload, sizeof(payload)))
    {
        Serial.println("[MQTT] Detection payload overflow.");
        return false;
    }

    return publishToMyNodeNetMQTT(topic, payload);
}

/**
 * @brief
 *
 * @param hospital_id
 * @param hospital_name
 * @param device_id
 * @param tag_id
 * @param timestamp
 * @return true
 * @return false
 */
bool MyNodeMQTT::publishRegistration(const char *hospital_id, const char *hospital_name, const char *device_id,
                                     const char *tag_id,
                                     const char *timestamp)
{
    if (!hasRequiredText(hospital_id) || !hasRequiredText(device_id) ||
        !hasRequiredText(tag_id))
    {
        Serial.println("[MQTT] Registration publish skipped: required data is missing.");
        return false;
    }

    char topic[SIZE_OF_TOPIC];
    int topic_len = snprintf(topic, sizeof(topic),
                             "%s/%s/%s/%s/%s/%s",
                             MQTT_TOPIC_ROOT,
                             hospital_id,
                             MQTT_TOPIC_NODES,
                             device_id,
                             MQTT_TOPIC_RFID,
                             MQTT_TOPIC_REGISTRATION_SCAN);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Registration topic overflow.");
        return false;
    }

    char payload[SIZE_OF_PAYLOAD];
    JsonDocument doc;
    doc["tag_id"] = tag_id;
    doc["device_id"] = device_id;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["timestamp"] = timestamp ? timestamp : "";

    if (!buildJsonPayload(doc, payload, sizeof(payload)))
    {
        Serial.println("[MQTT] Registration payload overflow.");
        return false;
    }

    return publishToMyNodeNetMQTT(topic, payload);
}
