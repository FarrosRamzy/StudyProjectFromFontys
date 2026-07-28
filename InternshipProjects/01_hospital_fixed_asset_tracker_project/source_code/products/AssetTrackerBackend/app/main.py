"""
File: main.py
Author: Farros Ramzy (you@domain.com)
Description: Asset Tracker Backend entrypoint
Version: 1.0
Date: 2026-04-30

Copyright (c) 2026
"""

import os
import asyncio
from app.services.realtime.broadcast_service import set_main_loop
from app.services.mqtt.mqtt_client import start_mqtt_background_worker
from app.services.nodes.node_status_monitor import start_node_status_monitor

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from app.routes.assets import router as assets_router
from app.routes.nodes import router as nodes_router
from app.routes.users import router as users_router
from app.routes.ws import router as ws_router
from app.routes.auth import router as auth_router
from app.routes.settings import router as settings_router
from app.database import Base, engine

APP_ENV = os.getenv("APP_ENV", "development").strip().lower()
ENABLE_API_DOCS = os.getenv("ENABLE_API_DOCS", "").strip().lower()


def should_enable_api_docs() -> bool:
    if ENABLE_API_DOCS in {"true", "1", "yes", "on"}:
        return True

    if ENABLE_API_DOCS in {"false", "0", "no", "off"}:
        return False

    return APP_ENV in {"development", "local", "dev"}


docs_enabled = should_enable_api_docs()

app = FastAPI(
    title="Hospital Asset Tracker Backend",
    version="0.1.0",
    docs_url="/docs" if docs_enabled else None,
    redoc_url="/redoc" if docs_enabled else None,
    openapi_url="/openapi.json" if docs_enabled else None,
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=[
        "http://localhost:5173",  # React dev registration server
        "http://127.0.0.1:5173",
        "http://localhost:5174",  # React dev asset and node monitor server
        "http://127.0.0.1:5174",
        "http://localhost:5175",  # React dev test server
        "http://127.0.0.1:5175",
        "https://rfid-hospital-asset-tracker-registration.onrender.com",  # Registration App Production
        "https://rfid-hospital-asset-tracker-monitor.onrender.com",  # Monitor App Production
    ],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(assets_router)
app.include_router(nodes_router)
app.include_router(auth_router)
app.include_router(users_router)
app.include_router(settings_router)
app.include_router(ws_router)


@app.on_event("startup")
async def startup_event():
    set_main_loop(asyncio.get_running_loop())  # Store main event loop
    Base.metadata.create_all(bind=engine)  # Initialize DB
    start_mqtt_background_worker()  # Start MQTT listener
    start_node_status_monitor()


@app.get("/")
def root() -> dict[str, str]:
    """Return the backend service message.

    Returns:
        dict[str, str]: [description]
    """
    return {"message": "Asset Tracker Backend is Running"}


@app.get("/health")
def health() -> dict[str, str]:
    """Return a lightweight health-check response.

    Returns:
        dict[str, str]: [description]
    """
    return {"status": "ok"}
