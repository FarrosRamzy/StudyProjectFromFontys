/**
 * @file alertBuilders.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { isAssetInWarningState, isAssetPendingPlacement } from "../flowStatus";

export function buildCombinedAlerts({ assets = [], nodes = [], alerts = [] }) {
    return dedupeAlerts([
        ...buildAssetAlerts(assets),
        ...buildNodeAlerts(nodes),
        ...alerts.filter((alert) => alert.type !== "node_offline"),
    ]);
}

function buildAssetAlerts(assets) {
    return assets
        .filter((asset) => isAssetInWarningState(asset) || isAssetPendingPlacement(asset))
        .map((asset) => ({
            id: `asset-${asset.tag_id}-${asset.flow_status}`,
            type: "asset",
            severity: asset.flow_status === "unauthorized_movement" ? "critical" : "warning",
            title: asset.item_name || "Unnamed asset",
            message: asset.movement_note || `Asset status: ${asset.flow_status}`,
            createdAt: asset.last_seen_at,
            asset,
        }));
}

function buildNodeAlerts(nodes) {
    return nodes
        .filter((node) => ["OFFLINE", "DISABLED"].includes(String(node.status || "").toUpperCase()))
        .map((node) => ({
            id: `node-${node.device_id}-${node.status}`,
            type: "node",
            severity: "warning",
            title: node.alias || node.device_id || "Node issue",
            message: `Node is ${node.status || "unknown"}.`,
            createdAt: node.last_ping_at,
            node,
        }));
}

function dedupeAlerts(alerts) {
    const seen = new Set();
    return alerts.filter((alert) => {
        const key = getAlertDedupeKey(alert);
        if (seen.has(key)) return false;
        seen.add(key);
        return true;
    });
}

function getAlertDedupeKey(alert) {
    if (alert.asset?.tag_id) {
        return ["asset", alert.asset.tag_id, alert.asset.flow_status, alert.asset.last_room_name].join("|");
    }
    if (alert.node?.device_id) {
        return ["node", alert.node.device_id, alert.node.status].join("|");
    }
    if (alert.payload?.tag_id) {
        return ["unknown-tag", alert.payload.tag_id, alert.payload.node_id || alert.payload.device_id || ""].join("|");
    }
    return alert.id || `${alert.type}-${alert.message}-${alert.createdAt}`;
}
