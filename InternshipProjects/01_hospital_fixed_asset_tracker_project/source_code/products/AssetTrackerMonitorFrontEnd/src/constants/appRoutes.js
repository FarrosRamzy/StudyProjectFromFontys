/**
 * @file appRoute.js
 * @author Farros Ramzy (you@domain.com)
 * @description Internal page route constants for the monitor app.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


export const APP_ROUTES = {
    DASHBOARD: "dashboard",
    ASSETS: "assets",
    NODES: "nodes",
    ALERTS: "alerts",
    ACTIVITY: "activity",
};

export const APP_NAV_ITEMS = [
    {
        key: APP_ROUTES.DASHBOARD,
        label: "Dashboard",
        description: "System overview",
    },
    {
        key: APP_ROUTES.ASSETS,
        label: "Assets",
        description: "Asset location monitor",
    },
    {
        key: APP_ROUTES.NODES,
        label: "Nodes",
        description: "Checkpoint and registration nodes",
    },
    {
        key: APP_ROUTES.ALERTS,
        label: "Alerts",
        description: "Warnings and abnormal states",
    },
    {
        key: APP_ROUTES.ACTIVITY,
        label: "Activities",
        description: "Realtime event history",
    },
];
