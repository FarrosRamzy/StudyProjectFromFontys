/**
 * @file movementRequestHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { isNodeOnline } from "../../../utils/nodeHelpers";

export function normalizeMovementRequests(result) {
    return Array.isArray(result) ? result : result?.movement_requests ?? [];
}

export function upsertAssetByTagId(currentAssets, updatedAsset) {
    if (!updatedAsset?.tag_id) {
        return currentAssets;
    }

    const exists = currentAssets.some((asset) => asset.tag_id === updatedAsset.tag_id);
    if (!exists) {
        return [updatedAsset, ...currentAssets];
    }

    return currentAssets.map((asset) =>
        asset.tag_id === updatedAsset.tag_id ? updatedAsset : asset
    );
}

export function selectedRegistrationNodeIsOnline({ registrationNodes, registrationNodeId }) {
    const node = registrationNodes.find((item) => item.device_id === registrationNodeId);
    return Boolean(node && isNodeOnline(node));
}

export function validateMovementAction({ request, registrationNodeId, registrationNodes, setError, actionName }) {
    if (!request?.id || !registrationNodeId) {
        setError(`Select a registration node before ${actionName} movement.`);
        return false;
    }

    if (!selectedRegistrationNodeIsOnline({ registrationNodes, registrationNodeId })) {
        setError("The selected registration node is offline. Choose an online registration node.");
        return false;
    }

    return true;
}

export function removeMovementRequest(currentRequests, requestId) {
    return currentRequests.filter((item) => item.id !== requestId);
}

export function normalizeStatus(value) {
    return String(value || "").trim().toUpperCase();
}

export function isOnlineRegistrationNode(node) {
    return normalizeStatus(node?.status) === "ONLINE";
}

export function getNodeLabel(node) {
    return [node.alias || node.name || "Registration Desk", node.room_name, node.device_id]
        .filter(Boolean)
        .join(" — ");
}
