"""
File: movement_decision_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Database helpers for movement approval and rejection.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.db.asset_db_model import Asset
from app.db.asset_movement_request_db_model import AssetMovementRequest
from app.db.node_db_model import Node


def find_registration_node(db, registration_node_id: str):
    return db.query(Node).filter(Node.device_id == registration_node_id).first()


def find_movement_request(db, movement_request_id: int):
    return (
        db.query(AssetMovementRequest)
        .filter(AssetMovementRequest.id == movement_request_id)
        .first()
    )


def find_asset_for_movement(db, movement: AssetMovementRequest):
    return db.query(Asset).filter(Asset.tag_id == movement.tag_id).first()


def cancel_other_pending_movement_requests(
    db, movement: AssetMovementRequest, cancelled_at
):
    (
        db.query(AssetMovementRequest)
        .filter(
            AssetMovementRequest.tag_id == movement.tag_id,
            AssetMovementRequest.id != movement.id,
            AssetMovementRequest.status == "pending",
        )
        .update(
            {
                AssetMovementRequest.status: "cancelled",
                AssetMovementRequest.rejected_at: cancelled_at,
            },
            synchronize_session=False,
        )
    )


def save_movement_decision(db, movement: AssetMovementRequest, asset: Asset):
    db.add(movement)
    db.add(asset)
    db.commit()
    db.refresh(asset)

    return asset
