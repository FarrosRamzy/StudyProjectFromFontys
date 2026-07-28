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


def test_create_user_record_succeeds(db_session):
    req = SimpleNamespace(
        email="  New.User@Hospital.Local  ",
        full_name="New User",
        role="monitor_staff",
        password="Monitor12345!",
    )

    result = create_user_record(req)

    assert result["message"] == "user_created"
    assert result["user"]["email"] == "new.user@hospital.local"
    assert result["user"]["full_name"] == "New User"
    assert result["user"]["role"] == "monitor_staff"
    assert result["user"]["is_active"] is True

    user = (
        db_session.query(User).filter(User.email == "new.user@hospital.local").first()
    )

    assert user is not None
    assert user.hashed_password != "Monitor12345!"
    assert verify_password("Monitor12345!", user.hashed_password)

def test_create_user_record_rejects_duplicate_email(db_session, make_user):
    make_user(
        email="duplicate@hospital.local",
        full_name="Existing User",
        role="monitor_staff",
    )

    req = SimpleNamespace(
        email="duplicate@hospital.local",
        full_name="Duplicate User",
        role="technician",
        password="Technician12345!",
    )

    with pytest.raises(HTTPException) as exc:
        create_user_record(req)

    assert exc.value.status_code == 409
    assert exc.value.detail == "email_already_registered"

def test_create_user_record_rejects_invalid_role():
    req = SimpleNamespace(
        email="bad.role@hospital.local",
        full_name="Bad Role User",
        role="visitor",
        password="Password12345!",
    )

    with pytest.raises(HTTPException) as exc:
        create_user_record(req)

    assert exc.value.status_code == 400
    assert exc.value.detail == "invalid_role"

def test_list_user_records_returns_users(db_session, make_user):
    make_user(
        email="user.one@hospital.local",
        full_name="User One",
        role="admin",
    )

    make_user(
        email="user.two@hospital.local",
        full_name="User Two",
        role="technician",
    )

    users = list_user_records()

    emails = [user["email"] for user in users]

    assert "user.one@hospital.local" in emails
    assert "user.two@hospital.local" in emails
