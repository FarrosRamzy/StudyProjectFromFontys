"""
File: node_assignment_payload.py
Author: Farros Ramzy (you@domain.com)
Description: Builds validated node assignment payloads.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.services.mqtt.settings.mqtt_settings_service import get_active_mqtt_settings

VALID_NODE_ROLES = {"CHECKPOINT", "REGISTRATION"}


def build_node_assignment_payload(req):
    settings = get_active_mqtt_settings()
    role = req.role.strip().upper()
    hospital_id = req.hospital_id.strip()

    if role not in VALID_NODE_ROLES:
        return None, {"message": "invalid_role"}

    if hospital_id != settings.hospital_id:
        return None, {
            "message": "hospital_id_must_match_mqtt_namespace",
            "expected_hospital_id": settings.hospital_id,
            "received_hospital_id": hospital_id,
        }

    if role == "CHECKPOINT" and not req.room_name.strip():
        return None, {"message": "room_required_for_checkpoint"}

    payload = build_payload_from_request(req, role, settings)
    return payload, None


def build_payload_from_request(req, role: str, settings) -> dict:
    return {
        "alias": req.alias.strip(),
        "role": role,
        "hospital_id": settings.hospital_id,
        "hospital_name": req.hospital_name.strip(),
        "room_name": get_assignment_room_name(req.room_name, role),
        "mqtt_host": settings.broker_host,
        "mqtt_port": settings.broker_port,
    }


def get_assignment_room_name(room_name: str, role: str) -> str:
    if role == "REGISTRATION":
        return ""

    return room_name.strip()
