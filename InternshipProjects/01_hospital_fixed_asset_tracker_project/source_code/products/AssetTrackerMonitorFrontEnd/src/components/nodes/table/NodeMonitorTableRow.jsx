/**
 * @file NodeMonitorTableRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { NodeRoleBadge } from "../NodeRoleBadge";
import { NodeStatusBadge } from "../NodeStatusBadge";
import { formatDateTime, getRelativeTime } from "../../../utils/dateFormat";
import { formatDeviceId } from "../../../utils/textFormat";

export function NodeMonitorTableRow({ node }) {
    return (
        <tr key={node.device_id}>
            <td className="monitor-primary-cell" data-label="Node">
                <strong>{node.alias || node.device_id || "Unnamed node"}</strong>
                <div className="monitor-muted monitor-mono" title={node.device_id}>{formatDeviceId(node.device_id)}</div>
            </td>
            <td data-label="Role"><NodeRoleBadge role={node.role} /></td>
            <td data-label="Status"><NodeStatusBadge status={node.status} isProvisioned={node.is_provisioned} /></td>
            <td data-label="Room">{node.room_name || "-"}</td>
            <td data-label="Hospital">{node.hospital_name || "-"}</td>
            <td data-label="Provisioned"><ProvisionedBadge value={node.is_provisioned} /></td>
            <td data-label="Last Ping"><strong>{getRelativeTime(node.last_ping_at)}</strong><div className="monitor-muted">{formatDateTime(node.last_ping_at)}</div></td>
            <td className="monitor-muted" data-label="Last Event">{formatDateTime(node.last_event_at)}</td>
        </tr>
    );
}

function ProvisionedBadge({ value }) {
    return (
        <span className={`status-badge ${value ? "success" : "warning"}`}>
            {value ? "Yes" : "No"}
        </span>
    );
}
