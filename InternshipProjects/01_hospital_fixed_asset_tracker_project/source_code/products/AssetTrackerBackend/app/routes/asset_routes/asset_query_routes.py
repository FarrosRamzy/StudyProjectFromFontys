"""
File: asset_query_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Asset query routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.serializers.asset_serializer import asset_to_dict
from app.services.assets.asset_service import list_assets
from app.services.authority.auth_dependencies import require_role

router = APIRouter(tags=["assets"])


@router.get("/assets")
def get_assets(
    current_user: User = Depends(
        require_role("admin", "test_user", "registration_staff", "monitor_staff")
    )
):
    assets = list_assets()
    return [asset_to_dict(asset) for asset in assets]
