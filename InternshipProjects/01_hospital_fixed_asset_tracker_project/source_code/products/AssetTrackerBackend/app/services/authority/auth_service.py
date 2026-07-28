"""
File: auth_service.py
Author: Farros Ramzy (you@domain.com)
Description: Password hashing, credential validation, JWT creation, and token decoding services.
Version: 0.1
Date: 2026-05-18

Copyright (c) 2026
"""

import os
import bcrypt

from typing import Optional

from datetime import timedelta
from app.utils import now_utc

from jose import JWTError, jwt
from app.db_models import User

JWT_SECRET_KEY = os.getenv("JWT_SECRET_KEY")
if not JWT_SECRET_KEY:
    raise RuntimeError("JWT_SECRET_KEY is not set")
JWT_ALGORITHM = os.getenv("JWT_ALGORITHM", "HS256")
JWT_ACCESS_TOKEN_EXPIRE_MINUTES = int(
    os.getenv("JWT_ACCESS_TOKEN_EXPIRE_MINUTES", "60")
)


def validate_bcrypt_password(password: str) -> str:
    password_bytes = str(password or "").encode("utf-8")

    if len(password_bytes) < 8:
        raise ValueError("password too short")

    if len(password_bytes) > 72:
        raise ValueError("password too long")

    return password_bytes


def hash_password(password: str) -> str:
    password_bytes = validate_bcrypt_password(password)
    
    hashed = bcrypt.hashpw(
        password_bytes,
        bcrypt.gensalt(rounds=12),
    )
    
    return hashed.decode("utf-8")


def verify_password(plain_password: str, hashed_password: str) -> bool:
    password_bytes = str(plain_password or "").encode("utf-8")
    
    if len(password_bytes) > 72:
        return False
    
    if not hashed_password:
        return False
    
    try:
        return bcrypt.checkpw(
            password_bytes,
            hashed_password.encode("utf-8"),
        )
    except ValueError:
        return False


def create_access_token(data: dict, expires_minutes: Optional[int] = None) -> str:
    expire_minutes = expires_minutes or JWT_ACCESS_TOKEN_EXPIRE_MINUTES

    payload = data.copy()
    expire = now_utc() + timedelta(minutes=expire_minutes)

    payload.update({"exp": expire})

    return jwt.encode(payload, JWT_SECRET_KEY, algorithm=JWT_ALGORITHM)


def authenticate_user(db, email: str, password: str) -> User | None:
    user = db.query(User).filter(User.email == email.strip().lower()).first()

    if user is None:
        return None

    if not user.is_active:
        return None

    if not verify_password(password, user.hashed_password):
        return None

    return user


def decode_access_token(token: str) -> dict | None:
    try:
        return jwt.decode(token, JWT_SECRET_KEY, algorithms=[JWT_ALGORITHM])
    except JWTError:
        return None
