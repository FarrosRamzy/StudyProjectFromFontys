/**
 * @file RecentActivityPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Recent realtime backend/WebSocket activity panel.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";

export function RecentActivityPanel({
    activity = [],
    maxItems = 8,
    onNavigate,
}) {
    const recentActivity = [...activity]
        .sort((a, b) => {
            return new Date(b.createdAt || 0) - new Date(a.createdAt || 0);
        })
        .slice(0, maxItems);

    return (
        <section className="panel">
            <div className="section-header">
                <div>
                    <h2>Recent Activity</h2>
                    <p>Latest realtime updates received by the monitor app.</p>
                </div>

                <button
                    type="button"
                    className="ghost-button"
                    onClick={() => onNavigate?.(APP_ROUTES.ACTIVITY)}
                >
                    View Activity
                </button>
            </div>

            {recentActivity.length === 0 ? (
                <div className="empty-state">
                    <p>No activity yet.</p>
                </div>
            ) : (
                <div className="summary-list">
                    {recentActivity.map((item) => (
                        <ActivityItem key={item.id} item={item} />
                    ))}
                </div>
            )}
        </section>
    );
}

function ActivityItem({ item }) {
    return (
        <article className="summary-card">
            <div className="summary-card-row">
                <strong>{item.message || "System event"}</strong>

                <span className="status-badge info">
                    {formatEventType(item.type)}
                </span>
            </div>

            <span>{getPayloadSummary(item.payload)}</span>

            <small title={formatDateTime(item.createdAt)}>
                {getRelativeTime(item.createdAt)}
            </small>
        </article>
    );
}

function formatEventType(type) {
    return String(type || "system")
        .replace(/_/g, " ")
        .replace(/\b\w/g, (letter) => letter.toUpperCase());
}

function getPayloadSummary(payload) {
    if (!payload) {
        return "No extra detail";
    }

    if (payload.item_name || payload.tag_id) {
        return [
            payload.item_name,
            payload.tag_id,
            payload.last_room_name || payload.room_name,
        ]
            .filter(Boolean)
            .join(" · ");
    }

    if (payload.alias || payload.device_id || payload.node_id) {
        return [
            payload.alias,
            payload.device_id || payload.node_id,
            payload.room_name,
            payload.status,
        ]
            .filter(Boolean)
            .join(" · ");
    }

    if (payload.message) {
        return payload.message;
    }

    return "System update";
}
