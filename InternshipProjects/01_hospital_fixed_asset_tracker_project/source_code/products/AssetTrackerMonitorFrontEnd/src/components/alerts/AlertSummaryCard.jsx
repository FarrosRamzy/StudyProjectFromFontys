/**
 * @file AlertSummaryCard.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable alert summary card for warning and critical states.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { AssetFlowBadge } from "../assets/AssetFlowBadge";
import { NodeStatusBadge } from "../nodes/NodeStatusBadge";

import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";
import { formatDeviceId, formatTagId } from "../../utils/textFormat";

export function AlertSummaryCard({ alert }) {
    const severity = String(alert?.severity || "warning").toLowerCase();

    return (
        <article className={`summary-card ${severity === "critical" ? "danger" : "warning"}`}>
            <div className="summary-card-row">
                <div>
                    <strong>{getAlertTitle(alert)}</strong>

                    <span className="monitor-muted monitor-mono">
                        {getAlertSubtitle(alert)}
                    </span>
                </div>

                {renderAlertStatus(alert)}
            </div>

            <span>{alert?.message || "Alert detected."}</span>

            <small title={formatDateTime(alert?.createdAt)}>
                {getAlertLocation(alert)} · {getRelativeTime(alert?.createdAt)}
            </small>
        </article>
    );
}

function getAlertTitle(alert) {
    if (alert?.asset) {
        return alert.asset.item_name || "Unnamed asset";
    }

    if (alert?.node) {
        return alert.node.alias || alert.node.device_id || "Unnamed node";
    }

    return alert?.title || "Alert";
}

function getAlertSubtitle(alert) {
    if (alert?.asset) {
        return formatTagId(alert.asset.tag_id);
    }

    if (alert?.node) {
        return formatDeviceId(alert.node.device_id);
    }

    if (alert?.payload?.tag_id) {
        return formatTagId(alert.payload.tag_id);
    }

    if (alert?.payload?.device_id || alert?.payload?.node_id) {
        return formatDeviceId(alert.payload.device_id || alert.payload.node_id);
    }

    return alert?.type || "-";
}

function getAlertLocation(alert) {
    if (alert?.asset) {
        return `Location: ${alert.asset.last_room_name || "-"}`;
    }

    if (alert?.node) {
        return `Room: ${alert.node.room_name || "-"}`;
    }

    if (alert?.payload?.room_name) {
        return `Room: ${alert.payload.room_name}`;
    }

    if (alert?.payload?.location_name) {
        return `Location: ${alert.payload.location_name}`;
    }

    return "Location: -";
}

function renderAlertStatus(alert) {
    if (alert?.asset) {
        return <AssetFlowBadge flowStatus={alert.asset.flow_status} />;
    }

    if (alert?.node) {
        return <NodeStatusBadge status={alert.node.status} />;
    }

    const severity = String(alert?.severity || "warning").toLowerCase();

    return (
        <span className={`status-badge ${severity === "critical" ? "danger" : "warning"}`}>
            {severity}
        </span>
    );
}
