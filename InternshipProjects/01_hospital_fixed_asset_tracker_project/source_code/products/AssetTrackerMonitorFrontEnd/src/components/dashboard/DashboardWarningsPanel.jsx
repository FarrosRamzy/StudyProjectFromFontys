/**
 * @file DashboardWarningsPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";

export function DashboardWarningsPanel({ summary, onNavigate }) {
    const empty = summary.recentWarnings.length === 0 &&
        summary.nodeIssueAlerts.length === 0 &&
        summary.realtimeAlerts.length === 0;

    return (
        <section className="panel">
            <PanelHeader onNavigate={onNavigate} />
            {empty ? <div className="empty-state"><p>No active warnings.</p></div> : (
                <div className="summary-list">
                    {summary.recentWarnings.map((asset) => <AssetWarningCard key={asset.tag_id} asset={asset} />)}
                    {summary.nodeIssueAlerts.slice(0, 5).map((alert) => <NodeWarningCard key={alert.id} alert={alert} />)}
                    {summary.realtimeAlerts.slice(0, 5).map((alert) => <RealtimeWarningCard key={alert.id} alert={alert} />)}
                </div>
            )}
        </section>
    );
}

function PanelHeader({ onNavigate }) {
    return (
        <div className="section-header">
            <div><h2>Recent Warnings</h2><p>Assets and nodes that need attention.</p></div>
            <button type="button" className="ghost-button" onClick={() => onNavigate?.(APP_ROUTES.ALERTS)}>Open Alerts</button>
        </div>
    );
}

function AssetWarningCard({ asset }) {
    return (
        <article className="summary-card danger">
            <strong>{asset.item_name || "Unnamed asset"}</strong>
            <span>{asset.movement_note || asset.flow_status || "Asset warning"}</span>
            <small>Last seen: {getRelativeTime(asset.last_seen_at)}</small>
        </article>
    );
}

function NodeWarningCard({ alert }) {
    return (
        <article className="summary-card warning">
            <strong>{alert.title}</strong><span>{alert.message}</span>
            <small>Last ping: {getRelativeTime(alert.createdAt)}</small>
        </article>
    );
}

function RealtimeWarningCard({ alert }) {
    return (
        <article className={`summary-card ${alert.severity === "critical" ? "danger" : "warning"}`}>
            <strong>{alert.title}</strong><span>{alert.message}</span>
            <small>{formatDateTime(alert.createdAt)}</small>
        </article>
    );
}
