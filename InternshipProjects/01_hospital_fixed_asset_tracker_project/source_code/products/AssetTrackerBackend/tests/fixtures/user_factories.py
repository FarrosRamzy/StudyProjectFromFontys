"""
File: user_factories.py
Author: Farros Ramzy (you@domain.com)
Description: User factory fixtures.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest

from app.db_models import User
from app.services.authority.auth_service import hash_password


@pytest.fixture()
def make_user(db_session):
    def _make_user(
        email="admin@test.local",
        full_name="Test Admin",
        role="admin",
        password="Password12345!",
        is_active=True,
    ):
        user = User(
            email=str(email).strip().lower(),
            full_name=full_name,
            role=role,
            hashed_password=hash_password(password),
            is_active=is_active,
        )

        db_session.add(user)
        db_session.commit()
        db_session.refresh(user)

        return user

    return _make_user
