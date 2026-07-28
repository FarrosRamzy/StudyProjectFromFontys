"""
File: asset_movement_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset movement request routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import (
    CancelMovementRequest,
    CreateMovementRequest,
    DecideMovementRequest,
)
from app.services.assets.asset_service import (
    approve_asset_movement_request,
    cancel_asset_movement_request,
    create_asset_movement_request,
    list_asset_movement_requests,
    reject_asset_movement_request,
)
from app.services.authority.auth_dependencies import require_role
from app.websocket_manager import ws_manager

router = APIRouter(tags=["assets"])


@router.get("/assets/movement/requests")
def get_asset_movement_requests(
    status: str = "",
    current_user: User = Depends(
        require_role("admin", "test_user", "registration_staff", "monitor_staff")
    ),
):
    return list_asset_movement_requests(status=status)


@router.post("/assets/movement/request")
async def request_asset_movement(
    req: CreateMovementRequest,
    current_user: User = Depends(
        require_role("admin", "test_user", "registration_staff", "monitor_staff")
    ),
):
    result = create_asset_movement_request(req, current_user.id)

    if result.get("message") == "movement_requested":
        await ws_manager.broadcast_json(
            {
                "type": "asset_movement_requested",
                "asset": result["asset"],
                "movement_request": {
                    "id": result["movement_request_id"],
                    "movement_request_id": result["movement_request_id"],
                    "tag_id": result["asset"]["tag_id"],
                    "item_name": result["asset"]["item_name"],
                    "status": "pending",
                },
            }
        )

    return result


@router.post("/assets/movement/approve")
async def approve_asset_movement(
    req: DecideMovementRequest,
    current_user: User = Depends(require_role("admin", "test_user", "registration_staff")),
):
    result = approve_asset_movement_request(req, current_user.id)

    if result.get("message") == "movement_approved":
        await ws_manager.broadcast_json(
            {
                "type": "asset_movement_approved",
                "asset": result["asset"],
                "movement_request": {
                    "id": result["movement_request_id"],
                    "movement_request_id": result["movement_request_id"],
                    "tag_id": result["asset"]["tag_id"],
                    "item_name": result["asset"]["item_name"],
                    "status": "approved",
                },
            }
        )

    return result


@router.post("/assets/movement/reject")
async def reject_asset_movement(
    req: DecideMovementRequest,
    current_user: User = Depends(require_role("admin", "test_user", "registration_staff")),
):
    result = reject_asset_movement_request(req, current_user.id)

    if result.get("message") == "movement_rejected":
        await ws_manager.broadcast_json(
            {
                "type": "asset_movement_rejected",
                "asset": result["asset"],
                "movement_request": {
                    "id": result["movement_request_id"],
                    "movement_request_id": result["movement_request_id"],
                    "tag_id": result["asset"]["tag_id"],
                    "item_name": result["asset"]["item_name"],
                    "status": "rejected",
                },
            }
        )

    return result


@router.post("/assets/movement/cancel")
async def cancel_asset_movement(
    req: CancelMovementRequest,
    current_user: User = Depends(
        require_role("admin", "test_user", "registration_staff", "monitor_staff")
    ),
):
    result = cancel_asset_movement_request(req, current_user.id)

    if result.get("message") == "movement_cancelled":
        await ws_manager.broadcast_json(
            {
                "type": "asset_movement_cancelled",
                "asset": result["asset"],
                "movement_request": {
                    "id": result["movement_request_id"],
                    "movement_request_id": result["movement_request_id"],
                    "tag_id": result["asset"]["tag_id"],
                    "item_name": result["asset"]["item_name"],
                    "status": "cancelled",
                },
            }
        )

    return result
