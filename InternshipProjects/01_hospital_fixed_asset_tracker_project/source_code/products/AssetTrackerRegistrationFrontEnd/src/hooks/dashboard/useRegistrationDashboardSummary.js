/**
 * @file useRegistrationDashboardSummary.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export function useRegistrationDashboardSummary({ assets, nodes, movementRequests }) {
    const activeAssets = assets.filter((asset) => {
        return String(asset.status || "").toLowerCase() === "active";
    });

    const pendingPlacementAssets = assets.filter((asset) => {
        return String(asset.flow_status || "").toLowerCase() === "pending_placement";
    });

    const warningAssets = assets.filter((asset) => {
        const flowStatus = String(asset.flow_status || "").toLowerCase();
        return flowStatus === "wrong_location" || flowStatus === "unauthorized_movement";
    });

    const onlineNodes = nodes.filter((node) => {
        const status = String(node.status || "").trim().toUpperCase();
        return status === "ONLINE" || status === "ACTIVE" || status === "CONNECTED";
    });

    const offlineNodes = nodes.filter((node) => {
        return String(node.status || "").trim().toUpperCase() === "OFFLINE";
    });

    const disabledNodes = nodes.filter((node) => {
        return String(node.status || "").trim().toUpperCase() === "DISABLED";
    });

    const pendingRequests = movementRequests.filter((request) => {
        return String(request.status || "").toLowerCase() === "pending";
    });

    return {
        activeAssets,
        pendingPlacementAssets,
        warningAssets,
        onlineNodes,
        offlineNodes,
        disabledNodes,
        pendingRequests,
    };
}
