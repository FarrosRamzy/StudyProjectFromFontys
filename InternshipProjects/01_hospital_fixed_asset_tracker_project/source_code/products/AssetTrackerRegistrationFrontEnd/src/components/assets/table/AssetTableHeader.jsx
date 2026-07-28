/**
 * @file AssetTableHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


const COLUMNS = [
    ["sticky-col sticky-col-1", "Tag ID", "tag_id"],
    ["sticky-col sticky-col-2", "Asset Name", "item_name"],
    ["status-col", "Status", "status"],
    ["location-col", "Last Location", "location"],
    ["seen-col", "Last Seen", "last_seen_at"],
];

export default function AssetTableHeader({ handleSort, getSortLabel }) {
    return (
        <thead>
            <tr>
                {COLUMNS.map(([className, label, key]) => (
                    <th key={key} className={className}>
                        <button
                            type="button"
                            className="table-sort-button"
                            onClick={() => handleSort(key)}
                        >
                            {getSortLabel(label, key)}
                        </button>
                    </th>
                ))}
                <th className="action-col">Action</th>
            </tr>
        </thead>
    );
}
