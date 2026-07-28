/**
 * @file my_node_mqtt_payload_status.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <ArduinoJson.h>

#include "node_config.h"
#include "my_node_mqtt_lib/my_node_mqtt_payload_builder.h"

bool buildJsonPayload(JsonDocument &doc, char *payload, size_t payload_size);

bool buildHeartbeatPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *room_name,
    const char *timestamp,
    char *payload,
    size_t payload_size)
{
    if (!hasRequiredText(hospital_id) || !hasRequiredText(device_id))
    {
        return false;
    }

    JsonDocument doc;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["room_name"] = room_name ? room_name : "";
    doc["device_id"] = device_id;
    doc["timestamp"] = timestamp ? timestamp : "";
    doc["status"] = "OK";
    doc["message"] = "heartbeat";

    return buildJsonPayload(doc, payload, payload_size);
}

bool buildStatusPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *room_name,
    const char *message,
    const char *status,
    const char *timestamp,
    char *payload,
    size_t payload_size)
{
    if (!hasRequiredText(hospital_id) ||
        !hasRequiredText(device_id) ||
        !hasRequiredText(status))
    {
        return false;
    }

    JsonDocument doc;
    doc["hospital_id"] = hospital_id;
    doc["hospital_name"] = hospital_name ? hospital_name : "";
    doc["room_name"] = room_name ? room_name : "";
    doc["device_id"] = device_id;
    doc["message"] = message ? message : "";
    doc["status"] = status;
    doc["timestamp"] = timestamp ? timestamp : "";

    return buildJsonPayload(doc, payload, payload_size);
}