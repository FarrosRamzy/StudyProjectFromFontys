"""
File: detection_validator.py
Author: Farros Ramzy (you@domain.com)
Description: Validates detection source node and returns trusted context.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.services.mqtt.detection.detection_cases import (
    handle_ignored_source,
    handle_unknown_node_detection,
)
from app.services.mqtt.detection.detection_context import (
    build_trusted_detection_context,
)
from app.services.mqtt.detection.detection_guard import (
    has_hospital_mismatch,
    is_disabled_or_unprovisioned_node,
    is_non_checkpoint_node,
)
from app.services.mqtt.detection.detection_repository import find_node_by_device_id


def get_valid_detection_context(detection_payload: dict):
    db = SessionLocal()

    try:
        node = find_node_by_device_id(db, detection_payload["device_id"])

        if node is None:
            handle_unknown_node_detection(detection_payload)
            return None

        if is_disabled_or_unprovisioned_node(node):
            handle_ignored_source(
                reason="disabled_or_unprovisioned",
                context=detection_payload,
            )
            return None

        if is_non_checkpoint_node(node):
            handle_ignored_source(
                reason="non_checkpoint",
                context=detection_payload,
                node=node,
            )
            return None

        if has_hospital_mismatch(node, detection_payload):
            handle_ignored_source(
                reason="hospital_mismatch",
                context=detection_payload,
                node=node,
            )
            return None

        return build_trusted_detection_context(node, detection_payload)

    finally:
        db.close()
