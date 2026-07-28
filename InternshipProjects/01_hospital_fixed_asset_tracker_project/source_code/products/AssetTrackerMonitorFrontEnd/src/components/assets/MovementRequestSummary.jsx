/**
 * @file MovementRequestSummary.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { AssetFlowBadge } from "./AssetFlowBadge";
import { formatDateTime } from "../../utils/dateFormat";
import { formatTagId } from "../../utils/textFormat";

export function MovementRequestSummary({ asset }) {
    return (
        <div className="asset-request-summary">
            <SummaryItem label="Asset" value={asset.item_name || "Unnamed asset"} />
            <SummaryItem label="Tag ID" value={formatTagId(asset.tag_id)} mono />
            <div><span>Status</span><AssetFlowBadge flowStatus={asset.flow_status} /></div>
            <SummaryItem label="Assigned Room" value={asset.assigned_room_name || "-"} />
            <SummaryItem label="Current Room" value={asset.last_room_name || "-"} />
            <SummaryItem label="Last Seen" value={formatDateTime(asset.last_seen_at)} />
        </div>
    );
}

function SummaryItem({ label, value, mono = false }) {
    return <div><span>{label}</span><strong className={mono ? "monitor-mono" : ""}>{value}</strong></div>;
}
