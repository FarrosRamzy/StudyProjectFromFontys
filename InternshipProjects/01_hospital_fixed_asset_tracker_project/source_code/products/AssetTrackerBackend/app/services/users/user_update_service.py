"""
File: user_update_service.py
Author: Farros Ramzy (you@domain.com)
Description: Updates user roles and active status while enforcing administrator safety rules.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import HTTPException, status

from app.database import SessionLocal
from app.db_models import User
from app.services.users.user_admin_policy import(
    ensure_can_change_active,
    ensure_can_change_role,
)
from app.services.users.user_serializer import user_to_dict
from app.services.users.user_validation import validate_role


def get_user_or_404(db, user_id: int) -> User:
    user = db.query(User).filter(User.id == user_id).first()

    if user is None:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="user_not_found",
        )

    return user


def update_user_role_record(user_id: int, req, current_user: User):
    db = SessionLocal()

    try:
        role = validate_role(req.role)
        user = get_user_or_404(db, user_id)
        ensure_can_change_role(db, user, current_user, role)

        user.role = role
        db.add(user)
        db.commit()
        db.refresh(user)

        return {
            "message": "user_role_updated",
            "user": user_to_dict(user),
        }
    finally:
        db.close()


def update_user_active_status_record(user_id: int, req, current_user: User):
    db = SessionLocal()

    try:
        user = get_user_or_404(db, user_id)
        ensure_can_change_active(db, user, current_user, req.is_active)

        user.is_active = req.is_active
        db.add(user)
        db.commit()
        db.refresh(user)

        return {
            "message": "user_active_status_updated",
            "user": user_to_dict(user),
        }
    finally:
        db.close()
