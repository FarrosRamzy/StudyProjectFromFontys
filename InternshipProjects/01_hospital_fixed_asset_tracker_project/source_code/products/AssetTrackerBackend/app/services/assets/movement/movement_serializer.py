"""
File: movement_serializer.py
Author: Farros Ramzy
Description: Serializes asset movement requests.
Version: 0.2
"""

from app.db_models import AssetMovementRequest
from app.utils import to_wib_iso


def movement_request_to_dict(movement: AssetMovementRequest):
    return {
        "id": movement.id,
        "hospital_id": movement.hospital_id or "",
        "hospital_name": movement.hospital_name or "",
        "tag_id": movement.tag_id or "",
        "item_name": movement.item_name or "",
        "from_room_name": movement.from_room_name or "",
        "from_node_id": movement.from_node_id or "",
        "destination_room_name": movement.destination_room_name or "",
        "destination_node_id": movement.destination_node_id or "",
        "status": movement.status or "",
        "requested_by_user_id": movement.requested_by_user_id,
        "approved_by_user_id": movement.approved_by_user_id,
        "requested_at": to_wib_iso(movement.requested_at),
        "approved_at": to_wib_iso(movement.approved_at),
        "completed_at": to_wib_iso(movement.completed_at),
        "rejected_at": to_wib_iso(movement.rejected_at),
        "note": movement.note or "",
    }