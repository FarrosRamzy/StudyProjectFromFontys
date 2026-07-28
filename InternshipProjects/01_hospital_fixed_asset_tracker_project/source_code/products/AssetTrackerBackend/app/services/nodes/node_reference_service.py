"""
File: node_reference_service.py
Author: Farros Ramzy (you@domain.com)
Description: Prevents unassigning/removing a node while active assets or
                      movement requests still reference that node.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.db_models import Asset, AssetMovementRequest

ACTIVE_MOVEMENT_STATUSES = {"pending", "approved"}


def find_node_reference_blockers(db, device_id: str):
    assigned_assets_count = (
        db.query(Asset)
        .filter(
            Asset.status == "active",
            Asset.assigned_node_id == device_id,
        )
        .count()
    )

    expected_assets_count = (
        db.query(Asset)
        .filter(
            Asset.status == "active",
            Asset.expected_node_id == device_id,
        )
        .count()
    )

    current_location_assets_count = (
        db.query(Asset)
        .filter(
            Asset.status == "active",
            Asset.last_node_id == device_id,
        )
        .count()
    )

    active_movement_requests_count = (
        db.query(AssetMovementRequest)
        .filter(
            AssetMovementRequest.destination_node_id == device_id,
            AssetMovementRequest.status.in_(list(ACTIVE_MOVEMENT_STATUSES)),
        )
        .count()
    )

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
