"""
File: asset_registration_service.py
Author: Farros Ramzy (you@domain.com)
Description: Public interface for registering, de-registering, and validating hospital assets.
Version: 0.1
Date: 2026-05-12

Copyright (c) 2026
"""

from app.services.assets.registration.asset_register_service import (
    register_asset_record,
)

from app.services.assets.registration.asset_deregister_service import (
    deregister_asset_record,
)

from app.services.assets.registration.registration_validation_service import (
    get_registration_node,
    has_recent_registration_scan,
    validate_initial_checkpoint_node,
)

__all__ = [
    "deregister_asset_record",
    "get_registration_node",
    "has_recent_registration_scan",
    "register_asset_record",
    "validate_initial_checkpoint_node",
]
