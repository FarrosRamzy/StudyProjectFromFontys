"""
File: asset_flow_dispatcher.py
Author: Farros Ramzy (you@domain.com)
Description: Dispatches asset flow status to the correct resolver.
Version: 0.1
Date: 2026-06-12

Copyright (c) 2026
"""

from app.services.assets.location.flow.asset_flow_available import (
    resolve_available_flow,
)
from app.services.assets.location.flow.asset_flow_in_transit import (
    resolve_in_transit_flow,
)
from app.services.assets.location.flow.asset_flow_movement_requested import (
    resolve_movement_requested_flow,
)
from app.services.assets.location.flow.asset_flow_pending_placement import (
    resolve_pending_placement_flow,
)
from app.services.assets.location.flow.asset_flow_unauthorized import (
    resolve_unauthorized_movement_flow,
)
from app.services.assets.location.flow.asset_flow_wrong_location import (
    resolve_wrong_location_flow,
)

FLOW_RESOLVERS = {
    "pending_placement": resolve_pending_placement_flow,
    "available": resolve_available_flow,
    "movement_requested": resolve_movement_requested_flow,
    "in_transit": resolve_in_transit_flow,
    "unauthorized_movement": resolve_unauthorized_movement_flow,
    "wrong_location": resolve_wrong_location_flow,
}


def dispatch_asset_flow_resolution(db, asset, context: dict) -> None:
    resolver = FLOW_RESOLVERS.get(context["flow_status"])

    if resolver is None:
        return

    resolver(db, asset, context)
