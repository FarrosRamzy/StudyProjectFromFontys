/**
 * @file monitorSocketUtils.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

export function getPayload(message) {
    return message?.data || message?.payload || message || {};
}

export function getMessageAsset(message) {
    const payload = getPayload(message);
    return message?.asset || payload?.asset || null;
}

export function getMessageAssets(message) {
    const payload = getPayload(message);
    return message?.assets || payload?.assets || [];
}

export function getMessageNode(message) {
    const payload = getPayload(message);
    return message?.node || payload?.node || null;
}

export function getMessageNodes(message) {
    const payload = getPayload(message);
    return message?.nodes || payload?.nodes || [];
}

export function getMessageTagId(message) {
    const payload = getPayload(message);
    return String(message?.tag_id || payload?.tag_id || "").trim();
}

export function getMessageDeviceId(message) {
    const payload = getPayload(message);
    return String(message?.device_id || payload?.device_id || "").trim();
}

export function upsertAssetByTagId(currentAssets, updatedAsset) {
    if (!updatedAsset?.tag_id) {
        return currentAssets;
    }

    const exists = currentAssets.some(
        (asset) => asset.tag_id === updatedAsset.tag_id
    );

    if (!exists) {
        return [updatedAsset, ...currentAssets];
    }

    return currentAssets.map((asset) =>
        asset.tag_id === updatedAsset.tag_id ? updatedAsset : asset
    );
}

export function upsertNodeByDeviceId(currentNodes, updatedNode) {
    if (!updatedNode?.device_id) {
        return currentNodes;
    }

    const exists = currentNodes.some(
        (node) => node.device_id === updatedNode.device_id
    );

    if (!exists) {
        return [updatedNode, ...currentNodes];
    }

    return currentNodes.map((node) =>
        node.device_id === updatedNode.device_id ? updatedNode : node
    );
}

export function createActivityItem(type, message) {
    return {
        id: crypto.randomUUID(),
        type,
        message,
        createdAt: new Date().toISOString(),
    };
}

export function createAlertItem(type, title, description, raw = {}) {
    return {
        id: crypto.randomUUID(),
        type,
        title,
        description,
        createdAt: new Date().toISOString(),
        raw,
        read: false,
    };
}