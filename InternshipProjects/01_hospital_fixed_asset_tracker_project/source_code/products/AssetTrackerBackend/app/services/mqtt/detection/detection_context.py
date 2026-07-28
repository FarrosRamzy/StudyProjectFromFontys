"""
File: detection_context.py
Author: Farros Ramzy (you@domain.com)
Description: Builds trusted detection context from the database
             node record.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""


def build_trusted_detection_context(node, detection_payload: dict) -> dict:
    return {
        "tag_id": detection_payload["tag_id"],
        "device_id": detection_payload["device_id"],
        "room_name": node.room_name or detection_payload["room_name"],
        "hospital_id": node.hospital_id or detection_payload["hospital_id"],
        "hospital_name": node.hospital_name or detection_payload["hospital_name"],
        "timestamp": detection_payload["timestamp"],
        "raw_payload": detection_payload["raw_payload"],
    }
