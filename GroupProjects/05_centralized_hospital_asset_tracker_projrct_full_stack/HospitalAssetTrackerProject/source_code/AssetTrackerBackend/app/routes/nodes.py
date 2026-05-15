"""
File: nodes.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.3
Date: 2026-04-21

Copyright (c) 2026
"""

# from typing import Any
from fastapi import APIRouter

# from app.storage import nodes
# from app.models import RegisterNodeRequest, ProvisionNodeRequest
from app.models import EnrollNodeRequest, AssignNodeRequest, ProvisionNodeRequest

from app.services.nodes.node_service import (
    list_nodes,
    enroll_node_record,
    get_provision_payload,
    delete_node_record,
    unassign_node_record,
)
from app.services.nodes.node_assigner import assign_node_record

from app.websocket_manager import ws_manager

router = APIRouter(tags=["nodes"])


@router.get("/nodes")
def get_nodes():
    return list_nodes()


@router.post("/nodes/enroll")
async def enroll_node(req: EnrollNodeRequest):
    node_data = enroll_node_record(req.device_id)

    await ws_manager.broadcast_json(
        {
            "type": "node_enrolled",
            "node": node_data,
        }
    )

    return {"message": "node_enrolled", "node": node_data}


@router.post("/nodes/{device_id}/assign")
async def assign_node(device_id: str, req: AssignNodeRequest):
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

    # return result

    return {
        "message": "node_assigned",
        "node": node_data,
    }


@router.post("/nodes/provision")
def provision_node(req: ProvisionNodeRequest):
    return get_provision_payload(req.device_id)


@router.post("/nodes/{device_id}/unassign")
async def unassign_node(device_id: str):
    node_data = unassign_node_record(device_id)

    if node_data is None:
        return {"message": "node_not_found", "device_id": device_id}

    await ws_manager.broadcast_json(
        {
            "type": "node_unassigned",
            "node": node_data,
        }
    )

    return {"message": "node_unassigned", "node": node_data}


@router.delete("/nodes/{device_id}")
async def delete_node(device_id: str):
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
