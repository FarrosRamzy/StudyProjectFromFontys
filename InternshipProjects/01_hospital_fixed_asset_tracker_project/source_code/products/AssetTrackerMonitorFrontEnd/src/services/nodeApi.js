/**
 * @file nodeApi.js
 * @author Farros Ramzy (you@domain.com)
 * @description Node API helpers.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { apiRequest } from "./apiClient";

export async function getNodes() {
    const data = await apiRequest("/nodes");

    if (Array.isArray(data)) {
        return data;
    }

    return data?.nodes || data?.items || [];
}

export async function getNodeByDeviceId(deviceId) {
    return apiRequest(`/nodes/${encodeURIComponent(deviceId)}`);
}

export function normalizeNode(node) {
    if (!node) {
        return null;
    }

    return {
        ...node,
        device_id: node.device_id || node.node_id || node.id || "",
        alias: node.alias || node.name || "",
        role: node.role || "",
        status: node.status || "",
        room_name: node.room_name || "",
        hospital_id: node.hospital_id || "",
        hospital_name: node.hospital_name || "",
        is_provisioned:
            node.is_provisioned === true ||
            node.is_provisioned === "true" ||
            node.is_provisioned === 1,
    };
}

export function upsertNodeInList(nodes, incomingNode) {
    const normalizedNode = normalizeNode(incomingNode);

    if (!normalizedNode?.device_id) {
        return nodes;
    }

    const exists = nodes.some((node) => node.device_id === normalizedNode.device_id);

    if (!exists) {
        return [normalizedNode, ...nodes];
    }

    return nodes.map((node) =>
        node.device_id === normalizedNode.device_id
            ? {
                ...node,
                ...normalizedNode,
            }
            : node
    );
}
