/**
 * @file monitorSocketHandlers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import {
    createActivityItem,
    createAlertItem,
    getMessageAsset,
    getMessageAssets,
    getMessageDeviceId,
    getMessageNode,
    getMessageNodes,
    getMessageTagId,
    upsertAssetByTagId,
    upsertNodeByDeviceId,
} from "./monitorSocketUtils";

const ASSET_UPSERT_EVENTS = new Set([
    "asset_registered",
    "asset_updated",
    "asset_deregistered",
]);

const NODE_UPSERT_EVENTS = new Set([
    "node_enrolled",
    "node_assigned",
    "node_unassigned",
    "node_heartbeat",
    "node_offline",
    "disabled_node_reconnected",
    "node_status_unknown",
]);

export function handleMonitorSocketMessage(message, handlers) {
    const {
        setAssets,
        setNodes,
        setAlerts,
        setActivity,
    } = handlers;

    switch (message.type) {
        case "snapshot":
            handleSnapshot(message, { setAssets, setNodes });
            return;

        case "asset_deleted":
            handleAssetDeleted(message, setAssets, setActivity);
            return;

        case "node_deleted":
            handleNodeDeleted(message, setNodes, setActivity);
            return;

        case "unknown_tag":
            handleUnknownTag(message, { setAlerts, setActivity });
            return;

        case "inactive_asset_detected":
            handleInactiveAssetDetected(message, { setAlerts, setActivity });
            return;

        case "unknown_node_detection":
            handleUnknownNodeDetection(message, { setAlerts, setActivity });
            return;

        default:
            if (ASSET_UPSERT_EVENTS.has(message.type)) {
                handleAssetUpsert(message, setAssets, setActivity);
                return;
            }

            if (NODE_UPSERT_EVENTS.has(message.type)) {
                handleNodeUpsert(message, setNodes, setActivity);
                return;
            }
    }
}

function handleSnapshot(message, handlers) {
    const { setAssets, setNodes } = handlers;

    const assets = getMessageAssets(message);
    const nodes = getMessageNodes(message);

    if (Array.isArray(assets)) {
        setAssets(assets);
    }

    if (Array.isArray(nodes)) {
        setNodes(nodes);
    }
}

function handleAssetUpsert(message, setAssets, setActivity) {
    const asset = getMessageAsset(message);

    if (!asset) {
        return;
    }

    setAssets((currentAssets) => upsertAssetByTagId(currentAssets, asset));

    const assetName = asset.item_name || asset.tag_id || "Asset";
    const roomName = asset.last_room_name || "unknown location";

    setActivity((current) => [
        createActivityItem(
            message.type,
            `${assetName} updated at ${roomName}`
        ),
        ...current,
    ].slice(0, 100));
}

function handleNodeUpsert(message, setNodes, setActivity) {
    const node = getMessageNode(message);

    if (!node) {
        return;
    }

    setNodes((currentNodes) => upsertNodeByDeviceId(currentNodes, node));

    const nodeName = node.alias || node.device_id || "Node";
    const status = node.status || "updated";

    setActivity((current) => [
        createActivityItem(
            message.type,
            `${nodeName} status changed to ${status}`
        ),
        ...current,
    ].slice(0, 100));
}

function handleAssetDeleted(message, setAssets, setActivity) {
    const tagId = getMessageTagId(message);

    if (!tagId) {
        return;
    }

    setAssets((currentAssets) =>
        currentAssets.filter((asset) => asset.tag_id !== tagId)
    );

    setActivity((current) => [
        createActivityItem("asset_deleted", `Asset ${tagId} was deleted.`),
        ...current,
    ].slice(0, 100));
}

function handleNodeDeleted(message, setNodes, setActivity) {
    const deviceId = getMessageDeviceId(message);

    if (!deviceId) {
        return;
    }

    setNodes((currentNodes) =>
        currentNodes.filter((node) => node.device_id !== deviceId)
    );

    setActivity((current) => [
        createActivityItem("node_deleted", `Node ${deviceId} was deleted.`),
        ...current,
    ].slice(0, 100));
}

function handleUnknownTag(message, handlers) {
    const { setAlerts, setActivity } = handlers;

    const tagId = getMessageTagId(message);
    const deviceId = getMessageDeviceId(message);
    const roomName = message?.room_name || message?.data?.room_name || "unknown room";

    const description = `Unknown tag ${tagId || "unknown"} detected at ${roomName} by ${deviceId || "unknown node"}.`;

    const alert = createAlertItem(
        "unknown_tag",
        "Unknown RFID Tag Detected",
        description,
        message
    );

    setAlerts((current) => [alert, ...current].slice(0, 100));
    setActivity((current) => [
        createActivityItem("unknown_tag", description),
        ...current,
    ].slice(0, 100));
}

function handleInactiveAssetDetected(message, handlers) {
    const { setAlerts, setActivity } = handlers;

    const asset = getMessageAsset(message);
    const tagId = getMessageTagId(message);
    const name = asset?.item_name || tagId || "Inactive asset";

    const description = `${name} was detected but is not active.`;

    const alert = createAlertItem(
        "inactive_asset_detected",
        "Inactive Asset Detected",
        description,
        message
    );

    setAlerts((current) => [alert, ...current].slice(0, 100));
    setActivity((current) => [
        createActivityItem("inactive_asset_detected", description),
        ...current,
    ].slice(0, 100));
}

function handleUnknownNodeDetection(message, handlers) {
    const { setAlerts, setActivity } = handlers;

    const deviceId = getMessageDeviceId(message);
    const description = `Detection received from unknown node ${deviceId || "unknown device"}.`;

    const alert = createAlertItem(
        "unknown_node_detection",
        "Unknown Node Detection",
        description,
        message
    );

    setAlerts((current) => [alert, ...current].slice(0, 100));
    setActivity((current) => [
        createActivityItem("unknown_node_detection", description),
        ...current,
    ].slice(0, 100));
}