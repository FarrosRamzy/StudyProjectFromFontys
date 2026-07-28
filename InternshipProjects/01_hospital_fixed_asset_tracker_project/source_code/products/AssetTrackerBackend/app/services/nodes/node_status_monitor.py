"""
File: node_status_monitor.py
Author: Farros Ramzy (you@domain.com)
Description: Periodically detects heartbeat timeouts and marks inactive nodes offline.
Version: 0.5
Date: 2026-04-20

Copyright (c) 2026
"""

import os
import threading
import time
from datetime import timedelta

from app.database import SessionLocal
from app.db_models import Node
from app.utils import now_wib, parse_timestamp
from app.serializers.node_serializer import node_to_dict
from app.services.realtime.broadcast_service import schedule_broadcast
from app.services.nodes.node_demo_policy import should_skip_offline_timeout

OFFLINE_TIMEOUT_SECONDS = int(os.getenv("NODE_OFFLINE_TIMEOUT_SECONDS", "90"))
CHECK_INTERVAL_SECONDS = int(os.getenv("NODE_STATUS_CHECK_INTERVAL_SECONDS", "5"))

_monitor_started = False
_monitor_lock = threading.Lock()


def check_offline_nodes() -> None:
    db = SessionLocal()

    try:
        print("[NodeStatusMonitor] checking nodes...")
        now = now_wib()
        nodes = db.query(Node).filter(Node.is_provisioned == True).all()

        for node in nodes:
            node_status = str(node.status or "").strip().upper()
            
            if node_status == "DISABLED":
                continue

            if node_status == "ONLINE" and should_skip_offline_timeout(node):
                node.last_ping_at = now
                node.last_event_at = now
                node.last_message = "dummy heartbeat simulated"

                db.add(node)
                db.commit()
                db.refresh(node)

                print(
                    "[NodeStatusMonitor]",
                    node.device_id,
                    "dummy heartbeat refreshed",
                )

                continue

            reference_time = node.last_ping_at or node.last_event_at

            if not reference_time:
                continue

            elapsed = now - parse_timestamp(reference_time)

            print(
                "[NodeStatusMonitor]",
                node.device_id,
                node.status,
                "last_ping_at:",
                reference_time,
                "elapsed:",
                elapsed,
            )

            if elapsed > timedelta(seconds=OFFLINE_TIMEOUT_SECONDS):
                if node.status != "OFFLINE":
                    node.status = "OFFLINE"
                    node.last_message = "heartbeat timeout"
                    node.last_event_at = now

                    db.add(node)
                    db.commit()
                    db.refresh(node)

                    schedule_broadcast(
                        {
                            "type": "node_offline",
                            "node": node_to_dict(node),
                        }
                    )

    finally:
        db.close()


def node_status_monitor_loop() -> None:
    while True:
        try:
            check_offline_nodes()
        except Exception as exc:
            print(f"[NodeStatusMonitor] Error: {exc}")

        time.sleep(CHECK_INTERVAL_SECONDS)


def start_node_status_monitor() -> None:
    global _monitor_started
    with _monitor_lock:
        if _monitor_started:
            print("[NodeStatusMonitor] Already started. Skipping duplicate startup.")
            return

        thread = threading.Thread(
            target=node_status_monitor_loop,
            daemon=True,
            name="node-status-monitor",
        )
        thread.start()
        _monitor_started = True
