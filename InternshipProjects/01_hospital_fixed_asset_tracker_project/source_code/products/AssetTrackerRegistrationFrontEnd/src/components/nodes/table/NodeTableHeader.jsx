/**
 * @file NodeTableHeader.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


const COLUMNS = [
    ["Device Name", "device"],
    ["Role", "role"],
    ["Status", "status"],
    ["Hospital", "hospital"],
    ["Location", "location"],
    ["Last Ping", "last_ping_at"],
];

export default function NodeTableHeader({ handleSort, getSortLabel }) {
    return (
        <thead>
            <tr>
                {COLUMNS.map(([label, key]) => (
                    <th key={key}>
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
