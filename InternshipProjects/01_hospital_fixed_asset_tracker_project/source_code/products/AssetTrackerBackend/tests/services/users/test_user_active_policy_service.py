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


def test_update_user_active_status_record_reactivates_user(db_session, make_user):
    admin = make_user(
        email="admin.reactivate@hospital.local",
        full_name="Admin Reactivate",
        role="admin",
    )

    target_user = make_user(
        email="target.reactivate@hospital.local",
        full_name="Target Reactivate",
        role="monitor_staff",
        is_active=False,
    )

    req = SimpleNamespace(is_active=True)

    result = update_user_active_status_record(
        user_id=target_user.id,
        req=req,
        current_user=admin,
    )

    assert result["message"] == "user_active_status_updated"
    assert result["user"]["is_active"] is True

    db_session.refresh(target_user)
    assert target_user.is_active is True

def test_update_user_active_status_record_blocks_admin_self_deactivation(make_user):
    admin = make_user(
        email="self.admin@hospital.local",
        full_name="Self Admin",
        role="admin",
    )

    req = SimpleNamespace(is_active=False)

    with pytest.raises(HTTPException) as exc:
        update_user_active_status_record(
            user_id=admin.id,
            req=req,
            current_user=admin,
        )

    assert exc.value.status_code == 400
    assert exc.value.detail == "admin_cannot_deactivate_self"

def test_update_user_active_status_record_rejects_missing_user(make_user):
    admin = make_user(
        email="admin.missing.user@hospital.local",
        full_name="Admin Missing User",
        role="admin",
    )

    req = SimpleNamespace(is_active=False)

    with pytest.raises(HTTPException) as exc:
        update_user_active_status_record(
            user_id=9999,
            req=req,
            current_user=admin,
        )

    assert exc.value.status_code == 404
    assert exc.value.detail == "user_not_found"

def test_test_user_does_not_count_as_active_admin_for_admin_safety_policy(
    db_session,
    make_user,
):
    admin = make_user(
        email="only-admin@hospital.local",
        full_name="Only Admin",
        role="admin",
        is_active=True,
    )

    make_user(
        email="active-test-user@hospital.local",
        full_name="Active Test User",
        role="test_user",
        is_active=True,
    )

    assert count_active_admins(db_session) == 1
    assert is_last_active_admin(db_session, admin) is True
