/**
 * @file DashboardActivityPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { formatDateTime } from "../../utils/dateFormat";

export function DashboardActivityPanel({ activity = [], onNavigate }) {
    return (
        <section className="panel">
            <div className="section-header">
                <div><h2>Recent Activity</h2><p>Latest realtime updates from the backend.</p></div>
                <button type="button" className="ghost-button" onClick={() => onNavigate?.(APP_ROUTES.ACTIVITY)}>View Activity</button>
            </div>
            {activity.length === 0 ? <div className="empty-state"><p>No activity yet.</p></div> : (
                <div className="summary-list">
                    {activity.slice(0, 8).map((item) => <ActivityCard key={item.id} item={item} />)}
                </div>
            )}
        </section>
    );
}

function ActivityCard({ item }) {
    return (
        <article className="summary-card">
            <strong>{item.message}</strong>
            <span>{item.type || "system"}</span>
            <small>{formatDateTime(item.createdAt)}</small>
        </article>
    );
}
