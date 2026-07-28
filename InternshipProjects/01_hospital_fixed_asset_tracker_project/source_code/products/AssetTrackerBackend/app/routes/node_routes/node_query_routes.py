"""
File: node_query_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Admin-protected API routes for listing and retrieving user accounts.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.services.authority.auth_dependencies import require_role
from app.services.nodes.node_service import list_nodes

router = APIRouter(tags=["nodes"])


@router.get("/nodes")
def get_nodes(
    current_user: User = Depends(require_role("admin", "test_user", "technician", "monitor_staff", "registration_staff")),
):
    return list_nodes()
