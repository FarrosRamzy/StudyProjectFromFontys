"""
File: asset_service.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-04-23

Copyright (c) 2026
"""

from app.services.assets.asset_repository import (
    delete_asset_record,
    get_asset_by_tag,
    list_assets,
)

from app.services.assets.asset_location_service import (
    update_asset_location,
)

from app.services.assets.asset_registration_service import (
    deregister_asset_record,
    register_asset_record,
)


__all__ = [
    "list_assets",
    "get_asset_by_tag",
    "update_asset_location",
    "register_asset_record",
    "deregister_asset_record",
    "delete_asset_record",
]

# from datetime import datetime
# from app.database import SessionLocal
# from app.db_models import Asset
# from app.db_models import Node
# from app.utils import now_wib
# from app.utils import parse_timestamp
# from app.services.asset_event_service import create_asset_event


# def list_assets():
#     db = SessionLocal()
#     try:
#         return db.query(Asset).all()
#     finally:
#         db.close()


# def get_asset_by_tag(tag_id: str):
#     db = SessionLocal()
#     try:
#         return db.query(Asset).filter(Asset.tag_id == tag_id).first()
#     finally:
#         db.close()


# def update_asset_location(
#     tag_id: str,
#     device_id: str,
#     room_name: str,
#     hospital_id: str,
#     hospital_name: str,
#     timestamp: datetime,
# ):
#     db = SessionLocal()
#     try:
#         asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

#         if not asset:
#             return {
#                 "status": "unknown",
#                 "asset": None,
#             }

#         if asset.status != "active":
#             return {
#                 "status": "inactive",
#                 "asset": asset,
#             }

#         last_seen_at = asset.last_seen_at

#         if isinstance(last_seen_at, str):
#             try:
#                 last_seen_at = datetime.fromisoformat(last_seen_at)
#             except ValueError:
#                 last_seen_at = None

#         if last_seen_at and timestamp <= last_seen_at:
#             return {
#                 "status": "stale",
#                 "asset": asset,
#             }

#         asset.hospital_id = hospital_id
#         asset.hospital_name = hospital_name
#         asset.last_room_name = room_name
#         asset.last_device_id = device_id
#         asset.last_node_id = device_id
#         asset.last_seen_at = timestamp

#         db.add(asset)
#         db.commit()
#         db.refresh(asset)

#         return {
#             "status": "updated",
#             "asset": asset,
#         }
#     finally:
#         db.close()


# def register_asset_record(tag_id: str, item_name: str, registration_node_id: str):
#     db = SessionLocal()

#     hospital_name = ""
#     room_name = ""
#     event_time = now_wib()

#     try:
#         node = db.query(Node).filter(Node.device_id == registration_node_id).first()

#         if not node or node.role != "REGISTRATION":
#             return None

#         hospital_name = node.hospital_name or ""
#         hospital_id = node.hospital_id or ""
#         room_name = node.room_name or "REGISTRATION_DESK"

#         asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

#         if asset is None:
#             asset = Asset(tag_id=tag_id)

#         asset.item_name = item_name
#         asset.status = "active"
#         asset.hospital_id = hospital_id
#         asset.hospital_name = hospital_name
#         asset.last_room_name = room_name
#         asset.last_device_id = registration_node_id
#         asset.last_node_id = registration_node_id
#         asset.registered_at = asset.registered_at or event_time
#         asset.last_seen_at = now_wib()

#         db.add(asset)
#         db.commit()
#         db.refresh(asset)

#         asset_data = asset

#     finally:
#         db.close()

#     create_asset_event(
#         tag_id=tag_id,
#         device_id=registration_node_id,
#         hospital_id=hospital_id,
#         hospital_name=hospital_name,
#         room_name=room_name,
#         event_type="REGISTER",
#         timestamp=event_time,
#         raw_payload={
#             "tag_id": tag_id,
#             "item_name": item_name,
#             "registration_node_id": registration_node_id,
#         },
#     )
#     return asset_data


# def deregister_asset_record(tag_id: str, registration_node_id: str, reason: str = ""):
#     db = SessionLocal()

#     hospital_id = ""
#     hospital_name = ""
#     room_name = ""
#     event_time = now_wib()

#     try:
#         node = db.query(Node).filter(Node.device_id == registration_node_id).first()

#         if not node or node.role != "REGISTRATION":
#             return None

#         hospital_id = node.hospital_id or ""
#         hospital_name = node.hospital_name or ""
#         room_name = node.room_name or "REGISTRATION_DESK"

#         asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

#         if asset is None:
#             return None

#         asset.status = "deregistered"
#         asset.last_seen_at = event_time
#         asset.last_node_id = registration_node_id
#         asset.last_device_id = registration_node_id

#         db.add(asset)
#         db.commit()
#         db.refresh(asset)

#     finally:
#         db.close()

#     create_asset_event(
#         tag_id=tag_id,
#         device_id=registration_node_id,
#         hospital_id=hospital_id,
#         hospital_name=hospital_name,
#         room_name=room_name,
#         event_type="DEREGISTER",
#         timestamp=event_time,
#         raw_payload={
#             "tag_id": tag_id,
#             "registration_node_id": registration_node_id,
#             "reason": reason,
#         },
#     )

#     return asset


# def delete_asset_record(tag_id: str):
#     db = SessionLocal()

#     try:
#         asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

#         if asset is None:
#             return {"message": "asset_not_found"}

#         if asset.status != "deregistered":
#             return {
#                 "message": "asset_must_be_deregistered_first",
#             }

#         db.delete(asset)
#         db.commit()

#         return {
#             "message": "asset_deleted",
#             "tag_id": tag_id,
#         }

#     finally:
#         db.close()
