/**
 * @file nodeSocketMessageHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import {
    normalizeNodes,
    removeNodeById,
    upsertNode,
} from "../../utils/nodeHelpers";

const NODE_UPSERT_EVENTS = new Set([
    "node_enrolled",
    "node_assigned",
    "node_unassigned",
    "node_heartbeat",
    "node_offline",
    "disabled_node_reconnected",
    "node_status_unknown",
]);

const NODE_SUCCESS_MESSAGES = {
    node_enrolled: "New node enrolled.",
    node_assigned: "Node assigned successfully.",
    node_unassigned: "Node unassigned successfully.",
};

export function handleNodeSocketMessage(message, handlers) {
    const messageType = message?.type;

    if (messageType === "snapshot") {
        handleSnapshot(message, handlers.setNodes);
        return;
    }

    if (NODE_UPSERT_EVENTS.has(messageType)) {
        handleNodeUpsert(message, handlers);
        return;
    }

    if (messageType === "node_deleted") {
        handleNodeDeleted(message, handlers);
        return;
    }

    if (messageType === "node_heartbeat_ignored") {
        return;
    }

    if (messageType === "node_identify_requested") {
        handleIdentifyRequested(message, handlers.setSuccessMessage);
        return;
    }

    if (messageType === "node_identify_ack") {
        handleIdentifyAck(message, handlers.setSuccessMessage);
        return;
    }

    if (messageType === "error" || messageType === "node_error") {
        handlers.setError(message.message || "Node WebSocket error received.");
    }
}

function handleSnapshot(message, setNodes) {
    const snapshotNodes = message?.nodes || message?.payload?.nodes || [];

    if (Array.isArray(snapshotNodes)) {
        setNodes(normalizeNodes(snapshotNodes));
    }
}

function handleNodeUpsert(message, { setNodes, setSuccessMessage }) {
    const node = message?.node || message?.payload?.node || null;

    if (node) {
        setNodes((currentNodes) => upsertNode(currentNodes, node));
    }

    if (NODE_SUCCESS_MESSAGES[message.type]) {
        setSuccessMessage(NODE_SUCCESS_MESSAGES[message.type]);
    }
}

function handleNodeDeleted(message, { setNodes, setSuccessMessage }) {
    const deletedDeviceId =
        message?.device_id ||
        message?.payload?.device_id ||
        message?.node?.device_id ||
        message?.payload?.node?.device_id ||
        "";

    setNodes((currentNodes) => removeNodeById(currentNodes, deletedDeviceId));
    setSuccessMessage("Node deleted successfully.");
}

function handleIdentifyRequested(message, setSuccessMessage) {
    const deviceId = message?.device_id || message?.node?.device_id || "";

    if (deviceId) {
        setSuccessMessage(`Blink command sent to ${deviceId}.`);
    }
}

function handleIdentifyAck(message, setSuccessMessage) {
    const deviceId = message?.device_id || "";
    const status = message?.payload?.status || "received";

    if (deviceId) {
        setSuccessMessage(`Node ${deviceId} blink command ${status}.`);
    }
}
