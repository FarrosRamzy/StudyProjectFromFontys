/**
 * @file NodeMonitorToolbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { NODE_ROLE_OPTIONS, NODE_STATUS_OPTIONS } from "../../constants/nodeStatus";

export function NodeMonitorToolbar({ search, setSearch, nodeRole, setNodeRole, nodeStatus, setNodeStatus }) {
    return (
        <div className="monitor-toolbar">
            <input
                className="monitor-search"
                value={search}
                onChange={(event) => setSearch(event.target.value)}
                placeholder="Search node, room, role, status..."
            />
            <div className="toolbar-controls">
                <select value={nodeRole} onChange={(event) => setNodeRole(event.target.value)}>
                    {NODE_ROLE_OPTIONS.map((option) => (
                        <option key={option.value} value={option.value.toLowerCase()}>{option.label}</option>
                    ))}
                </select>
                <select value={nodeStatus} onChange={(event) => setNodeStatus(event.target.value)}>
                    {NODE_STATUS_OPTIONS.map((option) => (
                        <option key={option.value} value={option.value}>{option.label}</option>
                    ))}
                </select>
            </div>
        </div>
    );
}
