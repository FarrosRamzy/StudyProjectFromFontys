/**
 * @file NodeMonitorTableHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { SortHeader } from "../../common/SortHeader";

const HEADERS = [
    ["Node", "node"], ["Role", "role"], ["Status", "status"],
    ["Room", "room"], ["Hospital", "hospital"], ["Provisioned", "provisioned"],
    ["Last Ping", "last_ping"], ["Last Event", "last_event"],
];

export function NodeMonitorTableHeader({ sortKey, getSortButtonLabel, onSort }) {
    return (
        <thead>
            <tr>
                {HEADERS.map(([label, key]) => (
                    <th key={key}>
                        <SortHeader label={label} sortKey={key} activeSortKey={sortKey} getSortButtonLabel={getSortButtonLabel} onSort={onSort} />
                    </th>
                ))}
            </tr>
        </thead>
    );
}
