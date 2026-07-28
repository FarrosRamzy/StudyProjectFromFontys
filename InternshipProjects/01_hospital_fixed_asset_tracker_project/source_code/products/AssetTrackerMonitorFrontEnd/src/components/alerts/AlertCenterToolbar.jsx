/**
 * @file AlertCenterToolbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export function AlertCenterToolbar({ search, setSearch, type, setType, severity, setSeverity }) {
    return (
        <div className="monitor-toolbar">
            <input
                className="monitor-search"
                value={search}
                onChange={(event) => setSearch(event.target.value)}
                placeholder="Search alert, asset, tag, node..."
            />
            <div className="toolbar-controls">
                <select value={type} onChange={(event) => setType(event.target.value)}>
                    <option value="all">All Types</option>
                    <option value="asset">Assets</option>
                    <option value="node">Nodes</option>
                    <option value="unknown_tag_detected">Unknown Tags</option>
                </select>
                <select value={severity} onChange={(event) => setSeverity(event.target.value)}>
                    <option value="all">All Severities</option>
                    <option value="critical">Critical</option>
                    <option value="warning">Warning</option>
                    <option value="info">Info</option>
                </select>
            </div>
        </div>
    );
}
