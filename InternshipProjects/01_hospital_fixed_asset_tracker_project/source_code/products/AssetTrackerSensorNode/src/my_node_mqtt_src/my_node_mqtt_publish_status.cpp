/**
 * @file my_node_mqtt_publish_status.cpp
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
 * @param timestamp
 * @return true
 * @return false
 */
bool MyNodeMQTT::publishHeartbeat(const char *hospital_id, const char *hospital_name,
                                  const char *device_id, const char *room_name,
                                  const char *timestamp)
{
    if (!hasRequiredText(hospital_id) || !hasRequiredText(device_id))
    {
        Serial.println("[MQTT] Heartbeat publish skipped: required data is missing.");
        return false;
    }

    char topic[SIZE_OF_TOPIC];
    int topic_len = snprintf(topic, sizeof(topic),
                             "%s/%s/%s/%s/%s",
                             MQTT_TOPIC_ROOT,
                             hospital_id,
                             MQTT_TOPIC_NODES,
                             device_id,
                             MQTT_TOPIC_HEARTBEAT);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Heartbeat topic overflow.");
        return false;
    }

    char payload[SIZE_OF_PAYLOAD];
    JsonDocument doc;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["room_name"] = room_name ? room_name : "";
    doc["device_id"] = device_id;
    doc["timestamp"] = timestamp ? timestamp : "";
    doc["status"] = "OK";
    doc["message"] = "heartbeat";

    if (!buildJsonPayload(doc, payload, sizeof(payload)))
    {
        Serial.println("[MQTT] Heartbeat payload overflow.");
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
 * @param room_name
 * @param message
 * @param status
 * @param timestamp
 * @return true
 * @return false
 */
bool MyNodeMQTT::publishGreeting(const char *hospital_id, const char *hospital_name, const char *device_id,
                                 const char *room_name, const char *message,
                                 const char *status, const char *timestamp)
{
    if (!hasRequiredText(hospital_id) || !hasRequiredText(device_id) ||
        !hasRequiredText(status))
    {
        Serial.println("[MQTT] Status publish skipped: required data is missing.");
        return false;
    }

    char topic[SIZE_OF_TOPIC];
    int topic_len = snprintf(topic, sizeof(topic),
                             "%s/%s/%s/%s/%s",
                             MQTT_TOPIC_ROOT,
                             hospital_id,
                             MQTT_TOPIC_NODES,
                             device_id,
                             MQTT_TOPIC_STATUS);

    if (topic_len <= 0 || topic_len >= (int)sizeof(topic))
    {
        Serial.println("[MQTT] Status topic overflow.");
        return false;
    }

    char payload[SIZE_OF_PAYLOAD];
    JsonDocument doc;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["room_name"] = room_name ? room_name : "";
    doc["device_id"] = device_id;
    doc["message"] = message ? message : "";
    doc["status"] = status;
    doc["timestamp"] = timestamp ? timestamp : "";

    if (!buildJsonPayload(doc, payload, sizeof(payload)))
    {
        Serial.println("[MQTT] Status payload overflow.");
        return false;
    }

    return publishToMyNodeNetMQTT(topic, payload);
}
