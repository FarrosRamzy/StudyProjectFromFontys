/**
 * @file nodeState.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-11

 * @Copyright (c) 2026
 */


import { getNodeIdentity } from "./nodeAccessors";
import { normalizeNode } from "./nodeNormalizers";

export function upsertNode(currentNodes, updatedNode) {
    const normalizedNode = normalizeNode(updatedNode);
    const updatedNodeId = getNodeIdentity(normalizedNode);

    if (!updatedNodeId) {
        return currentNodes;
    }

    const exists = currentNodes.some((node) => {
        return getNodeIdentity(node) === updatedNodeId;
    });

    if (!exists) {
        return [normalizedNode, ...currentNodes];
    }

    return currentNodes.map((node) => {
        return getNodeIdentity(node) === updatedNodeId ? normalizedNode : node;
    });
}

export function removeNodeById(currentNodes, deviceId) {
    const cleanDeviceId = String(deviceId || "").trim();

    if (!cleanDeviceId) {
        return currentNodes;
    }

    return currentNodes.filter((node) => {
        return getNodeIdentity(node) !== cleanDeviceId;
    });
}