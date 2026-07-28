"""
File: node_command_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Node command routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.database import SessionLocal
from app.db_models import Node, User
from app.models import IdentifyNodeRequest
from app.serializers.node_serializer import node_to_dict
from app.services.authority.auth_dependencies import require_role
from app.services.mqtt.mqtt_client import publish_node_blink_command
from app.websocket_manager import ws_manager

router = APIRouter(tags=["nodes"])


@router.post("/nodes/{device_id}/identify")
async def identify_node(
    device_id: str,
    req: IdentifyNodeRequest,
    current_user: User = Depends(require_role("admin", "test_user", "technician")),
):
    db = SessionLocal()

    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if node is None:
            return {
                "message": "node_not_found",
                "device_id": device_id,
            }

        if not node.is_provisioned:
            return {
                "message": "node_not_provisioned",
                "node": node_to_dict(node),
            }

        node_status = str(node.status or "").strip().upper()

        if node_status == "DISABLED":
            return {
                "message": "node_disabled",
                "node": node_to_dict(node),
            }

        if node_status == "OFFLINE":
            return {
                "message": "node_offline",
                "node": node_to_dict(node),
            }

        if not node.hospital_id:
            return {
                "message": "node_missing_hospital_id",
                "node": node_to_dict(node),
            }

        publish_result = publish_node_blink_command(
            hospital_id=node.hospital_id,
            device_id=node.device_id,
            blink_count=req.blink_count,
            interval_ms=req.interval_ms,
        )

        if not publish_result.get("ok"):
            return {
                "message": publish_result.get("message", "blink_command_failed"),
                "node": node_to_dict(node),
                "publish": publish_result,
            }

        await ws_manager.broadcast_json(
            {
                "type": "node_identify_requested",
                "device_id": node.device_id,
                "node": node_to_dict(node),
            }
        )

        return {
            "message": "blink_command_sent",
            "node": node_to_dict(node),
            "publish": publish_result,
        }

    finally:
        db.close()
