"""
File: auth.py
Author: Farros Ramzy (you@domain.com)
Description: Authentication, first-admin setup, login, logout, and current-user API routes.
Version: 0.1
Date: 2026-05-18

Copyright (c) 2026
"""

from fastapi import APIRouter, Depends, HTTPException, status

from app.database import SessionLocal
from app.db_models import User
from app.models import LoginRequest, SetupAdminRequest
from app.services.authority.auth_service import authenticate_user, create_access_token
from app.services.authority.auth_dependencies import get_current_user

from app.services.setup.admin_setup_service import (
    create_first_admin,
    get_admin_setup_status,
)

router = APIRouter(prefix="/auth", tags=["auth"])


def user_to_dict(user: User) -> dict:
    return {
        "id": user.id,
        "email": user.email,
        "full_name": user.full_name,
        "role": user.role,
        "is_active": user.is_active,
    }


@router.get("/setup-status")
async def setup_status():
    return get_admin_setup_status()


@router.post("/setup-admin", status_code=status.HTTP_201_CREATED)
async def setup_admin(req: SetupAdminRequest):
    user = create_first_admin(req)
    access_token = create_access_token(
        {
            "sub": str(user["id"]),
            "email": user["email"],
            "role": user["role"],
        }
    )

    return {
        "message": "admin_created",
        "access_token": access_token,
        "token_type": "bearer",
        "user": user,
    }


@router.post("/login")
async def login(req: LoginRequest):
    db = SessionLocal()

    try:
        user = authenticate_user(db, req.email, req.password)

        if user is None:
            raise HTTPException(
                status_code=status.HTTP_401_UNAUTHORIZED,
                detail="invalid_email_or_password",
            )

        access_token = create_access_token(
            {
                "sub": str(user.id),
                "email": user.email,
                "role": user.role,
            }
        )

        return {
            "access_token": access_token,
            "token_type": "bearer",
            "user": user_to_dict(user),
        }

    finally:
        db.close()


@router.get("/me")
async def me(current_user: User = Depends(get_current_user)):
    return {
        "user": user_to_dict(current_user),
    }


@router.post("/logout")
async def logout():
    return {
        "message": "logged_out",
    }
