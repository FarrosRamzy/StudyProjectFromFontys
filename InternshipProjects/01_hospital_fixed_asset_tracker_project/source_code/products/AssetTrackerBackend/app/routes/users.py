"""
File: users.py
Author: Farros Ramzy (you@domain.com)
Description: Aggregates the user-management route modules into one router.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import APIRouter

from app.routes.user_routes.user_create_routes import router as user_create_router
from app.routes.user_routes.user_password_routes import router as user_password_router
from app.routes.user_routes.user_query_routes import router as user_query_router
from app.routes.user_routes.user_update_routes import router as user_update_router

router = APIRouter()

router.include_router(user_query_router)
router.include_router(user_create_router)
router.include_router(user_update_router)
router.include_router(user_password_router)
