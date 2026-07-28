/**
 * @file AlertCenterTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Table for displaying generated and realtime alerts.
 * @version 1.0.0
 * @date 2026-05-22

 * @Copyright (c) 2026
 */


import { Pagination } from "../common/Pagination";
import { AlertCenterTableHeader } from "./table/AlertCenterTableHeader";
import { AlertCenterTableRow } from "./table/AlertCenterTableRow";

export function AlertCenterTable({ alerts, sort, pagination }) {
    return (
        <div className="table-panel">
            <table className="monitor-table">
                <AlertCenterTableHeader
                    sortKey={sort.sortKey}
                    getSortButtonLabel={sort.getSortButtonLabel}
                    onSort={sort.requestSort}
                />
                <tbody>{alerts.map((alert) => <AlertCenterTableRow key={alert.id} alert={alert} />)}</tbody>
            </table>
            <Pagination {...pagination} />
            {pagination.totalItems === 0 && <div className="empty-state"><p>No active alerts.</p></div>}
        </div>
    );
}
