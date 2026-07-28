"""
File: detection_payload.py
Author: Farros Ramzy (you@domain.com)
Description: Normalizes MQTT asset detection payloads.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.utils import now_wib, parse_timestamp


def build_detection_payload(payload: dict) -> dict:
    return {
        "device_id": payload.get("device_id"),
        "tag_id": payload.get("tag_id"),
        "room_name": payload.get("room_name", ""),
        "hospital_id": payload.get("hospital_id", ""),
        "hospital_name": payload.get("hospital_name", ""),
        "timestamp": parse_timestamp(payload.get("timestamp") or now_wib()),
        "raw_payload": payload,
    }


def has_required_detection_fields(detection_payload: dict) -> bool:
    return bool(detection_payload["tag_id"] and detection_payload["device_id"])
