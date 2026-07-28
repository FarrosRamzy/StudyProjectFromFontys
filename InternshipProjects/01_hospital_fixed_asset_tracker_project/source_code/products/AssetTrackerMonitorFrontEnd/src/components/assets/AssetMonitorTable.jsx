/**
 * @file AssetMonitorTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable asset monitor table.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { Pagination } from "../common/Pagination";
import { AssetMonitorTableHeader } from "./table/AssetMonitorTableHeader";
import { AssetMonitorTableRow } from "./table/AssetMonitorTableRow";

export function AssetMonitorTable({
    assets = [],
    movementRequests = [],
    sortKey,
    getSortButtonLabel,
    onSort,
    cancelingRequestId,
    onCancelRequest,
    onRequestMove,
    pagination,
}) {
    return (
        <div className="table-panel">
            <table className="monitor-table">
                <AssetMonitorTableHeader
                    sortKey={sortKey}
                    getSortButtonLabel={getSortButtonLabel}
                    onSort={onSort}
                />
                <tbody>
                    {assets.map((asset) => (
                        <AssetMonitorTableRow
                            key={asset.tag_id}
                            asset={asset}
                            movementRequests={movementRequests}
                            cancelingRequestId={cancelingRequestId}
                            onCancelRequest={onCancelRequest}
                            onRequestMove={onRequestMove}
                        />
                    ))}
                </tbody>
            </table>
            <Pagination {...pagination} />
            {pagination.totalItems === 0 && <div className="empty-state"><p>No assets found.</p></div>}
        </div>
    );
}
