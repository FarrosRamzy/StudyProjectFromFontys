"""
File: user_admin_policy.py
Author: Farros Ramzy (you@domain.com)
Description: Safety rules for admin account management.
Version: 0.1
Date: 2026-06-05

Copyright (c) 2026
"""

from fastapi import HTTPException, status
from sqlalchemy import func

from app.db_models import User

ADMIN_ROLE = "admin"


def normalize_role(role: str | None) -> str:
    return str(role or "").strip().lower()


def is_admin(user: User | None) -> bool:
    return user is not None and normalize_role(user.role) == ADMIN_ROLE


def count_active_admins(db) -> int:
    return (
        db.query(User)
        .filter(func.lower(User.role) == ADMIN_ROLE)
        .filter(User.is_active.is_(True))
        .count()
    )


def is_last_active_admin(db, user: User) -> bool:
    return bool(is_admin(user) and user.is_active and count_active_admins(db) <= 1)


def ensure_can_change_role(db, target_user: User, current_user: User, new_role: str):
    if target_user.id == current_user.id:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="cannot_change_own_role",
        )

    demoting_admin = is_admin(target_user) and normalize_role(new_role) != ADMIN_ROLE

    if demoting_admin and is_last_active_admin(db, target_user):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="cannot_demote_last_active_admin",
        )


def ensure_can_change_active(db, target_user: User, current_user: User, is_active: bool):
    if is_active:
        return

    if target_user.id == current_user.id:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="admin_cannot_deactivate_self",
        )

    if is_last_active_admin(db, target_user):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="cannot_disable_last_active_admin",
        )


def ensure_can_admin_reset_password(target_user: User, current_user: User):
    if target_user.id == current_user.id:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="cannot_reset_own_password_here",
        )
