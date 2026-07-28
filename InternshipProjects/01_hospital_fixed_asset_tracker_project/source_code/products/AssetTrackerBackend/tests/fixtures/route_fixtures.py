"""
File: route_fixtures.py
Author: Farros Ramzy (you@domain.com)
Description: Route-test helper fixtures.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from typing import Iterable

import pytest
from fastapi import FastAPI
from fastapi.testclient import TestClient

from app.services.authority.auth_service import create_access_token


@pytest.fixture()
def make_route_client():
    def _make_route_client(routers: Iterable):
        test_app = FastAPI()

        for router in routers:
            test_app.include_router(router)

        return TestClient(test_app)

    return _make_route_client


@pytest.fixture()
def auth_header():
    def _auth_header(user):
        token = create_access_token(
            {
                "sub": str(user.id),
                "email": user.email,
                "role": user.role,
            }
        )

        return {
            "Authorization": f"Bearer {token}",
        }

    return _auth_header
