/**
 * @file checkpointSearch.js
 * @author Farros Ramzy (you@domain.com)
 * @description Helper utilities for searching and selecting checkpoint nodes.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { normalizeText } from "./textFormat";

export function getCheckpointDisplayName(node) {
    if (!node) {
        return "";
    }

    const roomName = node.room_name || "";
    const alias = node.alias || "";
    const deviceId = node.device_id || node.node_id || "";

    return [roomName, alias, deviceId].filter(Boolean).join(" — ");
}

export function getCheckpointSearchValue(node) {
    return getCheckpointDisplayName(node);
}

export function isCheckpointNode(node) {
    const role = normalizeText(node?.role).toUpperCase();
    const status = normalizeText(node?.status).toUpperCase();

    const isCheckpoint =
        role === "CHECKPOINT" ||
        role === "CHECKPOINT_NODE" ||
        role === "CHECKPOINT NODE";

    const isProvisioned =
        node?.is_provisioned === true ||
        node?.is_provisioned === "true" ||
        node?.is_provisioned === 1;

    const isNotDisabled = status !== "DISABLED";

    return isCheckpoint && isProvisioned && isNotDisabled;
}

export function getCheckpointNodes(nodes = []) {
    return nodes.filter(isCheckpointNode);
}

export function findCheckpointNodeByInput(inputValue, checkpointNodes = []) {
    const keyword = normalizeText(inputValue).toLowerCase();

    if (!keyword) {
        return null;
    }

    return (
        checkpointNodes.find((node) => {
            const deviceId = normalizeText(node.device_id || node.node_id).toLowerCase();
            const roomName = normalizeText(node.room_name).toLowerCase();
            const alias = normalizeText(node.alias).toLowerCase();
            const displayValue = normalizeText(getCheckpointDisplayName(node)).toLowerCase();

            return (
                keyword === deviceId ||
                keyword === roomName ||
                keyword === alias ||
                keyword === displayValue
            );
        }) || null
    );
}

export function filterCheckpointNodesByKeyword(checkpointNodes = [], keyword = "") {
    const search = normalizeText(keyword).toLowerCase();

    if (!search) {
        return checkpointNodes;
    }

    return checkpointNodes.filter((node) => {
        const searchableText = [
            node.device_id,
            node.node_id,
            node.room_name,
            node.alias,
            node.hospital_name,
            node.status,
        ]
            .filter(Boolean)
            .join(" ")
            .toLowerCase();

        return searchableText.includes(search);
    });
}

export function getCheckpointPayloadFromNode(node) {
    if (!node) {
        return {
            destination_node_id: "",
            destination_room_name: "",
        };
    }

    return {
        destination_node_id: node.device_id || node.node_id || "",
        destination_room_name: node.room_name || "",
    };
}
