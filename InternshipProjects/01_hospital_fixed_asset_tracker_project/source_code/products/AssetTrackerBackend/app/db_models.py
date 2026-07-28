"""
File: db_models.py
Author: Farros Ramzy (you@domain.com)
Description: Compatibility exports for database models.
Version: 0.1
Date: 2026-04-21

Copyright (c) 2026
"""

from app.db.node_db_model import Node
from app.db.asset_db_model import Asset
from app.db.asset_event_db_model import AssetEvent
from app.db.asset_movement_request_db_model import AssetMovementRequest
from app.db.user_db_model import User
from app.db.system_setting_db_model import SystemSetting

__all__ = [
    "Node",
    "Asset",
    "AssetEvent",
    "AssetMovementRequest",
    "User",
    "SystemSetting",
]
