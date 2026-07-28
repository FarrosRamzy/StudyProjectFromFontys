"""
File: auth_dependencies.py
Author: Farros Ramzy (you@domain.com)
Description: FastAPI dependencies for authenticating users and enforcing role-based access.
Version: 0.1
Date: 2026-05-18

Copyright (c) 2026
"""

from fastapi import Depends, HTTPException, status
from fastapi.security import HTTPAuthorizationCredentials, HTTPBearer

from app.database import SessionLocal
from app.db_models import User
from app.services.authority.auth_service import decode_access_token

security = HTTPBearer(auto_error=False)


def get_current_user(
    credentials: HTTPAuthorizationCredentials = Depends(security),
):
    if credentials is None:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="not_authenticated",
        )

    token = credentials.credentials
    payload = decode_access_token(token)

    if payload is None:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="invalid_token",
        )

    user_id = payload.get("sub")

    if user_id is None:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="invalid_token_payload",
        )

    db = SessionLocal()

    try:
        user = db.query(User).filter(User.id == int(user_id)).first()

        if user is None or not user.is_active:
            raise HTTPException(
                status_code=status.HTTP_401_UNAUTHORIZED,
                detail="user_not_found_or_inactive",
            )

        return user

    finally:
        db.close()


def normalize_role(role: str | None) -> str:
    return str(role or "").strip().lower().replace("-", "_").replace(" ", "_")


def require_role(*allowed_roles: str):
    normalized_allowed_roles = {normalize_role(role) for role in allowed_roles}

    def role_checker(current_user: User = Depends(get_current_user)):
        current_role = normalize_role(current_user.role)

        if current_role not in normalized_allowed_roles:
            raise HTTPException(
                status_code=status.HTTP_403_FORBIDDEN,
                detail="insufficient_permission",
            )

        return current_user

    return role_checker
