/**
 * @file socketMovementRequests.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function getMovementRequestStatusFromEvent(type) {
    const statusByEvent = {
        asset_movement_requested: "pending",
        asset_movement_approved: "approved",
        asset_movement_rejected: "rejected",
        asset_movement_cancelled: "cancelled",
        asset_movement_completed: "completed",
        movement_request_completed: "completed",
    };
    return statusByEvent[type] || "";
}

export function getRequestPayload(type, payload) {
    return payload.movement_request || payload.request || {
        id: payload.movement_request_id,
        movement_request_id: payload.movement_request_id,
        tag_id: payload.asset?.tag_id || payload.tag_id || "",
        item_name: payload.asset?.item_name || payload.item_name || "",
        status: getMovementRequestStatusFromEvent(type),
    };
}

export function upsertMovementRequestInList(requests, incomingRequest) {
    const incomingId = getRequestId(incomingRequest);
    if (!incomingId) return requests;

    const normalizedIncoming = {
        ...incomingRequest,
        id: incomingRequest.id || incomingId,
        movement_request_id: incomingRequest.movement_request_id || incomingId,
    };

    if (!requests.some((request) => Number(getRequestId(request)) === Number(incomingId))) {
        return [normalizedIncoming, ...requests];
    }

    return requests.map((request) => Number(getRequestId(request)) === Number(incomingId)
        ? { ...request, ...normalizedIncoming, status: normalizedIncoming.status || request.status }
        : request);
}

function getRequestId(request) {
    return request?.id || request?.request_id || request?.movement_request_id;
}
