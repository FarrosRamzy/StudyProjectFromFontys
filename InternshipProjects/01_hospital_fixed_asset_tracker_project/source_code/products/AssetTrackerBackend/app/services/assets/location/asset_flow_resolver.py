"""
File: asset_flow_resolver.py
Author: Farros Ramzy (you@domain.com)
Description: Coordinates asset flow resolution after checkpoint detection.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from app.db.asset_db_model import Asset
from app.services.assets.location.flow.asset_flow_context import (
    build_asset_flow_context,
)
from app.services.assets.location.flow.asset_flow_dispatcher import (
    dispatch_asset_flow_resolution,
)


def resolve_asset_flow_after_detection(
    db,
    asset: Asset,
    detected_room_name: str,
    detected_node_id: str,
):
    context = build_asset_flow_context(
        asset=asset,
        detected_room_name=detected_room_name,
        detected_node_id=detected_node_id,
    )

    dispatch_asset_flow_resolution(db, asset, context)
