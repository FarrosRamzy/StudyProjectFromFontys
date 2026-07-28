"""
File: mqtt_router_payload.py
Author: Farros Ramzy (you@domain.com)
Description: Payload helpers for MQTT routing.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import json


def decode_mqtt_payload(raw_payload) -> dict | None:
    try:
        payload = json.loads(raw_payload.decode("utf-8"))
    except Exception as exc:
        print(f"[MQTT] Invalid JSON payload: {exc}")
        return None

    if not isinstance(payload, dict):
        print("[MQTT] Ignored non-object JSON payload")
        return None

    return payload


def topic_payload_match(payload: dict, topic_info: dict) -> bool:
    payload_device_id = payload.get("device_id", "")
    payload_hospital_id = payload.get("hospital_id", "")

    if payload_device_id and payload_device_id != topic_info["device_id"]:
        print("[MQTT] Device ID mismatch between topic and payload")
        return False

    if payload_hospital_id and payload_hospital_id != topic_info["hospital_id"]:
        print("[MQTT] Hospital ID mismatch between topic and payload")
        return False

    return True


def apply_topic_identity(payload: dict, topic_info: dict) -> dict:
    payload["device_id"] = topic_info["device_id"]
    payload["hospital_id"] = topic_info["hospital_id"]
    return payload
