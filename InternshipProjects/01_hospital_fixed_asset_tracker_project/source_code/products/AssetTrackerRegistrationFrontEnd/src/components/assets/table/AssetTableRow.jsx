/**
 * @file AssetTableRow.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import StatusBadge from "../StatusBadge";
import { formatDateTime, formatTagId } from "../../../utils/assetFormatters";
import {
    getAssetFlowText,
    getAssetRowClass,
    shouldShowAssetFlowNote,
} from "../../../utils/assets/assetTableHelpers";

export default function AssetTableRow({
    asset,
    deletingTagId,
    onUseForDeregister,
    onDeleteAsset,
}) {
    return (
        <tr key={asset.tag_id} className={getAssetRowClass(asset)}>
            <td className="tag-cell sticky-col sticky-col-1" data-label="Tag ID" title={asset.tag_id}>
                {formatTagId(asset.tag_id)}
            </td>
            <td className="asset-name-cell sticky-col sticky-col-2" data-label="Asset Name">
                {asset.item_name || "-"}
            </td>
            <td className="status-col" data-label="Status">
                <div className="asset-status-stack">
                    <StatusBadge status={asset.status} />
                    <StatusBadge status={asset.flow_status || "unknown"} />
                    {shouldShowAssetFlowNote(asset) && (
                        <small className="asset-flow-note">{getAssetFlowText(asset)}</small>
                    )}
                </div>
            </td>
            <td className="last-location-col" data-label="Last Location">
                {asset.last_location || asset.last_room_name || "-"}
            </td>
            <td className="last-seen-col" data-label="Last Seen">
                {formatDateTime(asset.last_seen_at)}
            </td>
            <td className="action-col" data-label="Action">
                {asset.status === "active" && (
                    <button type="button" className="small-button" onClick={() => onUseForDeregister(asset)}>
                        Deregister
                    </button>
                )}
                {asset.status === "deregistered" && (
                    <button
                        type="button"
                        className="danger-small-button"
                        disabled={deletingTagId === asset.tag_id}
                        onClick={() => onDeleteAsset(asset)}
                    >
                        {deletingTagId === asset.tag_id ? "Deleting..." : "Delete"}
                    </button>
                )}
            </td>
        </tr>
    );
}
