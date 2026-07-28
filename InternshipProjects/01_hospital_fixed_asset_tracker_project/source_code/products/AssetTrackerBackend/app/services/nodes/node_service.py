"""
File: node_service.py
Author: Farros Ramzy (you@domain.com)
Description: Compatibility facade for node services.
                Old imports can still use:
                from app.services.nodes.node_service import list_nodes
Version: 2.0
Date: 2026-05-28

Copyright (c) 2026
"""

from app.services.nodes.node_queries import (
    list_nodes,
    get_provision_payload,
)
from app.services.nodes.node_lifecycle_service import (
    enroll_node_record,
    unassign_node_record,
    delete_node_record,
)
from app.services.nodes.node_reference_service import (
    find_node_reference_blockers,
)

__all__ = [
    "delete_node_record",
    "enroll_node_record",
    "find_node_reference_blockers",
    "get_provision_payload",
    "list_nodes",
    "unassign_node_record",
]
