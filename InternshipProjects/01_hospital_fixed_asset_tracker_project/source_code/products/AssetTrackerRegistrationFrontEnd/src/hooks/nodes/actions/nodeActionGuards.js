/**
 * @file nodeActionGuards.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export function cleanDeviceId(deviceId) {
    return String(deviceId || "").trim();
}

export function confirmUnassign(cleanDeviceId) {
    return window.confirm(
        `Unassign node "${cleanDeviceId}"?\n\n` +
        "The backend will block this action if active assets or movement requests still reference this node."
    );
}

export function confirmDelete(cleanDeviceId) {
    return window.confirm(
        `Delete node "${cleanDeviceId}"? This action should only be used for removed or invalid devices.`
    );
}

export function getIdentifyError(message) {
    if (message === "node_offline") {
        return "This node is offline. Blink is unavailable until the node reconnects.";
    }

    if (message === "node_disabled") {
        return "This node is disabled. Blink is unavailable.";
    }

    if (message === "node_not_provisioned") {
        return "This node has not been assigned yet. Blink is unavailable.";
    }

    if (message === "node_not_found") {
        return "The selected node could not be found.";
    }

    return "";
}
