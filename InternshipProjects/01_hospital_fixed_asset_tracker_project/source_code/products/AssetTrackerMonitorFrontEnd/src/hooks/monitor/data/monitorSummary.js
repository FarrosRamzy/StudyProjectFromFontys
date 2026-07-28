/**
 * @file monitorSummary.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function buildMonitorSummary({ assets, nodes, movementRequests, alerts }) {
    const activeAssets = assets.filter((asset) => asset.status === "active");
    const inPlaceAssets = assets.filter((asset) => asset.flow_status === "available");
    const pendingPlacementAssets = assets.filter((asset) => asset.flow_status === "pending_placement");
    const waitingApprovalAssets = assets.filter((asset) => asset.flow_status === "movement_requested");
    const inTransitAssets = assets.filter((asset) => asset.flow_status === "in_transit");
    const warningAssets = assets.filter((asset) => [
        "wrong_location", "unauthorized_movement",
    ].includes(asset.flow_status));
    const onlineNodes = nodes.filter((node) => {
        const status = String(node.status || "").toUpperCase();
        return ["ONLINE", "ACTIVE", "CONNECTED"].includes(status);
    });
    const offlineNodes = nodes.filter((node) => {
        const status = String(node.status || "").toUpperCase();
        return ["OFFLINE", "DISABLED"].includes(status);
    });

    return {
        totalAssets: assets.length,
        activeAssets: activeAssets.length,
        inPlaceAssets: inPlaceAssets.length,
        pendingPlacementAssets: pendingPlacementAssets.length,
        waitingApprovalAssets: waitingApprovalAssets.length,
        inTransitAssets: inTransitAssets.length,
        warningAssets: warningAssets.length,
        totalNodes: nodes.length,
        onlineNodes: onlineNodes.length,
        offlineNodes: offlineNodes.length,
        movementRequests: movementRequests.length,
        alerts: alerts.length,
    };
}
