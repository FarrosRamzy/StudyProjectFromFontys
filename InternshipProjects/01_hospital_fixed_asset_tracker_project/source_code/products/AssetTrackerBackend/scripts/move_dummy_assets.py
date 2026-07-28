"""
File: move_dummy_assets.py
Author: Farros Ramzy (you@domain.com)
Description: Moves dummy assets to another checkpoint room directly in the database.
Usage examples:
    python scripts/move_dummy_assets.py
    python scripts/move_dummy_assets.py --to "ICU Room 1"
    python scripts/move_dummy_assets.py --to "Ground Floor Storage" --count 10
Version: 0.1
Date: 2026-05-25

Copyright (c) 2026
"""

import argparse
import sys
from pathlib import Path

BACKEND_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(BACKEND_ROOT))

from app.database import SessionLocal
from scripts.dummy_data.dummy_asset_move_modes import apply_dummy_move
from scripts.dummy_data.dummy_asset_move_queries import (
    get_checkpoint_nodes,
    get_destination_node,
    get_dummy_assets,
)


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--to",
        dest="destination_room",
        default="",
        help="Destination checkpoint room. If omitted, a random room is used.",
    )
    parser.add_argument(
        "--count",
        type=int,
        default=10,
        help="Number of dummy assets to move.",
    )
    parser.add_argument(
        "--mode",
        choices=["authorized", "unauthorized", "in-place", "return"],
        default="unauthorized",
        help="Movement simulation mode.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    db = SessionLocal()

    try:
        moved_count, destination_node = move_dummy_assets(db, args)
        db.commit()
        print_move_result(moved_count, destination_node, args.mode)

    except Exception as exc:
        db.rollback()
        print(f"Failed to move dummy assets: {exc}")
        raise

    finally:
        db.close()


def move_dummy_assets(db, args):
    if not get_checkpoint_nodes(db):
        raise ValueError("No checkpoint nodes found.")

    destination_node = get_destination_node(db, args.destination_room)

    if destination_node is None:
        raise ValueError(f"No checkpoint node found for room: {args.destination_room}")

    dummy_assets = get_dummy_assets(db, args.count)

    if not dummy_assets:
        raise ValueError("No dummy assets found.")

    for asset in dummy_assets:
        apply_dummy_move(asset, destination_node, args.mode)
        db.add(asset)

    return len(dummy_assets), destination_node


def print_move_result(moved_count: int, destination_node, mode: str) -> None:
    print(
        f"Moved {moved_count} dummy assets to "
        f"{destination_node.room_name} ({destination_node.device_id}) "
        f"using mode: {mode}"
    )


if __name__ == "__main__":
    main()
