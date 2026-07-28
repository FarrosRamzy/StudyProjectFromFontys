/**
 * @file assetTableHelpers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export function getAssetRowClass(asset) {
    const flowStatus = String(asset.flow_status || "").toLowerCase();

    if ([
        "pending_placement",
        "in_transit",
        "wrong_location",
        "unauthorized_movement",
    ].includes(flowStatus)) {
        return "asset-row-danger";
    }

    if (flowStatus === "movement_requested") {
        return "asset-row-warning";
    }

    if (flowStatus === "available") {
        return "asset-row-success";
    }

    return "";
}

export function getAssetFlowText(asset) {
    const flowStatus = String(asset.flow_status || "").toLowerCase();
    const expectedRoom = asset.expected_room_name || "";

    if (flowStatus === "pending_placement") {
        return expectedRoom ? `Waiting for placement at ${expectedRoom}` : "Waiting for initial placement";
    }

    if (flowStatus === "movement_requested") {
        return expectedRoom ? `Movement requested to ${expectedRoom}` : "Movement requested";
    }

    if (flowStatus === "in_transit") {
        return expectedRoom ? `In transit to ${expectedRoom}` : "In transit";
    }

    if (flowStatus === "wrong_location") {
        return asset.movement_note ||
            `Assigned to ${asset.assigned_room_name || "-"}, detected at ${asset.last_room_name || "-"}`;
    }

    if (flowStatus === "unauthorized_movement") {
        return asset.movement_note ||
            `Unauthorized movement. Assigned to ${asset.assigned_room_name || "-"}, detected at ${asset.last_room_name || "-"}`;
    }

    if (flowStatus === "available") {
        return "Available";
    }

    return asset.movement_note || "-";
}

export function shouldShowAssetFlowNote(asset) {
    const flowStatus = String(asset.flow_status || "").toLowerCase();

    return [
        "pending_placement",
        "movement_requested",
        "in_transit",
        "wrong_location",
        "unauthorized_movement",
    ].includes(flowStatus);
}
