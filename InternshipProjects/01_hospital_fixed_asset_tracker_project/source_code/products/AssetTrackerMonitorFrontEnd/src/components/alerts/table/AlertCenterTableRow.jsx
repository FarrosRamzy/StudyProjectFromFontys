/**
 * @file AlertCenterTableRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { formatDateTime, getRelativeTime } from "../../../utils/dateFormat";
import { AlertStatusCell } from "./AlertStatusCell";
import { AlertSubjectCell } from "./AlertSubjectCell";

export function AlertCenterTableRow({ alert }) {
    return (
        <tr key={alert.id} className={alert.severity === "critical" ? "monitor-row-danger" : "monitor-row-warning"}>
            <td data-label="Severity"><span className={`status-badge ${alert.severity === "critical" ? "danger" : "warning"}`}>{alert.severity || "warning"}</span></td>
            <td data-label="Type">{alert.type || "-"}</td>
            <td className="monitor-primary-cell" data-label="Subject"><AlertSubjectCell alert={alert} /></td>
            <td data-label="Status"><AlertStatusCell alert={alert} /></td>
            <td data-label="Location">{getAlertLocation(alert)}</td>
            <td className="monitor-note" data-label="Message">{alert.message || "-"}</td>
            <td data-label="Time"><strong>{getRelativeTime(alert.createdAt)}</strong><div className="monitor-muted">{formatDateTime(alert.createdAt)}</div></td>
        </tr>
    );
}

function getAlertLocation(alert) {
    if (alert.asset) return alert.asset.last_room_name || "-";
    if (alert.node) return alert.node.room_name || "-";
    return "-";
}
