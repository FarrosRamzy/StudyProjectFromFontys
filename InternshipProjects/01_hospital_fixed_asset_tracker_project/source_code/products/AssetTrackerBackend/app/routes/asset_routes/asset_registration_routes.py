"""
File: asset_registration_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset registration and deregistration routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import DeregisterAssetRequest, RegisterAssetRequest
from app.serializers.asset_serializer import asset_to_dict
from app.services.assets.asset_service import (
    deregister_asset_record,
    register_asset_record,
)
from app.services.authority.auth_dependencies import require_role
from app.websocket_manager import ws_manager

router = APIRouter(tags=["assets"])


@router.post("/assets/register")
async def register_asset(
    req: RegisterAssetRequest,
    current_user: User = Depends(require_role("admin", "test_user", "registration_staff")),
):
    result = register_asset_record(
        req.tag_id,
        req.item_name,
        req.registration_node_id,
        req.initial_room_name,
        req.initial_node_id,
    )

    if result is None:
        return {"message": "registration_failed", "reason": "invalid_registration_node"}

    if isinstance(result, dict):
        return result

    asset = result
    asset_data = asset_to_dict(asset)

    await ws_manager.broadcast_json(
        {
            "type": "asset_registered",
            "asset": asset_data,
        }
    )

    return {"message": "registered", "asset": asset_data}


@router.post("/assets/deregister")
async def deregister_asset(
    req: DeregisterAssetRequest,
    current_user: User = Depends(require_role("admin", "test_user", "registration_staff")),
):
    asset = deregister_asset_record(req.tag_id, req.registration_node_id, req.reason)

    if asset is None:
        return {"message": "not_found", "tag_id": req.tag_id}

    asset_data = asset_to_dict(asset)

    await ws_manager.broadcast_json(
        {
            "type": "asset_deregistered",
            "asset": asset_data,
        }
    )

    return {
        "message": "deregistered",
        "tag_id": req.tag_id,
        "asset": asset_data,
    }
