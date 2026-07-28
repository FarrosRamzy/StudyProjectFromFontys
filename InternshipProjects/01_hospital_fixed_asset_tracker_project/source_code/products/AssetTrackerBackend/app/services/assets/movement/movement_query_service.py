"""
File: movement_query_service.py
Author: Farros Ramzy (you@domain.com)
Description: Lists asset movement requests.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import AssetMovementRequest
from app.services.assets.movement.movement_serializer import movement_request_to_dict


def list_asset_movement_requests(status: str = ""):
    db = SessionLocal()

    try:
        query = db.query(AssetMovementRequest)

        if status:
            query = query.filter(AssetMovementRequest.status == status)

        movements = query.order_by(AssetMovementRequest.requested_at.desc()).all()

        return [movement_request_to_dict(movement) for movement in movements]

    finally:
        db.close()
