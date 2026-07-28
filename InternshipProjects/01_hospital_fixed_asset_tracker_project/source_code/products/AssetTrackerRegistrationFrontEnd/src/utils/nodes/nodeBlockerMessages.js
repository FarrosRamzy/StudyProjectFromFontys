/**
 * @file nodeBlockerMessages.js
 * @author Farros Ramzy (you@domain.com)
 * @description Formats backend node reassignment/unassign blocker responses.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


export function isNodeOperationBlocked(result) {
    return (
        result?.message === "node_reassignment_blocked" ||
        result?.message === "node_unassign_blocked"
    );
}

export function formatNodeBlockerMessage(result) {
    const blockers = result?.blockers || {};

    const assignedAssets = blockers.assigned_assets_count || 0;
    const expectedAssets = blockers.expected_assets_count || 0;
    const currentLocationAssets = blockers.current_location_assets_count || 0;
    const activeMovementRequests = blockers.active_movement_requests_count || 0;

    if (result?.message === "node_reassignment_blocked") {
        return [
            "Cannot reassign this node.",
            "",
            "This node is still referenced by active assets or active movement requests.",
            "",
            `Current role: ${formatRole(result.old_role)}`,
            `New role: ${formatRole(result.new_role)}`,
            `Current room: ${result.old_room_name || "-"}`,
            `New room: ${result.new_room_name || "-"}`,
            "",
            `Assigned assets: ${assignedAssets}`,
            `Expected destination assets: ${expectedAssets}`,
            `Currently detected assets: ${currentLocationAssets}`,
            `Active movement requests: ${activeMovementRequests}`,
            "",
            "Move, resolve, or deregister the related assets first.",
        ].join("\n");
    }

    if (result?.message === "node_unassign_blocked") {
        return [
            "Cannot unassign this node.",
            "",
            "This node is still referenced by active assets or active movement requests.",
            "",
            `Assigned assets: ${assignedAssets}`,
            `Expected destination assets: ${expectedAssets}`,
            `Currently detected assets: ${currentLocationAssets}`,
            `Active movement requests: ${activeMovementRequests}`,
            "",
            "Move, resolve, or deregister the related assets first.",
        ].join("\n");
    }

    return result?.reason || result?.message || "Node operation failed.";
}

function formatRole(role) {
    const normalized = String(role || "").trim().toUpperCase();

    if (normalized === "REGISTRATION") {
        return "Registration Desk";
    }

    if (normalized === "CHECKPOINT") {
        return "Checkpoint Node";
    }

    return normalized || "-";
}