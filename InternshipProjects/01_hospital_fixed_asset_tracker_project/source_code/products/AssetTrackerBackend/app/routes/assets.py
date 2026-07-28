"""
File: assets.py
Author: Farros Ramzy (you@domain.com)
Description: Compatibility facade/router collector for asset routes.
Version: 0.2
Date: 2026-04-20

Copyright (c) 2026
"""

"""
Important: keep this file as app/routes/assets.py because main.py imports it.
The split route files are stored in app/routes/asset_routes/ to avoid a filesystem
name conflict with this file.
"""

from fastapi import APIRouter

from app.routes.asset_routes.asset_lifecycle_routes import (
    router as asset_lifecycle_router,
)
from app.routes.asset_routes.asset_movement_routes import (
    router as asset_movement_router,
)
from app.routes.asset_routes.asset_query_routes import router as asset_query_router
from app.routes.asset_routes.asset_registration_routes import (
    router as asset_registration_router,
)

router = APIRouter(tags=["assets"])

router.include_router(asset_query_router)
router.include_router(asset_registration_router)
router.include_router(asset_movement_router)
router.include_router(asset_lifecycle_router)
