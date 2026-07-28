/**
 * @file NodeTable.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Table for displaying and managing registered/discovered nodes.
 * @version 1.3.0
 * @date 2026-04-30
 */


import { useNodeTable } from "../../hooks/nodes/useNodeTable";
import NodeTableHeader from "./table/NodeTableHeader";
import NodeTablePagination from "./table/NodeTablePagination";
import NodeTableRow from "./table/NodeTableRow";

export default function NodeTable({
    nodes = [],
    loading,
    selectedNode,
    onSelectNode,
    identifyingNodeId = "",
    onIdentifyNode,
}) {
    const table = useNodeTable(nodes, 5);

    if (loading) {
        return <EmptyNodeState title="Loading nodes..." message="Please wait while the system retrieves node data." />;
    }

    if (!nodes.length) {
        return (
            <EmptyNodeState
                title="No nodes detected yet"
                message="Power on a node and connect it to the backend. Newly discovered nodes will appear here."
            />
        );
    }

    return (
        <section className="panel table-panel">
            <div className="section-header table-header-row">
                <div>
                    <h2>Registered Nodes</h2>
                    <p>{table.filteredNodes.length} of {nodes.length} node{nodes.length === 1 ? "" : "s"} shown</p>
                </div>
                <div className="table-search">
                    <input
                        type="search"
                        value={table.searchTerm}
                        onChange={table.handleSearchChange}
                        placeholder="Search by alias, device ID, role, hospital, location, or status..."
                    />
                </div>
            </div>

            {table.filteredNodes.length === 0 ? (
                <div className="empty-state table-empty-search">
                    <h2>No matching nodes</h2>
                    <p>Try another alias, device ID, room, role, or status.</p>
                </div>
            ) : (
                <>
                    <table className="asset-table node-table">
                        <NodeTableHeader handleSort={table.handleSort} getSortLabel={table.getSortLabel} />
                        <tbody>
                            {table.visibleNodes.map((node) => (
                                <NodeTableRow
                                    key={node.device_id || node.id}
                                    node={node}
                                    selectedNode={selectedNode}
                                    identifyingNodeId={identifyingNodeId}
                                    onIdentifyNode={onIdentifyNode}
                                    onSelectNode={onSelectNode}
                                />
                            ))}
                        </tbody>
                    </table>
                    <NodeTablePagination {...table} />
                </>
            )}
        </section>
    );
}

function EmptyNodeState({ title, message }) {
    return (
        <section className="panel empty-state">
            <h2>{title}</h2>
            <p>{message}</p>
        </section>
    );
}
