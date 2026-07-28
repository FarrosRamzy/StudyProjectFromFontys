"""
File: ws.py
Author: Farros Ramzy (you@domain.com)
Description: Authenticated WebSocket endpoint for realtime asset and node updates.
Version: 0.2
Date: 2026-04-21

Copyright (c) 2026
"""

import traceback

from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from fastapi.encoders import jsonable_encoder

# from app.storage import assets, nodes       # (can be used for offline data testing)
from app.database import SessionLocal
from app.db_models import Asset, Node, User
from app.websocket_manager import ws_manager
from app.serializers.asset_serializer import asset_to_dict
from app.serializers.node_serializer import node_to_dict
from app.services.authority.auth_service import decode_access_token

router = APIRouter(tags=["websocket"])


@router.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket) -> None:
    """WebSocket endpoint for live monitor updates.

    Args:
        websocket (WebSocket): Active websocket connection.
    """
    token = websocket.query_params.get("token")
    user = get_user_from_ws_token(token)

    if user is None or not user.is_active:
        await websocket.close(code=1008)
        return

    await ws_manager.connect(websocket)

    try:
        db = SessionLocal()

        try:
            db_assets = db.query(Asset).all()
            db_nodes = db.query(Node).all()

            snapshot = {
                "type": "snapshot",
                "assets": [asset_to_dict(asset) for asset in db_assets],
                "nodes": [node_to_dict(node) for node in db_nodes],
            }
        finally:
            db.close()

        await websocket.send_json(jsonable_encoder(snapshot))

        while True:
            message = await websocket.receive_text()

            if message == "ping":
                await websocket.send_text("pong")

    except WebSocketDisconnect:
        print("[WS] Client disconnected normally.")

    except Exception as exc:
        print(f"[WS] Error: {exc}")
        traceback.print_exc()

    finally:
        await ws_manager.disconnect(websocket)


def get_user_from_ws_token(token: str | None):
    if not token:
        return None

    payload = decode_access_token(token)

    if payload is None:
        return None

    user_id = payload.get("sub")

    if user_id is None:
        return None

    db = SessionLocal()

    try:
        return db.query(User).filter(User.id == int(user_id)).first()
    finally:
        db.close()
