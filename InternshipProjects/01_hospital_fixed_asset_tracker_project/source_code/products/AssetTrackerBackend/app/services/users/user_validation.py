"""
File: user_validation.py
Author: Farros Ramzy (you@domain.com)
Description: Normalizes and validates user email addresses, names, and roles.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

from fastapi import HTTPException, status

from app.services.users.user_constants import ALLOWED_USER_ROLES


def normalize_email(email: str) -> str:
    return str(email or "").strip().lower()


def validate_email(email: str) -> str:
    clean_email = normalize_email(email)

    if not clean_email:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="email_required",
        )

    return clean_email


def validate_full_name(full_name: str) -> str:
    clean_full_name = str(full_name or "").strip()

    if not clean_full_name:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="full_name_required",
        )

    return clean_full_name


def validate_role(role: str) -> str:
    clean_role = str(role or "").strip()

    if clean_role not in ALLOWED_USER_ROLES:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="invalid_role",
        )

    return clean_role
