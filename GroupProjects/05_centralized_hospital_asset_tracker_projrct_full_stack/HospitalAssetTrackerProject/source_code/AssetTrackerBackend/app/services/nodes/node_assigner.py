"""
File: node_assigner.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Node
from app.utils import now_wib
from app.serializers.node_serializer import node_to_dict


def assign_node_record(device_id: str, req):
    db = SessionLocal()
    try:
        node = db.query(Node).filter(Node.device_id == device_id).first()

        if not node:
            node = Node(
                device_id=device_id,
                role="",
                hospital_id="",
                hospital_name="",
                room_name="",
                mqtt_host="",
                mqtt_port=1883,
                is_provisioned=False,
                status="DISCOVERED",
                last_ping_at=None,
                last_event_at=now_wib(),
                last_message="created during assignment",
            )

        role = req.role.strip().upper()

        if role not in {"CHECKPOINT", "REGISTRATION"}:
            return {"message": "invalid_role"}

        if role == "CHECKPOINT" and not req.room_name.strip():
            return {"message": "room_required_for_checkpoint"}
        
        room_name = req.room_name.strip()

        if role == "REGISTRATION":
            room_name = ""

        node.alias = req.alias.strip()
        node.role = role
        node.hospital_id = req.hospital_id.strip()
        node.hospital_name = req.hospital_name.strip()
        node.room_name = room_name
        node.mqtt_host = req.mqtt_host.strip()
        node.mqtt_port = req.mqtt_port
        node.is_provisioned = True
        node.status = "ASSIGNED"
        node.last_event_at = now_wib()
        node.last_message = "configuration assigned"

        db.add(node)
        db.commit()
        db.refresh(node)
        return {"message": "node_assigned", "node": node_to_dict(node)}

    finally:
        db.close()
