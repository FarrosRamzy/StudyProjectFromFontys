"""
File: user_update_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Admin-only user update routes.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import UpdateUserActiveRequest, UpdateUserRoleRequest
from app.services.authority.auth_dependencies import require_role
from app.services.users.user_update_service import (
    update_user_active_status_record,
    update_user_role_record,
)

router = APIRouter(prefix="/users", tags=["users"])


@router.patch("/{user_id}/role")
def update_user_role(
    user_id: int,
    req: UpdateUserRoleRequest,
    current_user: User = Depends(require_role("admin")),
):
    return update_user_role_record(
        user_id=user_id,
        req=req,
        current_user=current_user,
    )


@router.patch("/{user_id}/active")
def update_user_active_status(
    user_id: int,
    req: UpdateUserActiveRequest,
    current_user: User = Depends(require_role("admin")),
):
    return update_user_active_status_record(
        user_id=user_id,
        req=req,
        current_user=current_user,
    )
