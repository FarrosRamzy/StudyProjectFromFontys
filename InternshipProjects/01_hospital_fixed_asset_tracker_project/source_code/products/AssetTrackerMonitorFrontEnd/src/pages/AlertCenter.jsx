/**
 * @file AlertCenter.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Alert center for wrong-location assets, unauthorized movement, and node issues.
 * @version 1.0.0
 * @date 2026-05-21

 * @Copyright (c) 2026
 */


import { usePagination } from "../hooks/common/usePagination";
import { useSortableTable } from "../hooks/common/useSortTable";
import { useAlertFilters } from "../hooks/monitor/useMonitorFilters";
import { AlertCenterTable } from "../components/alerts/AlertCenterTable";
import { AlertCenterToolbar } from "../components/alerts/AlertCenterToolbar";
import { buildCombinedAlerts } from "../utils/alerts/alertBuilders";

const ALERT_SORT_ACCESSORS = {
    severity: (alert) => alert.severity || "",
    type: (alert) => alert.type || "",
    subject: (alert) => alert.asset?.item_name || alert.node?.alias || alert.node?.device_id || alert.title || "",
    status: (alert) => alert.asset?.flow_status || alert.node?.status || alert.payload?.status || "",
    location: (alert) => alert.asset?.last_room_name || alert.node?.room_name || alert.payload?.room_name || "",
    time: (alert) => alert.createdAt || "",
};

export function AlertCenter({ assets = [], nodes = [], alerts = [], onRefresh }) {
    const combinedAlerts = buildCombinedAlerts({ assets, nodes, alerts });
    const filters = useAlertFilters(combinedAlerts);
    const sort = useSortableTable(filters.filteredAlerts, {
        defaultSortKey: "time",
        defaultDirection: "desc",
        accessors: ALERT_SORT_ACCESSORS,
    });
    const pagination = usePagination(sort.sortedItems, 10, [
        filters.search,
        filters.severity,
        filters.type,
        sort.sortKey,
    ]);

    return (
        <div>
            <PageHeader shown={sort.sortedItems.length} total={combinedAlerts.length} onRefresh={onRefresh} />
            <AlertCenterToolbar {...filters} />
            <AlertCenterTable
                alerts={pagination.paginatedItems}
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
                <h2>Alert Center</h2>
                <p>Review abnormal asset movement, unknown tags, and node issues.</p>
                <p className="table-result-count">{shown} of {total} alerts shown</p>
            </div>
            <button type="button" className="secondary-button" onClick={onRefresh}>Refresh</button>
        </div>
    );
}
