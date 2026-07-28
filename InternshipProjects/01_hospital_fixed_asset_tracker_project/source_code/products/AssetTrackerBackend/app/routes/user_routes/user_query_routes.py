"""
File: user_query_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends

from app.db_models import User
from app.services.authority.auth_dependencies import require_role
from app.services.users.user_query_service import list_user_records

router = APIRouter(prefix="/users", tags=["users"])


@router.get("")
def list_users(
    current_user: User = Depends(require_role("admin")),
):
    return list_user_records()
