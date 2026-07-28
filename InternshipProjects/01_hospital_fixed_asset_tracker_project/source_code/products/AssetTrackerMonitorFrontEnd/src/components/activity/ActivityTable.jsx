/**
 * @file ActivityTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";
import { getActivityRelatedText } from "../../utils/activity/activityRelatedText";

export function ActivityTable({ activity, assets, nodes }) {
    return (
        <div className="table-panel">
            <table className="monitor-table">
                <thead><tr><th>Time</th><th>Event Type</th><th>Message</th><th>Related Data</th></tr></thead>
                <tbody>
                    {activity.map((item) => (
                        <tr key={item.id}>
                            <td className="monitor-primary-cell" data-label="Time">
                                <strong>{getRelativeTime(item.createdAt)}</strong>
                                <div className="monitor-muted">{formatDateTime(item.createdAt)}</div>
                            </td>
                            <td data-label="Event Type"><span className="status-badge info">{item.type || "system"}</span></td>
                            <td data-label="Message"><strong>{item.message || "-"}</strong></td>
                            <td className="monitor-muted monitor-note" data-label="Related Data">
                                {getActivityRelatedText(item, assets, nodes)}
                            </td>
                        </tr>
                    ))}
                </tbody>
            </table>
            {activity.length === 0 && <div className="empty-state"><p>No activity found.</p></div>}
        </div>
    );
}
