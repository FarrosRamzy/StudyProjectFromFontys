/**
 * @file SystemHealthPanel.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Dashboard system health panel for node and asset warnings.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { APP_ROUTES } from "../../constants/appRoutes";
import { ASSET_FLOW_STATUS } from "../../constants/assetFlowStatus";
import { NODE_STATUS } from "../../constants/nodeStatus";
import { AssetFlowBadge } from "../assets/AssetFlowBadge";
import { NodeStatusBadge } from "../nodes/NodeStatusBadge";
import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";
import { formatDeviceId, formatTagId } from "../../utils/textFormat";

export function SystemHealthPanel({ assets = [], nodes = [], alerts = [], maxItems = 6, onNavigate }) {
    const healthItems = buildHealthItems(assets, nodes, alerts).slice(0, maxItems);

    return (
        <section className="panel">
            <div className="section-header">
                <div><h2>System Health</h2><p>Important warnings from assets, checkpoint nodes, and realtime events.</p></div>
                <button type="button" className="ghost-button" onClick={() => onNavigate?.(APP_ROUTES.ALERTS)}>Open Alerts</button>
            </div>
            {healthItems.length === 0 ? (
                <div className="empty-state"><p>No active warnings. System health looks good.</p></div>
            ) : (
                <div className="summary-list">{healthItems.map((item) => <HealthItem key={item.id} item={item} />)}</div>
            )}
        </section>
    );
}

function buildHealthItems(assets, nodes, alerts) {
    return [
        ...assets.filter(isWarningAsset).map(makeAssetHealthItem),
        ...nodes.filter(isOfflineNode).map(makeNodeHealthItem),
        ...alerts.map(makeAlertHealthItem),
    ].sort(compareHealthItems);
}

function isWarningAsset(asset) {
    return [
        ASSET_FLOW_STATUS.PENDING_PLACEMENT,
        ASSET_FLOW_STATUS.WRONG_LOCATION,
        ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT,
    ].includes(asset.flow_status);
}

function isOfflineNode(node) {
    return [NODE_STATUS.OFFLINE, NODE_STATUS.DISABLED].includes(String(node.status || "").toUpperCase());
}

function makeAssetHealthItem(asset) {
    return {
        id: `asset-${asset.tag_id}-${asset.flow_status}`,
        type: "asset",
        severity: asset.flow_status === ASSET_FLOW_STATUS.UNAUTHORIZED_MOVEMENT ? "critical" : "warning",
        title: asset.item_name || "Unnamed asset",
        subtitle: asset.tag_id,
        status: asset.flow_status,
        location: asset.last_room_name || asset.assigned_room_name || "-",
        message: asset.movement_note || `Asset status is ${asset.flow_status || "unknown"}.`,
        createdAt: asset.last_seen_at,
    };
}

function makeNodeHealthItem(node) {
    return {
        id: `node-${node.device_id}-${node.status}`,
        type: "node",
        severity: "warning",
        title: node.alias || node.device_id || "Unnamed node",
        subtitle: node.device_id,
        status: node.status,
        location: node.room_name || "-",
        message: `Node is ${node.status || "unknown"}.`,
        createdAt: node.last_ping_at,
    };
}

function makeAlertHealthItem(alert) {
    return {
        id: alert.id,
        type: alert.type || "alert",
        severity: alert.severity || "warning",
        title: alert.title || "Alert",
        subtitle: alert.type || "",
        status: alert.severity || "warning",
        location: alert.asset?.last_room_name || alert.node?.room_name || "-",
        message: alert.message || "Alert detected.",
        createdAt: alert.createdAt,
    };
}

function compareHealthItems(a, b) {
    const order = { critical: 0, warning: 1, info: 2 };
    return (order[a.severity] ?? 9) - (order[b.severity] ?? 9) ||
        new Date(b.createdAt || 0) - new Date(a.createdAt || 0);
}

function HealthItem({ item }) {
    return (
        <article className={`summary-card ${item.severity === "critical" ? "danger" : "warning"}`}>
            <div className="summary-card-row"><div><strong>{item.title}</strong><span className="monitor-muted monitor-mono">{formatSubtitle(item)}</span></div><ItemBadge item={item} /></div>
            <span>{item.message}</span>
            <small title={formatDateTime(item.createdAt)}>Location: {item.location} · {getRelativeTime(item.createdAt)}</small>
        </article>
    );
}

function ItemBadge({ item }) {
    if (item.type === "asset") return <AssetFlowBadge flowStatus={item.status} />;
    if (item.type === "node") return <NodeStatusBadge status={item.status} />;
    return <span className={`status-badge ${item.severity === "critical" ? "danger" : "warning"}`}>{item.severity}</span>;
}

function formatSubtitle(item) {
    if (item.type === "asset") return formatTagId(item.subtitle);
    if (item.type === "node") return formatDeviceId(item.subtitle);
    return item.subtitle || "-";
}
