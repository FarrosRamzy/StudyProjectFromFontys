"""
File: node_assignment_blockers.py
Author: Farros Ramzy (you@domain.com)
Description: Finds active records that block node re-assignment.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.asset_db_model import Asset
from app.db.asset_movement_request_db_model import AssetMovementRequest

ACTIVE_MOVEMENT_STATUSES = {"pending", "approved"}


def find_node_reassignment_blockers(db, device_id: str) -> dict:
    assigned_assets_count = _count_assigned_assets(db, device_id)
    expected_assets_count = _count_expected_assets(db, device_id)
    current_location_assets_count = _count_current_location_assets(db, device_id)
    active_movement_requests_count = _count_active_movement_requests(db, device_id)

    return {
        "assigned_assets_count": assigned_assets_count,
        "expected_assets_count": expected_assets_count,
        "current_location_assets_count": current_location_assets_count,
        "active_movement_requests_count": active_movement_requests_count,
        "total": (
            assigned_assets_count
            + expected_assets_count
            + current_location_assets_count
            + active_movement_requests_count
        ),
    }


def _count_assigned_assets(db, device_id: str) -> int:
    return _count_active_assets_by_field(db, Asset.assigned_node_id, device_id)


def _count_expected_assets(db, device_id: str) -> int:
    return _count_active_assets_by_field(db, Asset.expected_node_id, device_id)


def _count_current_location_assets(db, device_id: str) -> int:
    return _count_active_assets_by_field(db, Asset.last_node_id, device_id)


def _count_active_assets_by_field(db, field, device_id: str) -> int:
    return (
        db.query(Asset)
        .filter(
            Asset.status == "active",
            field == device_id,
        )
        .count()
    )


def _count_active_movement_requests(db, device_id: str) -> int:
    return (
        db.query(AssetMovementRequest)
        .filter(
            AssetMovementRequest.destination_node_id == device_id,
            AssetMovementRequest.status.in_(list(ACTIVE_MOVEMENT_STATUSES)),
        )
        .count()
    )
