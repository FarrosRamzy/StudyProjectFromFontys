"""
File: user_password_service.py
Author: Farros Ramzy (you@domain.com)
Description: Password update services for user accounts.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import HTTPException, status

from app.database import SessionLocal
from app.db_models import User
from app.services.authority.auth_service import hash_password, verify_password
from app.services.users.user_admin_policy import ensure_can_admin_reset_password
from app.services.users.user_serializer import user_to_dict


def hash_password_or_400(password: str) -> str:
    try:
        return hash_password(password)
    except ValueError as exc:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=str(exc),
        ) from exc


def get_user_or_404(db, user_id: int) -> User:
    user = db.query(User).filter(User.id == user_id).first()

    if user is None:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="user_not_found",
        )

    return user


def reset_user_password_record(user_id: int, req, current_user: User):
    db = SessionLocal()

    try:
        user = get_user_or_404(db, user_id)
        ensure_can_admin_reset_password(user, current_user)

        user.hashed_password = hash_password_or_400(req.password)
        db.add(user)
        db.commit()
        db.refresh(user)

        return {
            "message": "user_password_reset",
            "user": user_to_dict(user),
        }
    finally:
        db.close()


def change_current_user_password_record(current_user: User, req):
    db = SessionLocal()

    try:
        user = get_user_or_404(db, current_user.id)

        if not user.is_active:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="user_not_found",
            )

        if not verify_password(req.current_password, user.hashed_password):
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail="current_password_incorrect",
            )

        user.hashed_password = hash_password_or_400(req.new_password)
        db.add(user)
        db.commit()
        db.refresh(user)

        return {
            "message": "password_changed",
            "user": user_to_dict(user),
        }
    finally:
        db.close()
