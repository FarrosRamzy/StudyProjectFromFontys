/**
 * @file monitorDataLoaders.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { getAssets, getMovementRequests, normalizeAsset } from "../../../services/assetApi";
import { getNodes, normalizeNode } from "../../../services/nodeApi";

export async function loadMonitorSnapshot() {
    const [assets, nodes, requests] = await Promise.all([
        getAssets(), getNodes(), getMovementRequests(),
    ]);
    return {
        assets: assets.map(normalizeAsset).filter(Boolean),
        nodes: nodes.map(normalizeNode).filter(Boolean),
        movementRequests: Array.isArray(requests) ? requests : [],
    };
}

export async function loadNodesSnapshot() {
    return (await getNodes()).map(normalizeNode).filter(Boolean);
}

export async function loadActiveAssetsSnapshot() {
    return (await getAssets())
        .map(normalizeAsset)
        .filter(Boolean)
        .filter((asset) => String(asset.status || "").toLowerCase() !== "deregistered");
}
