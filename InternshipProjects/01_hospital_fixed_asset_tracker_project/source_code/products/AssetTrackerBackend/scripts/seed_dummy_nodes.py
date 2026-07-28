"""
File: seed_dummy_nodes.py
Author: Farros Ramzy (you@domain.com)
Description: Creates or updates dummy node records for development and system testing.
Usage:
    python scripts/seed_dummy_nodes.py
    python scripts/seed_dummy_nodes.py --status ASSIGNED
    python scripts/seed_dummy_nodes.py --status ONLINE
    python scripts/seed_dummy_nodes.py --discovered 3
Version: 0.1
Date: 2026-06-02

Copyright (c) 2026
"""

import argparse
import sys
from pathlib import Path

BACKEND_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(BACKEND_ROOT))

from app.database import SessionLocal
from scripts.dummy_data.dummy_node_payloads import (
    make_checkpoint_nodes,
    make_discovered_nodes,
    make_registration_nodes,
)
from scripts.dummy_data.dummy_node_service import upsert_dummy_node


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--status",
        choices=["ASSIGNED", "ONLINE", "OFFLINE"],
        default="ASSIGNED",
        help="Status for provisioned dummy nodes.",
    )
    parser.add_argument(
        "--discovered",
        type=int,
        default=2,
        help="Number of unprovisioned DISCOVERED dummy nodes.",
    )
    parser.add_argument(
        "--device-id",
        default="",
        help="Only update one dummy node by device_id.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    db = SessionLocal()

    try:
        payloads = []
        payloads.extend(make_registration_nodes())
        payloads.extend(make_checkpoint_nodes())
        payloads.extend(make_discovered_nodes(args.discovered))

        if args.device_id:
            payloads = [
                item for item in payloads if item["device_id"] == args.device_id
            ]

            if not payloads:
                raise ValueError(f"Unknown dummy device_id: {args.device_id}")

        created_or_updated = 0

        updated_nodes = []

        for payload in payloads:
            node = upsert_dummy_node(db, payload, args.status)
            updated_nodes.append(node.device_id)
            created_or_updated += 1

        db.commit()
        print(f"Seeded {created_or_updated} dummy nodes.")

        for device_id in updated_nodes:
            print(f"- {device_id}: {args.status}")

    except Exception as exc:
        db.rollback()
        print(f"Failed to seed dummy nodes: {exc}")
        raise

    finally:
        db.close()


if __name__ == "__main__":
    main()
