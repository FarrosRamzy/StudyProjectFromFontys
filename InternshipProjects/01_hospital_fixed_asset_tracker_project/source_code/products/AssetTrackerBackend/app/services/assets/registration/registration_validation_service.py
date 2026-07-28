"""
File: registration_validation_service.py
Author: Farros Ramzy (you@domain.com)
Description: Validation helpers for asset registration and deregistration.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from datetime import timedelta

from app.db_models import AssetEvent, Node
from app.utils import now_wib


def get_registration_node(db, registration_node_id: str):
    node = db.query(Node).filter(Node.device_id == registration_node_id).first()

    if not node:
        return None

    if not node.is_provisioned or node.status == "DISABLED":
        return None

    if node.role != "REGISTRATION":
        return None

    return node


def has_recent_registration_scan(
    db,
    tag_id: str,
    registration_node_id: str,
    max_age_seconds: int = 120,
) -> bool:
    cutoff_time = now_wib() - timedelta(seconds=max_age_seconds)

    scan = (
        db.query(AssetEvent)
        .filter(
            AssetEvent.tag_id == tag_id,
            AssetEvent.device_id == registration_node_id,
            AssetEvent.event_type == "REGISTRATION_SCAN",
            AssetEvent.timestamp >= cutoff_time,
        )
        .order_by(AssetEvent.timestamp.desc())
        .first()
    )

    return scan is not None


def validate_initial_checkpoint_node(
    db,
    initial_node_id: str,
    initial_room_name: str,
    hospital_id: str,
):
    if not initial_node_id:
        return None

    initial_node = db.query(Node).filter(Node.device_id == initial_node_id).first()

    if initial_node is None:
        return {
            "message": "registration_failed",
            "reason": "initial_node_not_found",
        }

    if not initial_node.is_provisioned:
        return {
            "message": "registration_failed",
            "reason": "initial_node_not_provisioned",
        }

    if initial_node.status == "DISABLED":
        return {
            "message": "registration_failed",
            "reason": "initial_node_disabled",
        }

    if initial_node.role != "CHECKPOINT":
        return {
            "message": "registration_failed",
            "reason": "initial_node_not_checkpoint",
        }

    if initial_node.hospital_id != hospital_id:
        return {
            "message": "registration_failed",
            "reason": "initial_node_wrong_hospital",
        }

    if initial_node.room_name and initial_node.room_name != initial_room_name:
        return {
            "message": "registration_failed",
            "reason": "initial_node_room_mismatch",
        }

    return None
