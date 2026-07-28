/**
 * @file NodeMonitor.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Node monitor page for registration and checkpoint devices.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { usePagination } from "../hooks/common/usePagination";
import { useSortableTable } from "../hooks/common/useSortTable";
import { useNodeFilters } from "../hooks/monitor/useMonitorFilters";
import { NodeMonitorTable } from "../components/nodes/NodeMonitorTable";
import { NodeMonitorToolbar } from "../components/nodes/NodeMonitorToolbar";

const NODE_SORT_ACCESSORS = {
    node: (node) => node.alias || node.device_id || "",
    role: (node) => node.role || "",
    status: (node) => node.status || "",
    room: (node) => node.room_name || "",
    hospital: (node) => node.hospital_name || "",
    provisioned: (node) => (node.is_provisioned ? 1 : 0),
    last_ping: (node) => node.last_ping_at || "",
    last_event: (node) => node.last_event_at || "",
};

export function NodeMonitor({ nodes = [], onRefresh }) {
    const filters = useNodeFilters(nodes);
    const sort = useSortableTable(filters.filteredNodes, {
        defaultSortKey: "role",
        defaultDirection: "asc",
        accessors: NODE_SORT_ACCESSORS,
    });
    const pagination = usePagination(sort.sortedItems, 10, [
        filters.search,
        filters.nodeStatus,
        filters.nodeRole,
        sort.sortKey,
    ]);

    return (
        <div>
            <PageHeader shown={sort.sortedItems.length} total={nodes.length} onRefresh={onRefresh} />
            <NodeMonitorToolbar {...filters} />
            <NodeMonitorTable
                nodes={pagination.paginatedItems}
                sort={sort}
                pagination={{
                    page: pagination.currentPage,
                    totalPages: pagination.totalPages,
                    totalItems: pagination.totalItems,
                    pageSize: pagination.pageSize,
                    onPageChange: pagination.setCurrentPage,
                }}
            />
        </div>
    );
}

function PageHeader({ shown, total, onRefresh }) {
    return (
        <div className="section-header">
            <div>
                <h2>Node Monitor</h2>
                <p>Monitor registration desks and checkpoint nodes across hospital rooms.</p>
                <p className="table-result-count">{shown} of {total} nodes shown</p>
            </div>
            <button type="button" className="secondary-button" onClick={onRefresh}>Refresh</button>
        </div>
    );
}
