/**
 * @file AssetMonitorTableRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { AssetFlowBadge } from "../AssetFlowBadge";
import { formatDateTime, getRelativeTime } from "../../../utils/dateFormat";
import { getAssetFlowRowClass, getAssetLocationSummary, isAssetAvailableForMovement } from "../../../utils/flowStatus";
import { formatTagId } from "../../../utils/textFormat";
import { getMovementRequestId, getPendingMovementRequestForAsset } from "../../../utils/assets/movementRequestLookup";

export function AssetMonitorTableRow({
    asset,
    movementRequests,
    cancelingRequestId,
    onCancelRequest,
    onRequestMove,
}) {
    const pendingRequest = getPendingMovementRequestForAsset(asset, movementRequests);
    const requestId = getMovementRequestId(pendingRequest);

    return (
        <tr key={asset.tag_id} className={getAssetFlowRowClass(asset.flow_status)}>
            <td className="monitor-primary-cell" data-label="Asset">
                <strong>{asset.item_name || "Unnamed asset"}</strong>
                <div className="monitor-muted">{asset.status || "unknown"}</div>
            </td>
            <td className="monitor-mono" data-label="Tag ID" title={asset.tag_id}>{formatTagId(asset.tag_id)}</td>
            <td data-label="Flow Status"><AssetFlowBadge flowStatus={asset.flow_status} /></td>
            <td data-label="Current"><strong>{asset.last_room_name || "-"}</strong><NodeId asset={asset} /></td>
            <td data-label="Assigned">{asset.assigned_room_name || "-"}</td>
            <td data-label="Expected">{asset.expected_room_name || "-"}</td>
            <td data-label="Last Seen"><strong>{getRelativeTime(asset.last_seen_at)}</strong><div className="monitor-muted">{formatDateTime(asset.last_seen_at)}</div></td>
            <td className="monitor-note" data-label="Note">{asset.movement_note || getAssetLocationSummary(asset)}</td>
            <td className="monitor-action-cell" data-label="Action">
                {pendingRequest ? (
                    <button type="button" className="danger-button small" disabled={Number(cancelingRequestId) === Number(requestId)} onClick={() => onCancelRequest(asset)}>
                        {Number(cancelingRequestId) === Number(requestId) ? "Cancelling..." : "Cancel Request"}
                    </button>
                ) : (
                    <button type="button" className="secondary-button small" disabled={!isAssetAvailableForMovement(asset)} onClick={() => onRequestMove(asset)}>
                        Request Move
                    </button>
                )}
            </td>
        </tr>
    );
}

function NodeId({ asset }) {
    return <div className="monitor-muted monitor-mono">{asset.last_node_id || asset.last_device_id || ""}</div>;
}
