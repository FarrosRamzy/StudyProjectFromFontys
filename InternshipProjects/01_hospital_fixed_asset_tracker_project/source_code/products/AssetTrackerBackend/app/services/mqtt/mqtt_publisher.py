"""
File: mqtt_publisher.py
Author: Farros Ramzy (you@domain.com)
Description: MQTT command publishers.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from __future__ import annotations

import json
import time
from typing import Any

import paho.mqtt.client as my_mqtt

from app.services.mqtt.settings.mqtt_settings_service import get_active_mqtt_settings
from app.services.mqtt.mqtt_topics import build_node_command_topic
from app.services.mqtt.mqtt_worker import get_mqtt_client


def publish_node_blink_command(
    hospital_id: str,
    device_id: str,
    blink_count: int = 6,
    interval_ms: int = 150,
) -> dict[str, Any]:
    settings = get_active_mqtt_settings()
    clean_hospital_id = str(hospital_id or "").strip()
    clean_device_id = str(device_id or "").strip()

    if not clean_hospital_id or not clean_device_id:
        return {"ok": False, "message": "missing_hospital_or_device_id"}

    if clean_hospital_id != settings.hospital_id:
        return {
            "ok": False,
            "message": "hospital_topic_namespace_mismatch",
            "expected_hospital_id": settings.hospital_id,
            "received_hospital_id": clean_hospital_id,
        }

    client = get_mqtt_client()

    if client is None or not client.is_connected():
        return {"ok": False, "message": "mqtt_not_connected"}

    return publish_blink_payload(
        client=client,
        settings=settings,
        device_id=clean_device_id,
        blink_count=blink_count,
        interval_ms=interval_ms,
    )


def publish_blink_payload(
    client,
    settings,
    device_id: str,
    blink_count: int,
    interval_ms: int,
) -> dict[str, Any]:
    topic = build_node_command_topic(settings, device_id, "blink")
    command_id = f"blink-{device_id}-{int(time.time() * 1000)}"
    payload = {
        "command": "blink",
        "command_id": command_id,
        "device_id": device_id,
        "hospital_id": settings.hospital_id,
        "blink_count": blink_count,
        "interval_ms": interval_ms,
    }
    publish_result = client.publish(topic, json.dumps(payload), qos=1, retain=False)

    if publish_result.rc != my_mqtt.MQTT_ERR_SUCCESS:
        return {
            "ok": False,
            "message": "mqtt_publish_failed",
            "result_code": publish_result.rc,
        }

    return {
        "ok": True,
        "message": "blink_command_published",
        "command_id": command_id,
        "topic": topic,
        "payload": payload,
    }
