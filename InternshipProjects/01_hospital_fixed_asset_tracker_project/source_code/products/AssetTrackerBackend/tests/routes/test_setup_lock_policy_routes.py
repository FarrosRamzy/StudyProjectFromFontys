"""
File: test_setup_lock_policy_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Route tests for first-administrator setup and permanent setup-lock behavior.
Version: 0.1
Date: 2026-06-05

Copyright (c) 2026
"""

from app.db_models import SystemSetting, User
from app.routes.auth import router as auth_router
from app.services.authority.auth_service import hash_password
from app.services.setup.setup_flag_service import FIRST_ADMIN_SETUP_KEY


def test_setup_status_marks_completed_when_admin_exists(
    db_session, make_user, make_route_client
):
    make_user(email="admin@hospital.local", role="admin")
    client = make_route_client([auth_router])

    response = client.get("/auth/setup-status")

    assert response.status_code == 200
    assert response.json() == {"setup_required": False}
    setting = (
        db_session.query(SystemSetting).filter_by(key=FIRST_ADMIN_SETUP_KEY).first()
    )
    assert setting is not None
    assert setting.value == "true"


def test_setup_admin_stays_locked_after_all_admins_deleted(
    db_session, make_route_client
):
    db_session.add(SystemSetting(key=FIRST_ADMIN_SETUP_KEY, value="true"))
    db_session.commit()
    client = make_route_client([auth_router])

    status_response = client.get("/auth/setup-status")
    create_response = client.post(
        "/auth/setup-admin",
        json={
            "email": "admin@hospital.local",
            "full_name": "System Admin",
            "password": "Password12345!",
        },
    )

    assert status_response.json() == {"setup_required": False}
    assert create_response.status_code == 403
    assert create_response.json()["detail"] == "admin_setup_already_completed"


def test_setup_admin_creates_first_admin_and_locks_setup(db_session, make_route_client):
    client = make_route_client([auth_router])

    response = client.post(
        "/auth/setup-admin",
        json={
            "email": "admin@hospital.local",
            "full_name": "System Admin",
            "password": "Password12345!",
        },
    )

    assert response.status_code == 201
    assert response.json()["user"]["role"] == "admin"
    setting = (
        db_session.query(SystemSetting).filter_by(key=FIRST_ADMIN_SETUP_KEY).first()
    )
    assert setting is not None
    assert setting.value == "true"
