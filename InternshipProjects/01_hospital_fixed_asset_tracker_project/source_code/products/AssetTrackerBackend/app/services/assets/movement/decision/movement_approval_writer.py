"""
File: movement_approval_writer.py
Author: Farros Ramzy (you@domain.com)
Description: Applies approval changes to movement and asset records.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.movement.decision.movement_decision_repository import (
    cancel_other_pending_movement_requests,
)
from app.utils import now_wib


def approve_movement(db, movement, asset, user_id: int) -> None:
    approved_at = now_wib()

    movement.status = "approved"
    movement.approved_by_user_id = user_id
    movement.approved_at = approved_at

    cancel_other_pending_movement_requests(
        db=db,
        movement=movement,
        cancelled_at=approved_at,
    )

    asset.flow_status = "in_transit"
    asset.expected_room_name = movement.destination_room_name
    asset.expected_node_id = movement.destination_node_id or ""
    asset.active_movement_request_id = movement.id
    asset.movement_note = f"Approved for movement to {movement.destination_room_name}."
