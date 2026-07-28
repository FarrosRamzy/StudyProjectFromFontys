/**
 * @file AlertCenterTableHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { SortHeader } from "../../common/SortHeader";

const HEADERS = [
    ["Severity", "severity"], ["Type", "type"], ["Subject", "subject"],
    ["Status", "status"], ["Location", "location"], ["Time", "time"],
];

export function AlertCenterTableHeader({ sortKey, getSortButtonLabel, onSort }) {
    return (
        <thead>
            <tr>
                {HEADERS.slice(0, 5).map(([label, key]) => (
                    <th key={key}><SortHeader label={label} sortKey={key} activeSortKey={sortKey} getSortButtonLabel={getSortButtonLabel} onSort={onSort} /></th>
                ))}
                <th>Message</th>
                <th><SortHeader label="Time" sortKey="time" activeSortKey={sortKey} getSortButtonLabel={getSortButtonLabel} onSort={onSort} /></th>
            </tr>
        </thead>
    );
}
