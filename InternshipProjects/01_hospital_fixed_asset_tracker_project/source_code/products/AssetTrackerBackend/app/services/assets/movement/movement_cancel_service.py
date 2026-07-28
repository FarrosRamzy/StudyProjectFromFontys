"""
File: movement_cancel_service.py
Author: Farros Ramzy (you@domain.com)
Description: Cancels pending asset movement requests.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db_models import Asset, AssetMovementRequest
from app.serializers.asset_serializer import asset_to_dict
from app.services.assets.location.asset_location_matcher import location_matches
from app.utils import now_wib


def cancel_asset_movement_request(req, user_id: int):
    db = SessionLocal()

    try:
        movement = (
            db.query(AssetMovementRequest)
            .filter(AssetMovementRequest.id == req.movement_request_id)
            .first()
        )

        if movement is None:
            return {"message": "movement_request_not_found"}

        if movement.status != "pending":
            return {"message": "movement_request_not_pending"}

        asset = db.query(Asset).filter(Asset.tag_id == movement.tag_id).first()

        if asset is None:
            return {"message": "asset_not_found"}

        if asset.status != "active":
            return {"message": "asset_not_active"}

        # Allow requester to cancel their own request.
        # Admin/registration_staff permission can still be handled in route dependencies.
        if movement.requested_by_user_id and movement.requested_by_user_id != user_id:
            return {"message": "movement_request_not_owned_by_user"}

        movement.status = "cancelled"

        # Current DB model has no cancelled_at column.
        # Reuse rejected_at as a cancellation timestamp for now.
        movement.rejected_at = now_wib()

        asset_is_at_assigned_location = location_matches(
            expected_room_name=asset.assigned_room_name,
            expected_node_id=asset.assigned_node_id,
            detected_room_name=asset.last_room_name,
            detected_node_id=asset.last_node_id,
        )

        if asset_is_at_assigned_location:
            asset.flow_status = "available"
            asset.movement_note = (
                f"Movement request was cancelled. Asset remains at "
                f"{asset.assigned_room_name or asset.last_room_name}."
            )
        else:
            asset.flow_status = "unauthorized_movement"
            asset.movement_note = (
                f"Movement request was cancelled, but asset is not at its assigned location. "
                f"Expected {asset.assigned_room_name or asset.assigned_node_id}, "
                f"currently detected at {asset.last_room_name or asset.last_node_id}."
            )

        asset.expected_room_name = ""
        asset.expected_node_id = ""
        asset.active_movement_request_id = None

        db.add(movement)
        db.add(asset)
        db.commit()
        db.refresh(asset)

        return {
            "message": "movement_cancelled",
            "asset": asset_to_dict(asset),
            "movement_request_id": movement.id,
        }

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to cancel movement request: {exc}")
        return {"message": "db_error"}

    finally:
        db.close()
