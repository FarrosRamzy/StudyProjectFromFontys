"""
File: cleanup_dummy_assets.py
Author: Farros Ramzy (you@domain.com)
Description: Deletes dummy assets created by seed_dummy_assets.py.
Usage: python scripts/cleanup_dummy_assets.py
Version: 0.1
Date: 2026-05-25

Copyright (c) 2026
"""

from app.database import SessionLocal
from app.db_models import Asset

DUMMY_TAG_PREFIX = "DUMMYEPC"


def main():
    db = SessionLocal()

    try:
        deleted_count = (
            db.query(Asset)
            .filter(Asset.tag_id.like(f"{DUMMY_TAG_PREFIX}%"))
            .delete(synchronize_session=False)
        )

        db.commit()

        print(f"Deleted {deleted_count} dummy assets.")

    except Exception as exc:
        db.rollback()
        print(f"Failed to delete dummy assets: {exc}")
        raise

    finally:
        db.close()


if __name__ == "__main__":
    main()
