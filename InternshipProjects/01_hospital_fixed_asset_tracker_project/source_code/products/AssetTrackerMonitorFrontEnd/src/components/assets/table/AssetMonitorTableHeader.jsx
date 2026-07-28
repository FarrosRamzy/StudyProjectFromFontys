/**
 * @file AssetMonitorTableHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { SortHeader } from "../../common/SortHeader";

const HEADERS = [
    ["Asset", "asset"], ["Tag ID", "tag_id"], ["Flow Status", "flow_status"],
    ["Current", "current"], ["Assigned", "assigned"], ["Expected", "expected"],
    ["Last Seen", "last_seen"],
];

export function AssetMonitorTableHeader({ sortKey, getSortButtonLabel, onSort }) {
    return (
        <thead>
            <tr>
                {HEADERS.map(([label, key]) => (
                    <th key={key}>
                        <SortHeader
                            label={label}
                            sortKey={key}
                            activeSortKey={sortKey}
                            getSortButtonLabel={getSortButtonLabel}
                            onSort={onSort}
                        />
                    </th>
                ))}
                <th>Note</th>
                <th>Action</th>
            </tr>
        </thead>
    );
}
