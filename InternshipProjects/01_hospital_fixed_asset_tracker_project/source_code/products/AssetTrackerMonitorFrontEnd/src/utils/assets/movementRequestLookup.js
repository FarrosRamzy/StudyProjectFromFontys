/**
 * @file movementRequestLookup.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function getPendingMovementRequestForAsset(asset, movementRequests = []) {
    if (!asset?.tag_id) return null;
    const activeRequestId = asset.active_movement_request_id || asset.activeMovementRequestId;
    return movementRequests.find((request) => {
        const status = String(request.status || "").toLowerCase();
        const requestId = request.id || request.request_id || request.movement_request_id;
        if (activeRequestId) {
            return Number(requestId) === Number(activeRequestId) && status === "pending";
        }
        return request.tag_id === asset.tag_id && status === "pending";
    }) || null;
}

export function getMovementRequestId(request) {
    return request?.id || request?.request_id || request?.movement_request_id;
}
