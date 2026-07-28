"""
File: user_password_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Password management routes for user accounts.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.models import ResetUserPasswordRequest, ChangeOwnPasswordRequest
from app.services.authority.auth_dependencies import require_role, get_current_user
from app.services.users.user_password_service import (
    reset_user_password_record,
    change_current_user_password_record,
)

router = APIRouter(prefix="/users", tags=["users"])


@router.post("/me/password")
def change_my_password(
    req: ChangeOwnPasswordRequest,
    current_user: User = Depends(get_current_user),
):
    return change_current_user_password_record(
        current_user=current_user,
        req=req,
    )


@router.post("/{user_id}/reset-password")
def reset_user_password(
    user_id: int,
    req: ResetUserPasswordRequest,
    current_user: User = Depends(require_role("admin")),
):
    return reset_user_password_record(
        user_id=user_id,
        req=req,
        current_user=current_user,
    )
