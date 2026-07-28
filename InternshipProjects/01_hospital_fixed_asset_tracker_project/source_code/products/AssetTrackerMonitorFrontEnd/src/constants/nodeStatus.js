/**
 * @file nodeStatus.js
 * @author Farros Ramzy (you@domain.com)
 * @description Node role and status constants.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export const NODE_ROLE = {
    REGISTRATION: "REGISTRATION",
    REGISTRATION_DESK: "REGISTRATION_DESK",
    CHECKPOINT: "CHECKPOINT",
    CHECKPOINT_NODE: "CHECKPOINT_NODE",
};

export const NODE_STATUS = {
    ONLINE: "ONLINE",
    OFFLINE: "OFFLINE",
    DISABLED: "DISABLED",
    DISCOVERED: "DISCOVERED",
    UNKNOWN: "UNKNOWN",
    ACTIVE: "ACTIVE",
    CONNECTED: "CONNECTED",
};

export const NODE_ROLE_OPTIONS = [
    {
        value: "all",
        label: "All Roles",
    },
    {
        value: NODE_ROLE.REGISTRATION_DESK,
        label: "Registration Desk",
    },
    {
        value: NODE_ROLE.CHECKPOINT_NODE,
        label: "Checkpoint Node",
    },
];

export const NODE_STATUS_OPTIONS = [
    {
        value: "all",
        label: "All Node Statuses",
    },
    {
        value: NODE_STATUS.ONLINE,
        label: "Online",
    },
    {
        value: NODE_STATUS.OFFLINE,
        label: "Offline",
    },
    {
        value: NODE_STATUS.DISABLED,
        label: "Disabled",
    },
    {
        value: NODE_STATUS.UNKNOWN,
        label: "Unknown / Discovered",
    },
];

export const NODE_STATUS_META = {
    [NODE_STATUS.ONLINE]: {
        label: "Online",
        tone: "success",
        severity: "normal",
        description: "Node is online and recently sent a heartbeat.",
    },

    [NODE_STATUS.ACTIVE]: {
        label: "Active",
        tone: "success",
        severity: "normal",
        description: "Node is active.",
    },

    [NODE_STATUS.CONNECTED]: {
        label: "Connected",
        tone: "success",
        severity: "normal",
        description: "Node is connected.",
    },

    [NODE_STATUS.OFFLINE]: {
        label: "Offline",
        tone: "danger",
        severity: "warning",
        description: "Node has not sent a heartbeat recently.",
    },

    [NODE_STATUS.DISABLED]: {
        label: "Disabled",
        tone: "neutral",
        severity: "inactive",
        description: "Node has been disabled and should not be used.",
    },

    [NODE_STATUS.UNKNOWN]: {
        label: "Unknown",
        tone: "warning",
        severity: "unknown",
        description: "Node status is unknown.",
    },
};

export const NODE_ROLE_META = {
    [NODE_ROLE.REGISTRATION]: {
        label: "Registration",
        tone: "info",
        description: "Node used for asset registration and deregistration.",
    },

    [NODE_ROLE.REGISTRATION_DESK]: {
        label: "Registration Desk",
        tone: "info",
        description: "Node used at the registration desk.",
    },

    [NODE_ROLE.CHECKPOINT]: {
        label: "Checkpoint",
        tone: "success",
        description: "Node used to detect asset movement and location.",
    },

    [NODE_ROLE.CHECKPOINT_NODE]: {
        label: "Checkpoint Node",
        tone: "success",
        description: "Node used to detect asset movement and location.",
    },
};
