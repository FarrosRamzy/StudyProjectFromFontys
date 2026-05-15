"""
File: assets.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.2
Date: 2026-04-20

Copyright (c) 2026
"""

# from typing import Any
from fastapi import APIRouter

from app.models import RegisterAssetRequest, DeregisterAssetRequest
from app.serializers.asset_serializer import asset_to_dict

from app.services.assets.asset_service import (
    list_assets,
    register_asset_record,
    deregister_asset_record,
    delete_asset_record,
)

# from app.storage import assets
from app.websocket_manager import ws_manager

router = APIRouter(tags=["assets"])


@router.get("/assets")
def get_assets():
    assets = list_assets()
    return [asset_to_dict(asset) for asset in assets]


@router.post("/assets/register")
async def register_asset(req: RegisterAssetRequest):
    asset = register_asset_record(
        req.tag_id,
        req.item_name,
        req.registration_node_id,
    )

    if asset is None:
        return {"message": "registration_failed", "reason": "invalid_registration_node"}

    asset_data = asset_to_dict(asset)

    await ws_manager.broadcast_json(
        {
            "type": "asset_registered",
            "asset": asset_data,
        }
    )

    return {"message": "registered", "asset": asset_data}


@router.post("/assets/deregister")
async def deregister_asset(req: DeregisterAssetRequest):
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


@router.delete("/assets/{tag_id}")
async def delete_asset(tag_id: str):
    result = delete_asset_record(tag_id)

    if result is None:
        return {"message": "asset_not_found"}

    if result.get("message") == "asset_deleted":
        await ws_manager.broadcast_json(
            {
                "type": "asset_deleted",
                "tag_id": tag_id,
            }
        )

    return result
