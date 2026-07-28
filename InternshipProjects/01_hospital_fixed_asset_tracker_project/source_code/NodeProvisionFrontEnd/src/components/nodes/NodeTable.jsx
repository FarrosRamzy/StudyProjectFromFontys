/**
 * @file NodeTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Table for displaying and managing registered/discovered nodes.
 * @version 1.3.0
 * @date 2026-04-30
 */

/**
 * @file NodeTable.jsx
 * @description 
 */

import NodeStatusBadge from "./NodeStatusBadge";
import NodeRoleBadge from "./NodeRoleBadge";

import { useNodeTable } from "../../hooks/useNodeTable";

import {
    canEditNode,
    getNodeIdentity,
} from "../../utils/nodeHelpers";

import {
    formatLastPing,
    formatNodeHospital,
    formatNodeLocation,
    formatNodeName,
    formatShortNodeId,
} from "../../utils/nodeFormatters";

export default function NodeTable({
    nodes = [],
    loading,
    selectedNode,
    onSelectNode,
    identifyingNodeId = "",
    onIdentifyNode,
}) {
    const {
        searchTerm, handleSearchChange,
        filteredNodes, visibleNodes,
        handleSort, getSortLabel,
        currentPage, totalPages, pageInput,
        goToPreviousPage, goToNextPage,
        handlePageInputChange, handlePageInputBlur, handlePageInputKeyDown,
    } = useNodeTable(nodes, 5);

    if (loading) {
        return (
            <section className="panel empty-state">
                <h2>Loading nodes...</h2>
                <p>Please wait while the system retrieves node data.</p>
            </section>
        );
    }

    if (!nodes.length) {
        return (
            <section className="panel empty-state">
                <h2>No nodes detected yet</h2>
                <p>
                    Power on a node and connect it to the backend. Newly
                    discovered nodes will appear here.
                </p>
            </section>
        );
    }

    return (
        <section className="panel table-panel">
            <div className="section-header table-header-row">
                <div>
                    <h2>Registered Nodes</h2>
                    <p>
                        {filteredNodes.length} of {nodes.length} node
                        {nodes.length === 1 ? "" : "s"} shown
                    </p>
                </div>

                <div className="table-search">
                    <input
                        type="search"
                        value={searchTerm}
                        onChange={handleSearchChange}
                        placeholder="Search by alias, device ID, role, hospital, location, or status..."
                    />
                </div>
            </div>

            {filteredNodes.length === 0 ? (
                <div className="empty-state table-empty-search">
                    <h2>No matching nodes</h2>
                    <p>Try another alias, device ID, room, role, or status.</p>
                </div>
            ) : (
                <>
                    <table className="asset-table node-table">
                        <thead>
                            <tr>
                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("device")}
                                    >
                                        {getSortLabel("Device Name", "device")}
                                    </button>
                                </th>

                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("role")}
                                    >
                                        {getSortLabel("Role", "role")}
                                    </button>
                                </th>

                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("status")}
                                    >
                                        {getSortLabel("Status", "status")}
                                    </button>
                                </th>

                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("hospital")}
                                    >
                                        {getSortLabel("Hospital", "hospital")}
                                    </button>
                                </th>

                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("location")}
                                    >
                                        {getSortLabel("Location", "location")}
                                    </button>
                                </th>

                                <th>
                                    <button
                                        type="button"
                                        className="table-sort-button"
                                        onClick={() => handleSort("last_ping_at")}
                                    >
                                        {getSortLabel("Last Ping", "last_ping_at")}
                                    </button>
                                </th>
                                <th className="action-col">Action</th>
                            </tr>
                        </thead>

                        <tbody>
                            {visibleNodes.map((node) => {
                                const deviceId = getNodeIdentity(node);
                                const actionLabel = canEditNode(node) ? "Edit" : "Assign";
                                const isSelected = selectedNode?.device_id === deviceId;

                                const isAssigned = Boolean(node.is_provisioned);
                                const nodeStatus = String(node.status || "").toUpperCase();
                                const isOffline = nodeStatus === "OFFLINE";
                                const isDisabled = nodeStatus === "DISABLED";

                                const showBlinkButton = isAssigned;
                                const canIdentify = showBlinkButton && !isOffline && !isDisabled;
                                const isIdentifying = identifyingNodeId === deviceId;

                                return (
                                    <tr key={deviceId} className={
                                        isSelected
                                            ? "selected-row"
                                            : ""
                                    }>
                                        <td className="device-cell">
                                            <strong className="device-alias">
                                                {formatNodeName(node)}
                                            </strong>

                                            <span
                                                className="device-id-small"
                                                title={deviceId}
                                            >
                                                {formatShortNodeId(node)}
                                            </span>
                                        </td>

                                        <td>
                                            <NodeRoleBadge role={node.role} />
                                        </td>

                                        <td>
                                            <NodeStatusBadge status={node.status} />
                                        </td>

                                        <td>{formatNodeHospital(node)}</td>

                                        <td>{formatNodeLocation(node)}</td>

                                        <td>{formatLastPing(node)}</td>

                                        <td className="action-col">
                                            <div className="node-action-buttons">
                                                {showBlinkButton && (
                                                    <button
                                                        type="button"
                                                        className="node-action-button node-action-button-secondary"
                                                        disabled={!canIdentify || isIdentifying}
                                                        title={
                                                            isOffline
                                                                ? "This node is offline. Blink is unavailable."
                                                                : isDisabled
                                                                    ? "This node is disabled. Blink is unavailable."
                                                                    : "Ask this physical node to blink"
                                                        }
                                                        onClick={() => onIdentifyNode?.(deviceId)}
                                                    >
                                                        {isIdentifying ? "Blinking..." : "Blink"}
                                                    </button>
                                                )}

                                                <button
                                                    type="button"
                                                    className={
                                                        isSelected
                                                            ? "node-action-button node-action-button-selected"
                                                            : "node-action-button node-action-button-primary"
                                                    }
                                                    onClick={() => onSelectNode(node)}
                                                >
                                                    {isSelected ? "Close" : actionLabel}
                                                </button>
                                            </div>
                                        </td>
                                    </tr>
                                );
                            })}
                        </tbody>
                    </table>

                    {totalPages > 1 && (
                        <div className="simple-pagination">
                            <button
                                type="button"
                                className="pagination-button"
                                onClick={goToPreviousPage}
                                disabled={currentPage <= 1}
                            >
                                Previous
                            </button>

                            <div className="pagination-page-jump">
                                <span>Page</span>

                                <input
                                    className="pagination-page-input"
                                    type="number"
                                    min="1"
                                    max={totalPages}
                                    value={pageInput}
                                    onChange={handlePageInputChange}
                                    onBlur={handlePageInputBlur}
                                    onKeyDown={handlePageInputKeyDown}
                                />

                                <span>of {totalPages}</span>
                            </div>

                            <button
                                type="button"
                                className="pagination-button"
                                onClick={goToNextPage}
                                disabled={currentPage >= totalPages}
                            >
                                Next
                            </button>
                        </div>
                    )}
                </>
            )}
        </section>
    );
}