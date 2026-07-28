"""
File: asset_lifecycle_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset lifecycle routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.services.assets.asset_service import delete_asset_record
from app.services.authority.auth_dependencies import require_role
from app.websocket_manager import ws_manager

router = APIRouter(tags=["assets"])


@router.delete("/assets/{tag_id}")
async def delete_asset(
    tag_id: str,
    current_user: User = Depends(require_role("admin", "test_user", "registration_staff")),
):
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
