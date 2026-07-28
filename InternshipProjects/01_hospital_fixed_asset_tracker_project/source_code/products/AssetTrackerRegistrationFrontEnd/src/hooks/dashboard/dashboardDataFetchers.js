/**
 * @file dashboardDataFetchers.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { getAssets, getMovementRequests } from "../../services/assetApi";
import { getNodes } from "../../services/nodeApi";

function getList(data, possibleKeys = []) {
    if (Array.isArray(data)) {
        return data;
    }

    for (const key of possibleKeys) {
        if (Array.isArray(data?.[key])) {
            return data[key];
        }
    }

    return [];
}

export async function fetchDashboardData({
    loadAssets,
    loadNodes,
    loadMovementRequests,
}) {
    const [assetData, nodeData, movementData] = await Promise.all([
        loadAssets ? getAssets() : Promise.resolve([]),
        loadNodes ? getNodes() : Promise.resolve([]),
        loadMovementRequests ? getMovementRequests("pending") : Promise.resolve([]),
    ]);

    return {
        assets: getList(assetData, ["assets"]),
        nodes: getList(nodeData, ["nodes"]),
        movementRequests: getList(movementData, ["movement_requests", "requests"]),
    };
}
