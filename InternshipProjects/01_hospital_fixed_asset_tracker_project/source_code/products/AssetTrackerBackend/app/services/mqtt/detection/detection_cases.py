"""
File: detection_cases.py
Author: Farros Ramzy (you@domain.com)
Description: Handles individual MQTT detection result cases.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.mqtt.detection.detection_broadcasts import (
    broadcast_asset_movement_completed,
    broadcast_asset_updated,
    broadcast_inactive_asset_detected,
    broadcast_unknown_node_detection,
    broadcast_unknown_tag,
)
from app.services.mqtt.detection.detection_events import create_detection_event


def handle_unknown_node_detection(context: dict) -> None:
    print(f"[MQTT] Detection from an unknown node: {context['device_id']}")

    create_detection_event(context, "UNKNOWN_NODE_DETECTION")
    broadcast_unknown_node_detection(context)


def handle_unknown_tag(context: dict) -> None:
    create_detection_event(context, "UNKNOWN_TAG")
    broadcast_unknown_tag(context)

    print(f"[MQTT] Unknown tag detected: {context['tag_id']}")


def handle_inactive_asset(context: dict, asset) -> None:
    create_detection_event(context, "INACTIVE_ASSET_DETECTED")
    broadcast_inactive_asset_detected(asset, context)

    print(f"[MQTT] Inactive asset detected: {context['tag_id']}")


def handle_stale_detection(context: dict) -> None:
    print(
        f"[MQTT] Ignored stale detection: "
        f"{context['tag_id']} at {context['room_name']} "
        f"from {context['device_id']}, "
        f"timestamp={context['timestamp'].isoformat()}"
    )


def handle_duplicate_detection(context: dict) -> None:
    print(
        f"[MQTT] Ignored duplicate detection: "
        f"{context['tag_id']} at {context['room_name']} "
        f"from {context['device_id']}, "
        f"timestamp={context['timestamp'].isoformat()}"
    )


def handle_updated_asset(context: dict, asset) -> None:
    create_detection_event(context, "DETECTION")
    broadcast_asset_updated(asset, context)

    if context.get("movement_completed"):
        broadcast_asset_movement_completed(asset, context)

    print(
        f"[MQTT] Detection updated asset: "
        f"{context['tag_id']}->{context['room_name']} ({context['device_id']})"
    )


def handle_unknown_result_status(result_status) -> None:
    print(f"[MQTT] Ignored detection with unknown result status: {result_status}")


def handle_ignored_source(reason: str, context: dict, node=None) -> None:
    if reason == "disabled_or_unprovisioned":
        print(
            f"[MQTT] Ignored detection from disabled/unprovisioned node: "
            f"{context['device_id']}"
        )
        return

    if reason == "non_checkpoint":
        print(
            f"MQTT Ignored detection from non-checkpoint node: "
            f"{context['device_id']} role={node.role}"
        )
        return

    if reason == "hospital_mismatch":
        print(
            f"[MQTT] Hospital ID mismatch for node {context['device_id']}: "
            f"topic={context['hospital_id']}, db={node.hospital_id}"
        )
