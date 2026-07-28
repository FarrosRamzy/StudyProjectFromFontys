/**
 * @file assetSocketEventSets.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


export const ASSET_UPSERT_EVENTS = new Set([
    "asset_registered",
    "asset_updated",
    "asset_deregistered",
    "asset_movement_requested",
    "asset_movement_approved",
    "asset_movement_rejected",
    "asset_movement_cancelled",
    "asset_movement_completed",
    "asset_location_updated",
    "asset_flow_status_updated",
    "asset_detected",
]);

export const MOVEMENT_REQUEST_CHANGED_EVENTS = new Set([
    "asset_movement_requested",
    "asset_movement_approved",
    "asset_movement_rejected",
    "asset_movement_cancelled",
    "asset_movement_completed",
    "movement_request_created",
    "movement_request_updated",
]);
