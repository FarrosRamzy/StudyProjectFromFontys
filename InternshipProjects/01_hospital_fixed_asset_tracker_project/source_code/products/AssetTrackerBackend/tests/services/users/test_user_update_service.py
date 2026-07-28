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


def test_update_user_role_record_succeeds(db_session, make_user):
    user = make_user(
        email="role.change@hospital.local",
        full_name="Role Change",
        role="monitor_staff",
    )

    req = SimpleNamespace(role="technician")

    admin = make_user(
        email="admin-update-role@hospital.local",
        full_name="Admin Update Role",
        role="admin",
    )

    result = update_user_role_record(
        user_id=user.id,
        req=req,
        current_user=admin,
    )

    assert result["message"] == "user_role_updated"
    assert result["user"]["role"] == "technician"

    db_session.refresh(user)
    assert user.role == "technician"

def test_update_user_role_record_rejects_missing_user(make_user):
    req = SimpleNamespace(role="technician")

    with pytest.raises(HTTPException) as exc:
        admin = make_user(
            email="admin-missing-role@hospital.local",
            full_name="Admin Missing Role",
            role="admin",
            is_active=True,
        )

        update_user_role_record(
            user_id=9999,
            req=req,
            current_user=admin,
        )

    assert exc.value.status_code == 404
    assert exc.value.detail == "user_not_found"

def test_update_user_role_record_rejects_invalid_role(make_user):
    user = make_user(
        email="invalid.role.change@hospital.local",
        full_name="Invalid Role Change",
        role="monitor_staff",
    )

    req = SimpleNamespace(role="visitor")

    with pytest.raises(HTTPException) as exc:
        admin = make_user(
            email="admin-invalid-role@hospital.local",
            full_name="Admin Invalid Role",
            role="admin",
        )

        update_user_role_record(
            user_id=user.id,
            req=req,
            current_user=admin,
        )

    assert exc.value.status_code == 400
    assert exc.value.detail == "invalid_role"

def test_update_user_active_status_record_deactivates_other_user(db_session, make_user):
    admin = make_user(
        email="admin.active@hospital.local",
        full_name="Admin Active",
        role="admin",
    )

    target_user = make_user(
        email="target.active@hospital.local",
        full_name="Target Active",
        role="monitor_staff",
        is_active=True,
    )

    req = SimpleNamespace(is_active=False)

    result = update_user_active_status_record(
        user_id=target_user.id,
        req=req,
        current_user=admin,
    )

    assert result["message"] == "user_active_status_updated"
    assert result["user"]["is_active"] is False

    db_session.refresh(target_user)
    assert target_user.is_active is False
