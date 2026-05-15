"""
File: main.py
Author: Farros Ramzy (you@domain.com)
Description: Asset Tracker Backend entrypoint
Version: 1.0
Date: 2026-04-30

Copyright (c) 2026
"""

import asyncio
from app.services.realtime.broadcast_service import set_main_loop
from app.services.mqtt.mqtt_client import start_mqtt_background_worker
from app.services.nodes.node_status_monitor import start_node_status_monitor

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from app.routes.assets import router as assets_router
from app.routes.nodes import router as nodes_router
from app.routes.ws import router as ws_router
from app.database import engine
from app.db_models import Base

app = FastAPI(title="Hospital Asset Tracker Backend")

app.add_middleware(
    CORSMiddleware,
    allow_origins=[
        "http://localhost:5173",  # React dev node server
        "http://127.0.0.1:5173",
        
        "http://localhost:5174",  # React dev asset server
        "http://127.0.0.1:5174",
        
        "http://localhost:5175",  # React dev monitor server
        "http://127.0.0.1:5175",
    ],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(assets_router)
app.include_router(nodes_router)
app.include_router(ws_router)


@app.on_event("startup")
async def startup_event():
    # Store main event loop
    set_main_loop(asyncio.get_running_loop())
    # Initialize DB
    Base.metadata.create_all(bind=engine)
    # Start MQTT listener
    start_mqtt_background_worker()
    start_node_status_monitor()
    

@app.get("/")
def root() -> dict[str, str]:
    """AI is creating summary for root

    Returns:
        dict[str, str]: [description]
    """
    return {"message": "Asset Tracker Backend is Running"}


@app.get("/health")
def health() -> dict[str, str]:
    """AI is creating summary for health

    Returns:
        dict[str, str]: [description]
    """
    return {"status": "ok"}
