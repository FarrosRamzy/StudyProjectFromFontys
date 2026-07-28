/**
 * @file flowStatus.js
 * @author Farros Ramzy (you@domain.com)
 * @description Asset flow status helpers for monitor UI.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { ASSET_FLOW_STATUS, ASSET_FLOW_STATUS_META } from "../constants/assetFlowStatus";

export { ASSET_FLOW_STATUS, ASSET_FLOW_STATUS_META };

export function normalizeFlowStatus(flowStatus) {
    return String(flowStatus || "").trim().toLowerCase();
}

export function getAssetFlowMeta(flowStatus) {
    const normalized = normalizeFlowStatus(flowStatus);
    return ASSET_FLOW_STATUS_META[normalized] || {
        label: normalized || "Unknown",
        tone: "neutral",
        rowClass: "",
        severity: "unknown",
        description: "Unknown asset movement status.",
    };
}

export function getAssetFlowLabel(flowStatus) {
    return getAssetFlowMeta(flowStatus).label;
}

export function getAssetFlowTone(flowStatus) {
    return getAssetFlowMeta(flowStatus).tone;
}

export function getAssetFlowRowClass(flowStatus) {
    return getAssetFlowMeta(flowStatus).rowClass;
}

export function getAssetFlowSeverity(flowStatus) {
    return getAssetFlowMeta(flowStatus).severity;
}

export function isAssetAvailableForMovement(asset) {
    return Boolean(
        asset?.status === "active" &&
        normalizeFlowStatus(asset.flow_status) === ASSET_FLOW_STATUS.AVAILABLE
    );
}

export function isAssetInWarningState(asset) {
    const status = normalizeFlowStatus(asset?.flow_status);
    return [
        ASSET_FLOW_STATUS.WRONG_LOCATION,
        ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT,
    ].includes(status);
}

export function isAssetInMovementState(asset) {
    const status = normalizeFlowStatus(asset?.flow_status);
    return [ASSET_FLOW_STATUS.MOVEMENT_REQUESTED, ASSET_FLOW_STATUS.IN_TRANSIT]
        .includes(status);
}

export function isAssetPendingPlacement(asset) {
    return normalizeFlowStatus(asset?.flow_status) === ASSET_FLOW_STATUS.PENDING_PLACEMENT;
}

export function getAssetLocationSummary(asset) {
    if (!asset) return "-";
    const status = normalizeFlowStatus(asset.flow_status);
    if (status === ASSET_FLOW_STATUS.IN_TRANSIT) {
        return `Current: ${asset.last_room_name || "-"} → Target: ${asset.expected_room_name || "-"}`;
    }
    if (status === ASSET_FLOW_STATUS.MOVEMENT_REQUESTED) {
        return `Assigned: ${asset.assigned_room_name || "-"} → Requested: ${asset.expected_room_name || "-"}`;
    }
    if (status === ASSET_FLOW_STATUS.PENDING_PLACEMENT) {
        return `Waiting for: ${asset.expected_room_name || asset.assigned_room_name || "-"}`;
    }
    return asset.last_room_name || asset.assigned_room_name || "-";
}
