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


def test_normalize_email_trims_and_lowercases():
    assert normalize_email("  TEST@Hospital.Local  ") == "test@hospital.local"

def test_validate_email_rejects_empty_email():
    with pytest.raises(HTTPException) as exc:
        validate_email("   ")

    assert exc.value.status_code == 400
    assert exc.value.detail == "email_required"

def test_validate_full_name_rejects_empty_name():
    with pytest.raises(HTTPException) as exc:
        validate_full_name("   ")

    assert exc.value.status_code == 400
    assert exc.value.detail == "full_name_required"

def test_validate_role_accepts_valid_role():
    assert validate_role("admin") == "admin"
    assert validate_role("test_user") == "test_user"
    assert validate_role("registration_staff") == "registration_staff"
    assert validate_role("monitor_staff") == "monitor_staff"
    assert validate_role("technician") == "technician"

def test_validate_role_rejects_invalid_role():
    with pytest.raises(HTTPException) as exc:
        validate_role("visitor")

    assert exc.value.status_code == 400
    assert exc.value.detail == "invalid_role"
