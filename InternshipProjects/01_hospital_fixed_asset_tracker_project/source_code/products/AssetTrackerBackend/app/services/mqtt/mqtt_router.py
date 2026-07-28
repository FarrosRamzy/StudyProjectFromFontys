"""
File: mqtt_router.py
Author: Farros Ramzy (you@domain.com)
Description: Routes MQTT messages to the correct backend domain handler.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from __future__ import annotations

from typing import Any

import paho.mqtt.client as my_mqtt

from app.services.mqtt.mqtt_router_dispatcher import dispatch_mqtt_message
from app.services.mqtt.mqtt_router_payload import (
    apply_topic_identity,
    decode_mqtt_payload,
    topic_payload_match,
)
from app.services.mqtt.settings.mqtt_settings_service import get_active_mqtt_settings
from app.services.mqtt.mqtt_topics import get_mqtt_subscribe_topics, parse_mqtt_topic


def get_callback_settings(user_data: Any):
    if isinstance(user_data, dict) and user_data.get("settings"):
        return user_data["settings"]

    return get_active_mqtt_settings()


def on_connect(
    client: my_mqtt.Client,
    user_data: Any,
    flags: dict[str, Any],
    reason_code: Any,
    properties: Any = None,
) -> None:
    settings = get_callback_settings(user_data)

    print(f"[MQTT] Connected with reason code: {reason_code}")
    print(f"[MQTT] Namespace: {settings.topic_namespace}")

    for topic in get_mqtt_subscribe_topics(settings):
        client.subscribe(topic)
        print(f"[MQTT] Subscribed: {topic}")


def on_message(
    client: my_mqtt.Client,
    user_data: Any,
    msg: my_mqtt.MQTTMessage,
) -> None:
    settings = get_callback_settings(user_data)
    topic_info = parse_mqtt_topic(msg.topic, settings)

    if topic_info is None:
        print(f"[MQTT] Ignored invalid or foreign topic: {msg.topic}")
        return

    payload = decode_mqtt_payload(msg.payload)

    if payload is None or not topic_payload_match(payload, topic_info):
        return

    payload = apply_topic_identity(payload, topic_info)
    print("[MQTT] Topic:", msg.topic)
    print("[MQTT] Parsed:", topic_info)
    print("[MQTT] Payload:", payload)

    try:
        dispatch_mqtt_message(topic_info, payload, settings)

    except Exception as exc:
        print(f"[MQTT] Handler error for topic {msg.topic}: {exc}")
