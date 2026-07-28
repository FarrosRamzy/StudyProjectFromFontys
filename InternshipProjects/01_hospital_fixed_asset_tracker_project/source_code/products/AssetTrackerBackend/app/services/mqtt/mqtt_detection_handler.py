"""
File: mqtt_detection_handler.py
Author: Farros Ramzy (you@domain.com)
Description: Coordinates MQTT asset detection handling.
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.services.assets.location.asset_location_update_service import (
    update_asset_location,
)
from app.services.mqtt.detection.detection_dispatcher import dispatch_detection_result
from app.services.mqtt.detection.detection_payload import (
    build_detection_payload,
    has_required_detection_fields,
)
from app.services.mqtt.detection.detection_validator import get_valid_detection_context


def handle_detection(payload: dict) -> None:
    detection_payload = build_detection_payload(payload)

    if not has_required_detection_fields(detection_payload):
        print("[MQTT] Detection payload missing tag_id or device_id")
        return

    context = get_valid_detection_context(detection_payload)

    if context is None:
        return

    result = update_asset_location(
        tag_id=context["tag_id"],
        device_id=context["device_id"],
        room_name=context["room_name"],
        hospital_id=context["hospital_id"],
        hospital_name=context["hospital_name"],
        timestamp=context["timestamp"],
    )

    dispatch_detection_result(result, context)
