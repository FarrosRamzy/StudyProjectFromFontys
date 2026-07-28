/**
 * @file assetStatusOptions.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { ASSET_FLOW_STATUS, ASSET_STATUS, MOVEMENT_REQUEST_STATUS } from "./assetStatusBase";

export const ASSET_FLOW_STATUS_OPTIONS = [
    { value: "all", label: "All Flow Statuses" },
    { value: ASSET_FLOW_STATUS.PENDING_PLACEMENT, label: "Pending Placement" },
    { value: ASSET_FLOW_STATUS.AVAILABLE, label: "In Place" },
    { value: ASSET_FLOW_STATUS.MOVEMENT_REQUESTED, label: "Waiting Approval" },
    { value: ASSET_FLOW_STATUS.IN_TRANSIT, label: "Approved / Moving" },
    { value: ASSET_FLOW_STATUS.WRONG_LOCATION, label: "Wrong Location" },
    { value: ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT, label: "Unauthorized Movement" },
    { value: ASSET_FLOW_STATUS.DEREGISTERED, label: "Deregistered" },
];

export const ASSET_STATUS_OPTIONS = [
    { value: "all", label: "All Asset Statuses" },
    { value: ASSET_STATUS.ACTIVE, label: "Active" },
    { value: ASSET_STATUS.DEREGISTERED, label: "Deregistered" },
];

export const MOVEMENT_REQUEST_STATUS_OPTIONS = [
    { value: "all", label: "All Movement Requests" },
    { value: MOVEMENT_REQUEST_STATUS.PENDING, label: "Pending" },
    { value: MOVEMENT_REQUEST_STATUS.APPROVED, label: "Approved" },
    { value: MOVEMENT_REQUEST_STATUS.REJECTED, label: "Rejected" },
    { value: MOVEMENT_REQUEST_STATUS.COMPLETED, label: "Completed" },
    { value: MOVEMENT_REQUEST_STATUS.CANCELLED, label: "Cancelled" },
];
