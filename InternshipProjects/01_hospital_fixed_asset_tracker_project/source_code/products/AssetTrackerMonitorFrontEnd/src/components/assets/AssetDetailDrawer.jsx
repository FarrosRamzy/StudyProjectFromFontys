/**
 * @file AssetDetailDrawer.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Side drawer for viewing detailed asset information.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { AssetFlowBadge } from "./AssetFlowBadge";
import { formatDateTime, getRelativeTime } from "../../utils/dateFormat";
import { formatTagId } from "../../utils/textFormat";
import { getAssetLocationSummary, isAssetAvailableForMovement } from "../../utils/flowStatus";

export function AssetDetailDrawer({ asset, onClose, onRequestMove }) {
    if (!asset) return null;
    const sections = buildAssetDetailSections(asset);

    return (
        <div className="drawer-backdrop" role="presentation">
            <aside className="drawer-panel" role="dialog" aria-modal="true" aria-label="Asset detail">
                <div className="drawer-header">
                    <div><h2>{asset.item_name || "Unnamed asset"}</h2><p className="monitor-mono">{formatTagId(asset.tag_id)}</p></div>
                    <button type="button" className="ghost-button small" onClick={onClose}>Close</button>
                </div>
                {sections.map((section) => <DetailSection key={section.title} {...section} />)}
                <div className="drawer-actions">
                    <button type="button" className="secondary-button" onClick={onClose}>Close</button>
                    <button
                        type="button"
                        className="primary-button"
                        disabled={!isAssetAvailableForMovement(asset)}
                        onClick={() => onRequestMove?.(asset)}
                    >
                        Request Move
                    </button>
                </div>
            </aside>
        </div>
    );
}

function buildAssetDetailSections(asset) {
    return [
        {
            title: "Status",
            items: [
                ["Asset Status", asset.status || "-"],
                ["Flow Status", <AssetFlowBadge flowStatus={asset.flow_status} />],
                ["Location Summary", getAssetLocationSummary(asset)],
                ["Movement Note", asset.movement_note || "-"],
            ],
        },
        {
            title: "Location",
            items: [
                ["Current Room", asset.last_room_name || "-"],
                ["Current Node", asset.last_node_id || asset.last_device_id || "-", true],
                ["Assigned Room", asset.assigned_room_name || "-"],
                ["Assigned Node", asset.assigned_node_id || "-", true],
                ["Expected Room", asset.expected_room_name || "-"],
                ["Expected Node", asset.expected_node_id || "-", true],
            ],
        },
        {
            title: "Timing",
            items: [
                ["Last Seen", getRelativeTime(asset.last_seen_at)],
                ["Last Seen Date", formatDateTime(asset.last_seen_at)],
                ["Registered At", formatDateTime(asset.registered_at)],
                ["Deregistered At", formatDateTime(asset.deregistered_at)],
            ],
        },
        {
            title: "Hospital",
            items: [["Hospital", asset.hospital_name || "-"], ["Hospital ID", asset.hospital_id || "-", true]],
        },
    ];
}

function DetailSection({ title, items }) {
    return (
        <div className="drawer-section">
            <h3>{title}</h3>
            <div className="detail-grid">
                {items.map(([label, value, mono]) => <DetailItem key={label} label={label} value={value} mono={mono} />)}
            </div>
        </div>
    );
}

function DetailItem({ label, value, mono = false }) {
    return <div className="detail-item"><span>{label}</span><strong className={mono ? "monitor-mono" : ""}>{value}</strong></div>;
}
