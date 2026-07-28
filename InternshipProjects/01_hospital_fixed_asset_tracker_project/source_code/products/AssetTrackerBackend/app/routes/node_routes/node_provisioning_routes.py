"""
File: node_provisioning_routes.py
Author: Farros Ramzy (you@domain.com)
Description: Node provisioning routes.
Version: 0.1
Date: 2026-05-28

Copyright (c) 2026
"""

import os

from fastapi import APIRouter, Depends, Header, HTTPException, status

from app.models import ProvisionNodeRequest
from app.services.nodes.node_service import get_provision_payload

router = APIRouter(tags=["nodes"])

NODE_PROVISIONING_KEY = os.getenv("NODE_PROVISIONING_KEY", "")


def verify_node_provisioning_key(
    x_device_provisioning_key: str = Header(default=""),
) -> None:
    if not NODE_PROVISIONING_KEY:
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="node_provisioning_key_not_configured",
        )

    if x_device_provisioning_key != NODE_PROVISIONING_KEY:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="invalid_node_provisioning_key",
        )


@router.post("/nodes/provision")
def provision_node(
    req: ProvisionNodeRequest,
    _: None = Depends(verify_node_provisioning_key),
):
    return get_provision_payload(req.device_id)
