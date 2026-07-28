"""
File: dummy_asset_move_queries.py
Author: Farros Ramzy (you@domain.com)
Description: Query helpers for dummy asset movement scripts.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

import random

from app.db_models import Asset, Node

DUMMY_TAG_PREFIX = "DUMMYEPC"


def get_checkpoint_nodes(db):
    return (
        db.query(Node)
        .filter(
            Node.is_provisioned == True,  # noqa: E712
            Node.role == "CHECKPOINT",
        )
        .all()
    )


def get_destination_node(db, room_name):
    query = db.query(Node).filter(
        Node.is_provisioned == True,  # noqa: E712
        Node.role == "CHECKPOINT",
    )

    if room_name:
        query = query.filter(Node.room_name == room_name)

    nodes = query.all()

    if not nodes:
        return None

    return random.choice(nodes)


def get_dummy_assets(db, count: int):
    return (
        db.query(Asset)
        .filter(
            Asset.tag_id.like(f"{DUMMY_TAG_PREFIX}%"),
            Asset.status == "active",
        )
        .limit(count)
        .all()
    )
