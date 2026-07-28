"""
File: node_assignment_change.py
Author: Farros Ramzy (you@domain.com)
Description: Detects assignment changes during node re-assignment.
Version: 0.1
Date: 2026-06-11

Copyright (c) 2026
"""

from app.db.node_db_model import Node


def build_reassignment_context(
    node: Node,
    new_role: str,
    new_room_name: str,
    new_hospital_id: str,
) -> dict:
    old_values = _get_old_assignment_values(node)
    new_values = _get_new_assignment_values(
        new_role=new_role,
        new_room_name=new_room_name,
        new_hospital_id=new_hospital_id,
    )

    return {
        "device_id": node.device_id,
        "old": old_values,
        "new": new_values,
        "has_dangerous_change": _has_dangerous_change(old_values, new_values),
    }


def _get_old_assignment_values(node: Node) -> dict:
    return {
        "role": _clean_upper(node.role),
        "room_name": _clean_text(node.room_name),
        "hospital_id": _clean_text(node.hospital_id),
    }


def _get_new_assignment_values(
    new_role: str,
    new_room_name: str,
    new_hospital_id: str,
) -> dict:
    return {
        "role": _clean_upper(new_role),
        "room_name": _clean_text(new_room_name),
        "hospital_id": _clean_text(new_hospital_id),
    }


def _has_dangerous_change(old_values: dict, new_values: dict) -> bool:
    role_is_changing = old_values["role"] and old_values["role"] != new_values["role"]
    room_is_changing = old_values["room_name"] != new_values["room_name"]
    hospital_is_changing = old_values["hospital_id"] != new_values["hospital_id"]

    return role_is_changing or room_is_changing or hospital_is_changing


def _clean_text(value) -> str:
    return (value or "").strip()


def _clean_upper(value) -> str:
    return _clean_text(value).upper()
