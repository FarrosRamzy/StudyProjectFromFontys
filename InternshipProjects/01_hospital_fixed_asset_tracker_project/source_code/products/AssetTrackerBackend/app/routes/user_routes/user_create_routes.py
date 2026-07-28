"""
File: user_create_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Admin-protected API route for creating user accounts.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends, status

from app.db_models import User
from app.models import CreateUserRequest
from app.services.authority.auth_dependencies import require_role
from app.services.users.user_create_service import create_user_record

router = APIRouter(prefix="/users", tags=["users"])


@router.post("", status_code=status.HTTP_201_CREATED)
def create_user(
    req: CreateUserRequest,
    current_user: User = Depends(require_role("admin")),
):
    return create_user_record(req)
