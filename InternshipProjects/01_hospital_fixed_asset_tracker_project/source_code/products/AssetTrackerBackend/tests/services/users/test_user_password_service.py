"""User service tests."""

import pytest
from types import SimpleNamespace
from fastapi import HTTPException

from app.db_models import User
from app.services.authority.auth_service import verify_password
from app.services.users.user_admin_policy import count_active_admins, is_last_active_admin
from app.services.users.user_create_service import create_user_record
from app.services.users.user_password_service import reset_user_password_record
from app.services.users.user_query_service import list_user_records
from app.services.users.user_update_service import update_user_active_status_record, update_user_role_record
from app.services.users.user_validation import normalize_email, validate_email, validate_full_name, validate_role
from tests.conftest import make_user


def test_reset_user_password_record_succeeds(db_session, make_user):
    user = make_user(
        email="reset.password@hospital.local",
        full_name="Reset Password",
        role="monitor_staff",
    )

    old_hash = user.hashed_password

    req = SimpleNamespace(password="NewPassword12345!")

    admin = make_user(
        email="admin-reset-password@hospital.local",
        full_name="Admin Reset Password",
        role="admin",
    )

    result = reset_user_password_record(
        user_id=user.id,
        req=req,
        current_user=admin,
    )

    assert result["message"] == "user_password_reset"
    assert result["user"]["id"] == user.id

    db_session.refresh(user)

    assert user.hashed_password != old_hash
    assert verify_password("NewPassword12345!", user.hashed_password)

def test_reset_user_password_record_rejects_missing_user(make_user):
    req = SimpleNamespace(password="NewPassword12345!")

    with pytest.raises(HTTPException) as exc:
        admin = make_user(
            email="admin-missing-reset@hospital.local",
            full_name="Admin Missing Reset",
            role="admin",
            is_active=True,
        )

        reset_user_password_record(
            user_id=9999,
            req=req,
            current_user=admin,
        )

    assert exc.value.status_code == 404
    assert exc.value.detail == "user_not_found"
