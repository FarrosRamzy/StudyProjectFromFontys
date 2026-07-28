/**
 * @file UnknownTagTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Table for unknown RFID tag detection alerts.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";
import { formatTagId } from "../../utils/textFormat";

export function UnknownTagTable({ alerts = [] }) {
    const unknownTagAlerts = alerts.filter((alert) => {
        const type = String(alert.type || "").toLowerCase();

        return (
            type === "unknown_tag_detected" ||
            type === "unknown_tag" ||
            alert.payload?.tag_id
        );
    });

    return (
        <div className="table-panel">
            <table className="monitor-table">
                <thead>
                    <tr>
                        <th>Tag ID</th>
                        <th>Detected Room</th>
                        <th>Detected Node</th>
                        <th>Message</th>
                        <th>Detected At</th>
                    </tr>
                </thead>

                <tbody>
                    {unknownTagAlerts.map((alert) => {
                        const payload = alert.payload || {};

                        return (
                            <tr
                                key={alert.id}
                                className="monitor-row-warning"
                            >
                                <td
                                    className="monitor-mono"
                                    title={payload.tag_id || ""}
                                >
                                    {formatTagId(payload.tag_id || "-")}
                                </td>

                                <td>
                                    {payload.room_name ||
                                        payload.location_name ||
                                        "-"}
                                </td>

                                <td className="monitor-mono">
                                    {payload.device_id ||
                                        payload.node_id ||
                                        payload.nodeId ||
                                        "-"}
                                </td>

                                <td className="monitor-note">
                                    {alert.message ||
                                        payload.message ||
                                        "Unknown RFID tag detected."}
                                </td>

                                <td>
                                    <strong>
                                        {getRelativeTime(
                                            payload.timestamp ||
                                                alert.createdAt
                                        )}
                                    </strong>

                                    <div className="monitor-muted">
                                        {formatDateTime(
                                            payload.timestamp ||
                                                alert.createdAt
                                        )}
                                    </div>
                                </td>
                            </tr>
                        );
                    })}
                </tbody>
            </table>

            {unknownTagAlerts.length === 0 && (
                <div className="empty-state">
                    <p>No unknown tag detections.</p>
                </div>
            )}
        </div>
    );
}
