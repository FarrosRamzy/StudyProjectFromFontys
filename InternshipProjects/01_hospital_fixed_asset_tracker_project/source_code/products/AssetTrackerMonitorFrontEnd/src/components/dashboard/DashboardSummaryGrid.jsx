/**
 * @file DashboardSummaryGrid.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { DashboardStatCard } from "./DashboardStatCard";

export function DashboardSummaryGrid({ assets, nodes, summary, onNavigate }) {
    const movementTotal = summary.waitingApprovalAssets.length + summary.inTransitAssets.length;
    const warningTotal = summary.warningAssets.length + summary.nodeIssueAlerts.length + summary.realtimeAlerts.length;

    return (
        <div className="monitor-summary-grid">
            <DashboardStatCard label="Registered Assets" value={assets.length} detail={`${summary.activeAssets.length} active assets`} tone="success" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)} />
            <DashboardStatCard label="In Place" value={summary.availableAssets.length} detail="Assets in assigned location" tone="success" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)} />
            <DashboardStatCard label="Movement" value={movementTotal} detail={`${summary.waitingApprovalAssets.length} waiting approval, ${summary.inTransitAssets.length} moving`} tone="warning" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)} />
            <DashboardStatCard label="Warnings" value={warningTotal} detail={`${summary.warningAssets.length} asset, ${summary.nodeIssueAlerts.length} node issue${summary.nodeIssueAlerts.length === 1 ? "" : "s"}`} tone="danger" onClick={() => onNavigate?.(APP_ROUTES.ALERTS)} />
            <DashboardStatCard label="Pending Placement" value={summary.pendingPlacementAssets.length} detail="Registered but not yet placed" tone="danger" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)} />
            <DashboardStatCard label="Pending Requests" value={summary.pendingMovementRequests.length} detail="Waiting for registration desk approval" tone="warning" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)} />
            <DashboardStatCard label="Online Nodes" value={summary.onlineNodes.length} detail={`${summary.offlineNodes.length} offline or disabled`} tone="success" onClick={() => onNavigate?.(APP_ROUTES.NODES)} />
            <DashboardStatCard label="Total Nodes" value={nodes.length} detail="Registration and checkpoint nodes" tone="info" onClick={() => onNavigate?.(APP_ROUTES.NODES)} />
        </div>
    );
}
