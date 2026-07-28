"""
File: cleanup_dummy_nodes.py
Author: Farros Ramzy (you@domain.com)
Description: Deletes dummy nodes created by seed_dummy_nodes.py.

Usage:
    python scripts/cleanup_dummy_nodes.py
    python scripts/cleanup_dummy_nodes.py --force
    
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
from app.db_models import Node
from scripts.dummy_data.dummy_node_payloads import DUMMY_NODE_PREFIX
from scripts.dummy_data.dummy_node_service import count_node_asset_references


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--force",
        action="store_true",
        help="Delete dummy nodes even when assets reference them.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    db = SessionLocal()

    try:
        nodes = (
            db.query(Node).filter(Node.device_id.like(f"{DUMMY_NODE_PREFIX}%")).all()
        )

        deleted_count = 0
        skipped_count = 0

        for node in nodes:
            ref_count = count_node_asset_references(db, node.device_id)

            if ref_count > 0 and not args.force:
                skipped_count += 1
                continue

            db.delete(node)
            deleted_count += 1

        db.commit()

        print(f"Deleted {deleted_count} dummy nodes.")
        print(f"Skipped {skipped_count} referenced dummy nodes.")

    except Exception as exc:
        db.rollback()
        print(f"Failed to delete dummy nodes: {exc}")
        raise

    finally:
        db.close()


if __name__ == "__main__":
    main()
