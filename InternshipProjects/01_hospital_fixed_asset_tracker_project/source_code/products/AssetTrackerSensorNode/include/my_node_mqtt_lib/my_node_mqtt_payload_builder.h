/**
 * @file my_node_mqtt_payload_builder.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-29
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <stddef.h>

bool hasRequiredText(const char *value);

bool buildDetectionTopic(
    const char *hospital_id,
    const char *device_id,
    char *topic,
    size_t topic_size);

bool buildRegistrationTopic(
    const char *hospital_id,
    const char *device_id,
    char *topic,
    size_t topic_size);

bool buildHeartbeatTopic(
    const char *hospital_id,
    const char *device_id,
    char *topic,
    size_t topic_size);

bool buildStatusTopic(
    const char *hospital_id,
    const char *device_id,
    char *topic,
    size_t topic_size);

bool buildCommandBlinkTopic(
    const char *hospital_id,
    const char *device_id,
    char *topic,
    size_t topic_size);

bool buildDetectionPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *room_name,
    const char *tag_id,
    const char *timestamp,
    char *payload,
    size_t payload_size);

bool buildRegistrationPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *tag_id,
    const char *timestamp,
    char *payload,
    size_t payload_size);

bool buildHeartbeatPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *room_name,
    const char *timestamp,
    char *payload,
    size_t payload_size);

bool buildStatusPayload(
    const char *hospital_id,
    const char *hospital_name,
    const char *device_id,
    const char *room_name,
    const char *message,
    const char *status,
    const char *timestamp,
    char *payload,
    size_t payload_size);