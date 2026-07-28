/**
 * @file assetFlowStatusMeta.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { ASSET_FLOW_STATUS } from "./assetStatusBase";

export const ASSET_FLOW_STATUS_META = {
    [ASSET_FLOW_STATUS.PENDING_PLACEMENT]: {
        label: "Pending Placement", shortLabel: "Placement", tone: "danger",
        rowClass: "monitor-row-danger", severity: "action_required",
        description: "Asset has been registered but has not reached its assigned checkpoint.",
    },
    [ASSET_FLOW_STATUS.AVAILABLE]: {
        label: "In Place", shortLabel: "In Place", tone: "success",
        rowClass: "", severity: "normal",
        description: "Asset is detected in its assigned location.",
    },
    [ASSET_FLOW_STATUS.MOVEMENT_REQUESTED]: {
        label: "Waiting Approval", shortLabel: "Requested", tone: "warning",
        rowClass: "monitor-row-warning", severity: "waiting",
        description: "A movement request is waiting for registration desk approval.",
    },
    [ASSET_FLOW_STATUS.IN_TRANSIT]: {
        label: "Approved / Moving", shortLabel: "Moving", tone: "danger",
        rowClass: "monitor-row-danger", severity: "active_movement",
        description: "Movement was approved and the asset is going to the destination.",
    },
    [ASSET_FLOW_STATUS.WRONG_LOCATION]: {
        label: "Wrong Location", shortLabel: "Wrong", tone: "danger",
        rowClass: "monitor-row-danger", severity: "warning",
        description: "Asset was detected in a different location from its expected destination.",
    },
    [ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT]: {
        label: "Unauthorized Movement", shortLabel: "Unauthorized", tone: "danger",
        rowClass: "monitor-row-danger", severity: "critical",
        description: "Asset moved without an approved movement request.",
    },
    [ASSET_FLOW_STATUS.DEREGISTERED]: {
        label: "Deregistered", shortLabel: "Inactive", tone: "neutral",
        rowClass: "monitor-row-muted", severity: "inactive",
        description: "Asset is no longer actively tracked.",
    },
};
