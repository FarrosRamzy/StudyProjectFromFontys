"""
File: database_fixtures.py
Author: Farros Ramzy (you@domain.com)
Description: Database fixtures for backend tests.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from tests.fixtures.test_environment import configure_test_environment

configure_test_environment()

from app.database import Base


@pytest.fixture(scope="session")
def test_engine():
    engine = create_engine(
        "sqlite:///./test_asset_tracker.db",
        connect_args={"check_same_thread": False},
    )

    Base.metadata.drop_all(bind=engine)
    Base.metadata.create_all(bind=engine)

    yield engine

    Base.metadata.drop_all(bind=engine)


@pytest.fixture(scope="session")
def TestingSessionLocal(test_engine):
    return sessionmaker(
        bind=test_engine,
        autoflush=False,
        autocommit=False,
        expire_on_commit=False,
    )


@pytest.fixture()
def db_session(test_engine, TestingSessionLocal):
    session = TestingSessionLocal()

    try:
        for table in reversed(Base.metadata.sorted_tables):
            session.execute(table.delete())

        session.commit()

        yield session

    finally:
        session.rollback()
        session.close()
