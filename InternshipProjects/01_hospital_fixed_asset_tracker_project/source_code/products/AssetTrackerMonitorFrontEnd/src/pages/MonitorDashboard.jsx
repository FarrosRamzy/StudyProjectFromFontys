/**
 * @file MonitorDashboard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Main dashboard page for asset and node overview.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../constants/appRoutes";
import { DashboardActivityPanel } from "../components/dashboard/DashboardActivityPanel";
import { DashboardSummaryGrid } from "../components/dashboard/DashboardSummaryGrid";
import { DashboardWarningsPanel } from "../components/dashboard/DashboardWarningsPanel";
import { buildDashboardSummary } from "../utils/dashboard/dashboardSummary";

export function MonitorDashboard({
    assets = [],
    nodes = [],
    movementRequests = [],
    alerts = [],
    activity = [],
    onNavigate,
}) {
    const summary = buildDashboardSummary({ assets, nodes, movementRequests, alerts });

    return (
        <div className="dashboard-page">
            <div className="section-header">
                <div>
                    <h2>Dashboard</h2>
                    <p>Live overview of registered assets, checkpoint nodes, movement status, and warnings.</p>
                </div>
                <button type="button" className="secondary-button" onClick={() => onNavigate?.(APP_ROUTES.ASSETS)}>View Assets</button>
            </div>
            <DashboardSummaryGrid assets={assets} nodes={nodes} summary={summary} onNavigate={onNavigate} />
            <div className="dashboard-grid">
                <DashboardWarningsPanel summary={summary} onNavigate={onNavigate} />
                <DashboardActivityPanel activity={activity} onNavigate={onNavigate} />
            </div>
        </div>
    );
}
