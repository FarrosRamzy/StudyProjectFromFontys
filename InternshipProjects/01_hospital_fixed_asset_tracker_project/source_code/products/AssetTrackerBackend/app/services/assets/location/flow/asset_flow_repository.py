"""
File: asset_flow_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Database helpers for asset flow resolution.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.db.asset_movement_request_db_model import AssetMovementRequest


def find_active_movement_request(db, movement_request_id):
    if not movement_request_id:
        return None

    return (
        db.query(AssetMovementRequest)
        .filter(AssetMovementRequest.id == movement_request_id)
        .first()
    )
