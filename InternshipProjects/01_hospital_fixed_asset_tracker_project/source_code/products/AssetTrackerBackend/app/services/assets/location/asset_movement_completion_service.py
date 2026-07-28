"""
File: asset_movement_completion_service.py
Author: Farros Ramzy (you@domain.com)
Description: Completes an approved movement request when an asset reaches its destination.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.db_models import Asset, AssetMovementRequest
from app.utils import now_wib


def complete_active_movement_request(db, asset: Asset):
    if not asset.active_movement_request_id:
        return

    movement = (
        db.query(AssetMovementRequest)
        .filter(AssetMovementRequest.id == asset.active_movement_request_id)
        .first()
    )

    if movement is None:
        return

    if movement.status == "approved":
        movement.status = "completed"
        movement.completed_at = now_wib()
        db.add(movement)
