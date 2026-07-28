"""
File: movement_request_create_service.py
Author: Farros Ramzy (you@domain.com)
Description: Creates asset movement requests.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from sqlalchemy.exc import SQLAlchemyError

from app.database import SessionLocal
from app.db_models import Asset, AssetMovementRequest, Node
from app.serializers.asset_serializer import asset_to_dict
from app.utils import now_wib


def create_asset_movement_request(req, user_id: int):
    db = SessionLocal()

    try:
        asset = db.query(Asset).filter(Asset.tag_id == req.tag_id).first()

        if asset is None:
            return {"message": "asset_not_found"}

        if asset.status != "active":
            return {"message": "asset_not_active"}

        existing_active_request = (
            db.query(AssetMovementRequest)
            .filter(
                AssetMovementRequest.tag_id == req.tag_id,
                AssetMovementRequest.status.in_(["pending", "approved"]),
            )
            .first()
        )

        if existing_active_request is not None:
            return {
                "message": "movement_request_already_exists",
                "reason": "asset_already_has_active_movement_request",
                "movement_request_id": existing_active_request.id,
                "status": existing_active_request.status,
            }

        if asset.flow_status in {
            "pending_placement",
            "movement_requested",
            "in_transit",
            "wrong_location",
            "unauthorized_movement",
        }:
            return {
                "message": "asset_not_available_for_movement",
                "flow_status": asset.flow_status,
                "reason": "asset_must_be_resolved_before_new_movement_request",
            }

        destination_room_name = req.destination_room_name.strip()

        if not destination_room_name:
            return {"message": "destination_room_required"}

        destination_node = None
        if req.destination_node_id:
            destination_node = (
                db.query(Node).filter(Node.device_id == req.destination_node_id).first()
            )

            if destination_node is None:
                return {"message": "destination_node_not_found"}

            if not destination_node.is_provisioned:
                return {"message": "destination_node_not_provisioned"}

            if destination_node.status == "DISABLED":
                return {"message": "destination_node_disabled"}

            if destination_node.role != "CHECKPOINT":
                return {"message": "destination_node_not_checkpoint"}

            if destination_node.hospital_id != asset.hospital_id:
                return {"message": "destination_node_wrong_hospital"}

            if (
                destination_node.room_name
                and destination_node.room_name != destination_room_name
            ):
                return {"message": "destination_node_room_mismatch"}

        if asset.last_room_name == destination_room_name:
            return {"message": "destination_same_as_current_location"}

        movement = AssetMovementRequest(
            hospital_id=asset.hospital_id or "",
            hospital_name=asset.hospital_name or "",
            tag_id=asset.tag_id,
            item_name=asset.item_name or "",
            from_room_name=asset.assigned_room_name or asset.last_room_name or "",
            from_node_id=asset.assigned_node_id or asset.last_node_id or "",
            destination_room_name=destination_room_name,
            destination_node_id=req.destination_node_id or "",
            status="pending",
            requested_by_user_id=user_id,
            requested_at=now_wib(),
            note=req.note or "",
        )

        db.add(movement)
        db.flush()

        asset.flow_status = "movement_requested"
        asset.expected_room_name = destination_room_name
        asset.expected_node_id = req.destination_node_id or ""
        asset.active_movement_request_id = movement.id
        asset.movement_note = (
            "Movement request is waiting for registration desk approval."
        )

        db.add(asset)
        db.commit()
        db.refresh(asset)

        return {
            "message": "movement_requested",
            "asset": asset_to_dict(asset),
            "movement_request_id": movement.id,
        }

    except SQLAlchemyError as exc:
        db.rollback()
        print(f"[DB] Failed to create movement request: {exc}")
        return {"message": "db_error"}

    finally:
        db.close()
