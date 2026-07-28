"""
File: nodes.py
Author: Farros Ramzy (you@domain.com)
Description: Compatibility facade/router collector for node routes.
Version: 0.3
Date: 2026-04-21

Copyright (c) 2026
"""

"""
Important: keep this file as app/routes/nodes.py because main.py imports it.
The split route files are stored in app/routes/node_routes/ to avoid a filesystem
name conflict with this file.
"""

from fastapi import APIRouter

from app.routes.node_routes.node_command_routes import router as node_command_router
from app.routes.node_routes.node_lifecycle_routes import router as node_lifecycle_router
from app.routes.node_routes.node_provisioning_routes import (
    router as node_provisioning_router,
)
from app.routes.node_routes.node_query_routes import router as node_query_router

router = APIRouter(tags=["nodes"])

router.include_router(node_query_router)
router.include_router(node_lifecycle_router)
router.include_router(node_provisioning_router)
router.include_router(node_command_router)
