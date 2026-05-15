"""
File: ws.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.2
Date: 2026-04-21

Copyright (c) 2026
"""

import traceback

from fastapi import APIRouter, WebSocket, WebSocketDisconnect
from fastapi.encoders import jsonable_encoder

# from app.storage import assets, nodes
from app.database import SessionLocal
from app.db_models import Asset, Node
from app.websocket_manager import ws_manager
from app.serializers.asset_serializer import asset_to_dict
from app.serializers.node_serializer import node_to_dict

router = APIRouter(tags=["websocket"])


@router.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket) -> None:
    """WebSocket endpoint for live monitor updates.

    Args:
        websocket (WebSocket): Active websocket connection.
    """
    print("[WS] /ws endpoint hit")
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
            await websocket.receive_text()

    except WebSocketDisconnect:
        print("[WS] Client disconnected normally.")

    except Exception as exc:
        print(f"[WS] Error: {exc}")
        traceback.print_exc()

    finally:
        ws_manager.disconnect(websocket)
