/**
 * @file assetStatusBase.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export const ASSET_STATUS = {
    ACTIVE: "active",
    DEREGISTERED: "deregistered",
};

export const ASSET_FLOW_STATUS = {
    PENDING_PLACEMENT: "pending_placement",
    AVAILABLE: "available",
    MOVEMENT_REQUESTED: "movement_requested",
    IN_TRANSIT: "in_transit",
    WRONG_LOCATION: "wrong_location",
    UNAUTHORIZED_MOVEMENT: "unauthorized_movement",
    DEREGISTERED: "deregistered",
};

export const MOVEMENT_REQUEST_STATUS = {
    PENDING: "pending",
    APPROVED: "approved",
    REJECTED: "rejected",
    COMPLETED: "completed",
    CANCELLED: "cancelled",
};
