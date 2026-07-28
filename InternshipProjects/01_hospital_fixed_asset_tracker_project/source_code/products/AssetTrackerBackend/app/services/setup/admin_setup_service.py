"""
File: admin_setup_service.py
Author: Farros Ramzy (you@domain.com)
Description: First-admin setup service for fresh deployments.
Version: 0.1
Date: 2026-06-03

Copyright (c) 2026
"""

from fastapi import HTTPException, status
from sqlalchemy import func

from app.database import SessionLocal
from app.db_models import User
from app.services.authority.auth_service import hash_password
from app.services.setup.setup_flag_service import (
    is_first_admin_setup_completed,
    mark_first_admin_setup_completed,
)
from app.services.users.user_serializer import user_to_dict
from app.services.users.user_validation import validate_email, validate_full_name

ADMIN_ROLE = "admin"


def admin_exists_in_db(db) -> bool:
    return (
        db.query(User).filter(func.lower(User.role) == ADMIN_ROLE).first() is not None
    )


def ensure_setup_flag_for_existing_admin(db) -> None:
    if is_first_admin_setup_completed(db):
        return

    if admin_exists_in_db(db):
        mark_first_admin_setup_completed(db)
        db.commit()


def get_admin_setup_status() -> dict:
    db = SessionLocal()

    try:
        ensure_setup_flag_for_existing_admin(db)
        setup_done = is_first_admin_setup_completed(db)
        return {"setup_required": not setup_done}
    finally:
        db.close()


def hash_admin_password(password: str) -> str:
    try:
        return hash_password(password)
    except ValueError as exc:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=str(exc),
        ) from exc


def create_first_admin(req) -> dict:
    db = SessionLocal()

    try:
        ensure_setup_flag_for_existing_admin(db)

        if is_first_admin_setup_completed(db):
            raise HTTPException(
                status_code=status.HTTP_403_FORBIDDEN,
                detail="admin_setup_already_completed",
            )

        email = validate_email(req.email)
        full_name = validate_full_name(req.full_name)
        existing_user = db.query(User).filter(User.email == email).first()

        if existing_user is not None:
            raise HTTPException(
                status_code=status.HTTP_409_CONFLICT,
                detail="email_already_registered",
            )

        user = User(
            email=email,
            full_name=full_name,
            role=ADMIN_ROLE,
            hashed_password=hash_admin_password(req.password),
            is_active=True,
        )

        db.add(user)
        mark_first_admin_setup_completed(db)
        db.commit()
        db.refresh(user)

        return user_to_dict(user)
    finally:
        db.close()
