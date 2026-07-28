"""
File: seed_dummy_assets.py
Author: Farros Ramzy (you@domain.com)
Description: Seeds dummy hospital assets directly into the
             database for monitor testing.
Usage: python scripts/seed_dummy_assets.py
Version: 0.1
Date: 2026-05-25

Copyright (c) 2026
"""

import random
from app.utils import now_wib
from app.database import SessionLocal
from app.db_models import Asset, Node

DUMMY_ASSET_COUNT = 50

DUMMY_ASSET_NAMES = [
    "Infusion Pump",
    "Patient Monitor",
    "Wheelchair",
    "Defibrillator",
    "Ventilator",
    "ECG Machine",
    "Syringe Pump",
    "Oxygen Cylinder",
    "Ultrasound Scanner",
    "Portable Suction Unit",
    "Hospital Bed",
    "Transport Stretcher",
    "Anesthesia Machine",
    "Blood Pressure Monitor",
    "Pulse Oximeter",
]


def make_dummy_tag(index: int) -> str:
    """
    Creates a fake UHF-like EPC tag ID.
    Keep it unique and clearly marked as dummy.
    """
    return f"DUMMYEPC{index:04d}{random.randint(1_000_000_000_000_000, 9_999_999_999_999_999)}"


def get_checkpoint_nodes(db):
    return (
        db.query(Node)
        .filter(
            Node.is_provisioned == True,  # noqa: E712
            Node.role == "CHECKPOINT",
        )
        .all()
    )


def asset_exists(db, tag_id: str) -> bool:
    return db.query(Asset).filter(Asset.tag_id == tag_id).first() is not None


def create_dummy_asset(index: int, node: Node) -> Asset:
    asset_name = random.choice(DUMMY_ASSET_NAMES)

    return Asset(
        tag_id=make_dummy_tag(index),
        item_name=f"{asset_name} Dummy {index:03d}",
        status="active",
        # Location state
        flow_status="available",
        movement_note="Dummy asset seeded for database and monitor testing.",
        # Assigned official location
        assigned_room_name=node.room_name or "",
        assigned_node_id=node.device_id or "",
        # Current detected location
        last_room_name=node.room_name or "",
        last_node_id=node.device_id or "",
        last_device_id=node.device_id or "",
        # No active movement
        expected_room_name="",
        expected_node_id="",
        active_movement_request_id=None,
        # Hospital information
        hospital_id=node.hospital_id or "",
        hospital_name=node.hospital_name or "",
        # Timestamps
        registered_at=now_wib(),
        last_seen_at=now_wib(),
        deregistered_at=None,
    )


def main():
    db = SessionLocal()

    try:
        checkpoint_nodes = get_checkpoint_nodes(db)

        if not checkpoint_nodes:
            print(
                "No provisioned checkpoint nodes found. "
                "Please register at least one checkpoint node first."
            )
            return

        created_count = 0

        for index in range(1, DUMMY_ASSET_COUNT + 1):
            node = random.choice(checkpoint_nodes)
            dummy_asset = create_dummy_asset(index, node)

            while asset_exists(db, dummy_asset.tag_id):
                dummy_asset.tag_id = make_dummy_tag(index)

            db.add(dummy_asset)
            created_count += 1

        db.commit()

        print(f"Created {created_count} dummy assets successfully.")

    except Exception as exc:
        db.rollback()
        print(f"Failed to seed dummy assets: {exc}")
        raise

    finally:
        db.close()


if __name__ == "__main__":
    main()
