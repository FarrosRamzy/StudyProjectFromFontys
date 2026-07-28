"""
File: user_create_service.py
Author: Farros Ramzy (you@domain.com)
Description: Validates and creates new user records with securely hashed passwords.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import HTTPException, status

from app.database import SessionLocal
from app.db_models import User
from app.services.authority.auth_service import hash_password
from app.services.users.user_serializer import user_to_dict
from app.services.users.user_validation import (
    validate_email,
    validate_full_name,
    validate_role,
)


def create_user_record(req):
    db = SessionLocal()

    try:
        email = validate_email(req.email)
        full_name = validate_full_name(req.full_name)
        role = validate_role(req.role)

        existing_user = db.query(User).filter(User.email == email).first()

        if existing_user is not None:
            raise HTTPException(
                status_code=status.HTTP_409_CONFLICT,
                detail="email_already_registered",
            )

        try:
            hashed_password = hash_password(req.password)
        except ValueError as exc:
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail=str(exc),
            ) from exc

        user = User(
            email=email,
            full_name=full_name,
            role=role,
            hashed_password=hashed_password,
            is_active=True,
        )

        db.add(user)
        db.commit()
        db.refresh(user)

        return {
            "message": "user_created",
            "user": user_to_dict(user),
        }

    finally:
        db.close()
