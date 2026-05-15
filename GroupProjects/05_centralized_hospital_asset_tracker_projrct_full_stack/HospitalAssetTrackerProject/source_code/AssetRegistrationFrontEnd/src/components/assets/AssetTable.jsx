/**
 * @file AssetTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */

import StatusBadge from "./StatusBadge";
import { formatDateTime, formatTagId } from "../../utils/assetFormatters";
import { useAssetSort } from "../../hooks/useAssetSort";
import { usePagination } from "../../hooks/usePagination";
import { useAssetSearch } from "../../hooks/useAssetSearch";

export default function AssetTable({
    assets,
    loading,
    deletingTagId,
    onUseForDeregister,
    onDeleteAsset,
}) {
    const {
        searchTerm, setSearchTerm, filteredAssets
    } = useAssetSearch(assets);

    const {
        sortedAssets,handleSort, getSortIndicator
    } = useAssetSort(filteredAssets);

    const {
        currentPage, totalPages, visibleItems,
        pageInput, resetPage, handlePageInputChange,
        handlePageInputBlur, handlePageInputKeyDown,
        goToPreviousPage, goToNextPage
    } = usePagination(sortedAssets, 5);

    if (loading) {
        return (
            <section className="panel empty-state">
                <h2>Loading assets...</h2>
                <p>Please wait while the system retrieves asset data.</p>
            </section>
        );
    }

    if (!assets.length) {
        return (
            <section className="panel empty-state">
                <h2>No assets registered yet</h2>
                <p>Scan a tag and register your first hospital asset.</p>
            </section>
        );
    }

    return (
        <section className="panel table-panel">
            <div className="section-header table-header-row">
                <div>
                    <h2>Registered Assets</h2>
                    <p>
                        {filteredAssets.length} of {assets.length} asset
                        {assets.length === 1 ? "" : "s"} registered
                    </p>
                </div>

                <div className="table-search">
                    <input
                        type="search"
                        value={searchTerm}
                        onChange={(event) => {
                            setSearchTerm(event.target.value);
                            resetPage();
                        }}
                        placeholder="Search by ID, name, status, or location ..."
                    />
                </div>
            </div>

            {filteredAssets.length === 0 ? (
                <div className="empty-state table-empty-search">
                    <h2>No matching assets</h2>
                    <p>Try another tag ID, name, status, or location.</p>
                </div>
            ) : (
                <>
                    <table className="asset-table">
                        <thead>
                            <tr>
                                <th className="sticky-col sticky-col-1">
                                    <button
                                        type="button"
                                        className="sortable-header"
                                        onClick={() => handleSort("tag_id")}
                                    >
                                        Tag ID{getSortIndicator("tag_id")}
                                    </button>
                                </th>

                                <th className="sticky-col sticky-col-2">
                                    <button
                                        type="button"
                                        className="sortable-header"
                                        onClick={() => handleSort("item_name")}
                                    >
                                        Asset Name{getSortIndicator("item_name")}
                                    </button>
                                </th>

                                <th className="status-col">
                                    <button
                                        type="button"
                                        className="sortable-header"
                                        onClick={() => handleSort("status")}
                                    >
                                        Status{getSortIndicator("status")}
                                    </button>
                                </th>

                                <th className="location-col">
                                    <button
                                        type="button"
                                        className="sortable-header"
                                        onClick={() => handleSort("location")}
                                    >
                                        Last Location{getSortIndicator("location")}
                                    </button>
                                </th>

                                <th className="seen-col">
                                    <button
                                        type="button"
                                        className="sortable-header"
                                        onClick={() => handleSort("last_seen_at")}
                                    >
                                        Last Seen{getSortIndicator("last_seen_at")}
                                    </button>
                                </th>
                                <th className="action-col">Action</th>
                            </tr>
                        </thead>

                        <tbody>
                            {visibleItems.map((asset) => (
                                <tr key={asset.tag_id}>
                                    <td className="tag-cell sticky-col sticky-col-1" title={asset.tag_id}>
                                        {formatTagId(asset.tag_id)}
                                    </td>

                                    <td className="sticky-col sticky-col-2">
                                        {asset.item_name || "-"}
                                    </td>

                                    <td className="status-col">
                                        <StatusBadge status={asset.status} />
                                    </td>

                                    <td className="last-location-col">
                                        {asset.last_location || asset.last_room_name || "-"}
                                    </td>

                                    <td className="last-seen-col">
                                        {formatDateTime(asset.last_seen_at)}
                                    </td>

                                    <td className="action-col">
                                        {asset.status === "active" && (
                                            <button
                                                type="button"
                                                className="small-button"
                                                onClick={() => onUseForDeregister(asset)}
                                            >
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
                            ))}
                        </tbody>
                    </table>

                    {totalPages > 1 && (
                        <div className="simple-pagination">
                            <button
                                type="button"
                                className="pagination-button"
                                onClick={goToPreviousPage}
                                disabled={currentPage <= 1}
                            >
                                Previous
                            </button>

                            <div className="pagination-page-jump">
                                <span>Page</span>

                                <input
                                    className="pagination-page-input"
                                    type="number"
                                    min="1"
                                    max={totalPages}
                                    value={pageInput}
                                    onChange={handlePageInputChange}
                                    onBlur={handlePageInputBlur}
                                    onKeyDown={handlePageInputKeyDown}
                                />

                                <span>of {totalPages}</span>
                            </div>

                            <button
                                type="button"
                                className="pagination-button"
                                onClick={goToNextPage}
                                disabled={currentPage >= totalPages}
                            >
                                Next
                            </button>
                        </div>
                    )}
                </>
            )}
        </section>
    );
}