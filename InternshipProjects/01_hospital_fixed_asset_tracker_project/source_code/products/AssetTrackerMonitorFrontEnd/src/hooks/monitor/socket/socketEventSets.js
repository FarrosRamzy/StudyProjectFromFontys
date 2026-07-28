/**
 * @file socketEventSets.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export const ASSET_UPSERT_EVENTS = new Set([
    "asset_registered", "asset_updated", "asset_movement_requested",
    "asset_movement_approved", "asset_movement_rejected",
    "asset_movement_cancelled", "asset_movement_completed",
    "asset_location_updated", "asset_flow_status_updated", "asset_detected",
]);

export const ASSET_REMOVE_EVENTS = new Set(["asset_deregistered", "asset_deleted"]);

export const NODE_UPSERT_EVENTS = new Set([
    "node_registered", "node_enrolled", "node_assigned", "node_unassigned",
    "node_updated", "node_status_updated", "node_heartbeat", "node_offline",
    "node_status_unknown", "disabled_node_reconnected",
]);

export const MOVEMENT_REQUEST_UPSERT_EVENTS = new Set([
    "movement_request_created", "movement_request_updated",
    "asset_movement_requested", "asset_movement_approved",
    "asset_movement_rejected", "asset_movement_cancelled",
    "asset_movement_completed",
]);

export const ALERT_EVENTS = new Set([
    "unknown_tag", "unknown_tag_detected", "inactive_asset_detected",
    "unknown_node_detection", "asset_wrong_location", "asset_unauthorized_movement",
]);

export const SILENT_ACTIVITY_EVENTS = new Set([
    "node_heartbeat", "node_heartbeat_ignored",
]);
