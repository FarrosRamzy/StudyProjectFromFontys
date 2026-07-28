"""
File: node_lifecycle_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Node lifecycle routes: enroll, assign, unassign, delete.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import AssignNodeRequest, EnrollNodeRequest
from app.routes.node_routes.node_provisioning_routes import verify_node_provisioning_key
from app.services.authority.auth_dependencies import require_role
from app.services.nodes.node_assigner import assign_node_record
from app.services.nodes.node_service import (
    delete_node_record,
    enroll_node_record,
    unassign_node_record,
)
from app.websocket_manager import ws_manager

router = APIRouter(tags=["nodes"])


@router.post("/nodes/enroll")
async def enroll_node(
    req: EnrollNodeRequest,
    _: None = Depends(verify_node_provisioning_key),
):
    node_data = enroll_node_record(req.device_id)

    await ws_manager.broadcast_json(
        {
            "type": "node_enrolled",
            "node": node_data,
        }
    )

    return {"message": "node_enrolled", "node": node_data}


@router.post("/nodes/{device_id}/assign")
async def assign_node(
    device_id: str,
    req: AssignNodeRequest,
    current_user: User = Depends(require_role("admin", "test_user", "technician")),
):
    result = assign_node_record(device_id, req)

    if result is None:
        return {"message": "node_not_found"}

    if result.get("message") != "node_assigned":
        return result

    node_data = result["node"]

    await ws_manager.broadcast_json(
        {
            "type": "node_assigned",
            "node": node_data,
        }
    )

    return {
        "message": "node_assigned",
        "node": node_data,
    }


@router.post("/nodes/{device_id}/unassign")
async def unassign_node(
    device_id: str,
    current_user: User = Depends(require_role("admin", "test_user", "technician")),
):
    result = unassign_node_record(device_id)

    if result is None:
        return {"message": "node_not_found", "device_id": device_id}

    if isinstance(result, dict) and result.get("message") == "node_unassign_blocked":
        return result

    node_data = result

    await ws_manager.broadcast_json(
        {
            "type": "node_unassigned",
            "node": node_data,
        }
    )

    return {"message": "node_unassigned", "node": node_data}


@router.delete("/nodes/{device_id}")
async def delete_node(
    device_id: str,
    current_user: User = Depends(require_role("admin", "test_user", "technician")),
):
    result = delete_node_record(device_id)

    if result is None:
        return {"message": "node_not_found", "device_id": device_id}

    if result.get("message") == "node_deleted":
        await ws_manager.broadcast_json(
            {
                "type": "node_deleted",
                "device_id": device_id,
            }
        )

    return result
