"""
File: detection_events.py
Author: Farros Ramzy (you@domain.com)
Description: Asset event helpers for MQTT detections.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.assets.asset_event_service import create_asset_event


def create_detection_event(context: dict, event_type: str):
    return create_asset_event(
        tag_id=context["tag_id"],
        device_id=context["device_id"],
        hospital_id=context["hospital_id"],
        room_name=context["room_name"],
        hospital_name=context["hospital_name"],
        event_type=event_type,
        raw_payload=context["raw_payload"],
        timestamp=context["timestamp"],
    )
