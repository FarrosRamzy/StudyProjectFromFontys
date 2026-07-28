/**
 * @file AssetTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */


import { useAssetSearch } from "../../hooks/assets/useAssetSearch";
import { useAssetSort } from "../../hooks/assets/useAssetSort";
import { usePagination } from "../../hooks/usePagination";
import AssetTableHeader from "./table/AssetTableHeader";
import AssetTablePagination from "./table/AssetTablePagination";
import AssetTableRow from "./table/AssetTableRow";

export default function AssetTable({
    assets,
    loading,
    deletingTagId,
    onUseForDeregister,
    onDeleteAsset,
}) {
    const { searchTerm, setSearchTerm, filteredAssets } = useAssetSearch(assets);
    const { sortedAssets, handleSort, getSortLabel } = useAssetSort(filteredAssets);
    const pagination = usePagination(sortedAssets, 5);

    if (loading) {
        return <EmptyAssetState title="Loading assets..." message="Please wait while the system retrieves asset data." />;
    }

    if (!assets.length) {
        return <EmptyAssetState title="No assets registered yet" message="Scan a tag and register your first hospital asset." />;
    }

    return (
        <section className="panel table-panel">
            <div className="section-header table-header-row">
                <div>
                    <h2>Registered Assets</h2>
                    <p>{filteredAssets.length} of {assets.length} asset{assets.length === 1 ? "" : "s"} registered</p>
                </div>
                <div className="table-search">
                    <input
                        type="search"
                        value={searchTerm}
                        onChange={(event) => {
                            setSearchTerm(event.target.value);
                            pagination.resetPage();
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
                    <table className="asset-table asset-registration-table">
                        <AssetTableHeader handleSort={handleSort} getSortLabel={getSortLabel} />
                        <tbody>
                            {pagination.visibleItems.map((asset) => (
                                <AssetTableRow
                                    key={asset.tag_id}
                                    asset={asset}
                                    deletingTagId={deletingTagId}
                                    onUseForDeregister={onUseForDeregister}
                                    onDeleteAsset={onDeleteAsset}
                                />
                            ))}
                        </tbody>
                    </table>
                    <AssetTablePagination {...pagination} />
                </>
            )}
        </section>
    );
}

function EmptyAssetState({ title, message }) {
    return (
        <section className="panel empty-state">
            <h2>{title}</h2>
            <p>{message}</p>
        </section>
    );
}
