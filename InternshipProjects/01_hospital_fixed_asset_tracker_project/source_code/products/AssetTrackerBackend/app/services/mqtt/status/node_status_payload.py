"""
File: node_status_payload.py
Author: Farros Ramzy (you@domain.com)
Description: Normalizes MQTT node status payloads.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.utils import now_wib, parse_timestamp

VALID_ONLINE_STATUS = {"OK", "ONLINE"}
VALID_OFFLINE_STATUS = {"OFFLINE", "GOODBYE"}


def build_node_status_payload(payload: dict) -> dict:
    received_at = now_wib()
    timestamp = parse_timestamp(payload.get("timestamp") or received_at)

    return {
        "device_id": payload.get("device_id"),
        "hospital_id": payload.get("hospital_id", ""),
        "hospital_name": payload.get("hospital_name", ""),
        "room_name": payload.get("room_name", ""),
        "message": payload.get("message", ""),
        "received_at": received_at,
        "timestamp": timestamp,
        "status": str(payload.get("status", "")).upper(),
    }


def is_online_status(status: str) -> bool:
    return status in VALID_ONLINE_STATUS


def is_offline_status(status: str) -> bool:
    return status in VALID_OFFLINE_STATUS
