"""
File: asset_location_service.py
Author: Farros Ramzy (you@domain.com)
Description: Public interface for asset-location matching, updates, timestamps, and movement completion.
Version: 0.1
Date: 2026-05-12

Copyright (c) 2026
"""

from app.services.assets.location.asset_location_update_service import (
    update_asset_location,
)

from app.services.assets.location.asset_location_matcher import (
    location_matches,
)

from app.services.assets.location.asset_flow_resolver import (
    resolve_asset_flow_after_detection,
)

from app.services.assets.location.asset_movement_completion_service import (
    complete_active_movement_request,
)

from app.services.assets.location.asset_timestamp_service import (
    normalize_asset_timestamp,
)
