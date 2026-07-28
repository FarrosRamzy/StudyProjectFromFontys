/**
 * @file dashboardSummary.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { ASSET_FLOW_STATUS } from "../../constants/assetFlowStatus";
import { NODE_STATUS } from "../../constants/nodeStatus";

export function buildDashboardSummary({ assets, nodes, movementRequests, alerts }) {
    const warningAssets = assets.filter((asset) => [
        ASSET_FLOW_STATUS.WRONG_LOCATION,
        ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT,
    ].includes(asset.flow_status));
    const offlineNodes = getOfflineNodes(nodes);
    const nodeIssueAlerts = offlineNodes.map(makeNodeIssueAlert);
    const realtimeAlerts = alerts.filter((alert) => alert.type !== "node_offline");

    return {
        activeAssets: assets.filter((asset) => asset.status === "active"),
        availableAssets: assets.filter((asset) => asset.flow_status === ASSET_FLOW_STATUS.AVAILABLE),
        pendingPlacementAssets: assets.filter((asset) => asset.flow_status === ASSET_FLOW_STATUS.PENDING_PLACEMENT),
        waitingApprovalAssets: assets.filter((asset) => asset.flow_status === ASSET_FLOW_STATUS.MOVEMENT_REQUESTED),
        inTransitAssets: assets.filter((asset) => asset.flow_status === ASSET_FLOW_STATUS.IN_TRANSIT),
        pendingMovementRequests: movementRequests.filter((request) => String(request.status || "").toLowerCase() === "pending"),
        onlineNodes: getOnlineNodes(nodes),
        offlineNodes,
        warningAssets,
        nodeIssueAlerts,
        realtimeAlerts,
        recentWarnings: sortRecentWarnings(warningAssets),
    };
}

function getOnlineNodes(nodes) {
    return nodes.filter((node) => [
        NODE_STATUS.ONLINE, NODE_STATUS.ACTIVE, NODE_STATUS.CONNECTED,
    ].includes(String(node.status || "").toUpperCase()));
}

function getOfflineNodes(nodes) {
    return nodes.filter((node) => [
        NODE_STATUS.OFFLINE, NODE_STATUS.DISABLED,
    ].includes(String(node.status || "").toUpperCase()));
}

function makeNodeIssueAlert(node) {
    return {
        id: `node-${node.device_id}-${node.status}`,
        type: "node",
        severity: "warning",
        title: node.alias || node.device_id || "Node issue",
        message: `Node is ${node.status || "unknown"}.`,
        createdAt: node.last_ping_at || node.updated_at || node.created_at,
        node,
    };
}

function sortRecentWarnings(warningAssets) {
    return [...warningAssets]
        .sort((a, b) => new Date(b.last_seen_at || 0) - new Date(a.last_seen_at || 0))
        .slice(0, 5);
}
