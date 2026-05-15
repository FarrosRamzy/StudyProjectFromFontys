"""
File: asset_repository.py
Author: Farros Ramzy (you@domain.com)
Description: Description
Version: 0.1
Date: 2026-05-12

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Asset


def list_assets():
    db = SessionLocal()
    try:
        return db.query(Asset).all()
    finally:
        db.close()


def get_asset_by_tag(tag_id: str):
    db = SessionLocal()
    try:
        return db.query(Asset).filter(Asset.tag_id == tag_id).first()
    finally:
        db.close()


def delete_asset_record(tag_id: str):
    db = SessionLocal()

    try:
        asset = db.query(Asset).filter(Asset.tag_id == tag_id).first()

        if asset is None:
            return {"message": "asset_not_found"}

        if asset.status != "deregistered":
            return {
                "message": "asset_must_be_deregistered_first",
            }

        db.delete(asset)
        db.commit()

        return {
            "message": "asset_deleted",
            "tag_id": tag_id,
        }

    finally:
        db.close()