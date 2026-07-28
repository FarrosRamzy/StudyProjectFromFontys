/**
 * @file AssetMonitor.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Asset monitor table and movement request entry point.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { usePagination } from "../hooks/common/usePagination";
import { useSortableTable } from "../hooks/common/useSortTable";
import { useAssetFilters } from "../hooks/monitor/useMonitorFilters";
import { useAssetMovementActions } from "../hooks/assets/useAssetMovementActions";
import { AssetMonitorToolbar } from "../components/assets/AssetMonitorToolbar";
import { AssetMonitorTable } from "../components/assets/AssetMonitorTable";
import { MovementRequestModal } from "../components/assets/MovementRequestModal";

const ASSET_SORT_ACCESSORS = {
    asset: (asset) => asset.item_name || "",
    tag_id: (asset) => asset.tag_id || "",
    flow_status: (asset) => asset.flow_status || "",
    current: (asset) => asset.last_room_name || "",
    assigned: (asset) => asset.assigned_room_name || "",
    expected: (asset) => asset.expected_room_name || "",
    last_seen: (asset) => asset.last_seen_at || "",
};

export function AssetMonitor({
    assets = [],
    nodes = [],
    movementRequests = [],
    onRefresh,
}) {
    const filters = useAssetFilters(assets);
    const movement = useAssetMovementActions({ movementRequests, onRefresh });
    const sort = useSortableTable(filters.filteredAssets, {
        defaultSortKey: "last_seen",
        defaultDirection: "desc",
        accessors: ASSET_SORT_ACCESSORS,
    });
    const pagination = usePagination(sort.sortedItems, 10, [
        filters.search,
        filters.flowStatus,
        filters.assetStatus,
        sort.sortKey,
    ]);

    return (
        <div>
            <PageHeader shown={sort.sortedItems.length} total={assets.length} onRefresh={onRefresh} />
            <RequestMessages error={movement.requestError} success={movement.requestSuccess} />
            <AssetMonitorToolbar {...filters} />
            <AssetMonitorTable
                assets={pagination.paginatedItems}
                movementRequests={movementRequests}
                sortKey={sort.sortKey}
                getSortButtonLabel={sort.getSortButtonLabel}
                onSort={sort.requestSort}
                cancelingRequestId={movement.cancelingRequestId}
                onCancelRequest={movement.cancelAssetMovementRequest}
                onRequestMove={(asset) => {
                    movement.setSelectedAsset(asset);
                    movement.clearMessages();
                }}
                pagination={{
                    page: pagination.currentPage,
                    totalPages: pagination.totalPages,
                    totalItems: pagination.totalItems,
                    pageSize: pagination.pageSize,
                    onPageChange: pagination.setCurrentPage,
                }}
            />
            {movement.selectedAsset && (
                <MovementRequestModal
                    asset={movement.selectedAsset}
                    nodes={nodes}
                    movementRequests={movementRequests}
                    submitting={movement.submittingRequest}
                    onClose={() => movement.setSelectedAsset(null)}
                    onSubmit={movement.submitMovementRequest}
                />
            )}
        </div>
    );
}

function PageHeader({ shown, total, onRefresh }) {
    return (
        <div className="section-header">
            <div>
                <h2>Asset Monitor</h2>
                <p>Monitor current asset location, assigned location, expected destination, and movement state.</p>
                <p className="table-result-count">{shown} of {total} assets shown</p>
            </div>
            <button type="button" className="secondary-button" onClick={onRefresh}>Refresh</button>
        </div>
    );
}

function RequestMessages({ error, success }) {
    return (
        <>
            {error && <div className="message-banner error">{error}</div>}
            {success && <div className="message-banner success">{success}</div>}
        </>
    );
}
