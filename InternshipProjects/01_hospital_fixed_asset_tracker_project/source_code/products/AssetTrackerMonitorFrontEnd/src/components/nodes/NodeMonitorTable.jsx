/**
 * @file NodeMonitorTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Reusable table for displaying registered nodes.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { Pagination } from "../common/Pagination";
import { NodeMonitorTableHeader } from "./table/NodeMonitorTableHeader";
import { NodeMonitorTableRow } from "./table/NodeMonitorTableRow";

export function NodeMonitorTable({ nodes, sort, pagination }) {
    return (
        <div className="table-panel">
            <table className="monitor-table">
                <NodeMonitorTableHeader
                    sortKey={sort.sortKey}
                    getSortButtonLabel={sort.getSortButtonLabel}
                    onSort={sort.requestSort}
                />
                <tbody>{nodes.map((node) => <NodeMonitorTableRow key={node.device_id} node={node} />)}</tbody>
            </table>
            <Pagination {...pagination} />
            {pagination.totalItems === 0 && <div className="empty-state"><p>No nodes found.</p></div>}
        </div>
    );
}
