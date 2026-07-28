"""
File: asset_service.py
Author: Farros Ramzy (you@domain.com)
Description: Facade that exposes asset registration, location, movement, and repository operations.
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.services.assets.asset_repository import (
    delete_asset_record,
    get_asset_by_tag,
    list_assets,
)

from app.services.assets.asset_location_service import (
    update_asset_location,
)

from app.services.assets.asset_registration_service import (
    deregister_asset_record,
    register_asset_record,
)

from app.services.assets.asset_movement_service import (
    approve_asset_movement_request,
    cancel_asset_movement_request,
    create_asset_movement_request,
    reject_asset_movement_request,
    list_asset_movement_requests,
)

__all__ = [
    "list_assets",
    "get_asset_by_tag",
    "update_asset_location",
    "register_asset_record",
    "deregister_asset_record",
    "delete_asset_record",
    "approve_asset_movement_request",
    "cancel_asset_movement_request",
    "create_asset_movement_request",
    "reject_asset_movement_request",
    "list_asset_movement_requests",
]
