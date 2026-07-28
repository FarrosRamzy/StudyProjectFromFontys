/**
 * @file AssetRegisterFields.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { getNodeLabel, isNodeOnline } from "../../utils/nodeHelpers";

export function LatestScanCard({ latestScan, latestScanNode }) {
    const label = latestScanNode ? getNodeLabel(latestScanNode) : latestScan?.device_id || "-";

    return (
        <div className="scan-card" key={`${latestScan.tag_id}-${latestScan.received_at || latestScan.timestamp}`}>
            <strong>Latest scanned tag</strong>
            <span>{latestScan.tag_id}</span>
            <small>Node: {label} · {latestScan.timestamp || "-"}</small>
        </div>
    );
}

export function RegistrationNodeSelect({
    registrationNodes,
    selectedNodeId,
    setSelectedNodeId,
    saving,
    selectedRegistrationNodeIsOnline,
}) {
    return (
        <label className="form-field">
            <span>Registration Node</span>
            <select value={selectedNodeId} onChange={(event) => setSelectedNodeId(event.target.value)} disabled={saving}>
                <option value="">Select registration node</option>
                {registrationNodes.map((node) => <RegistrationNodeOption key={node.device_id} node={node} />)}
            </select>
            {selectedNodeId && !selectedRegistrationNodeIsOnline && (
                <small className="form-warning-text">This registration node is offline. Choose an online registration node.</small>
            )}
        </label>
    );
}

function RegistrationNodeOption({ node }) {
    const nodeOnline = isNodeOnline(node);

    return (
        <option value={node.device_id} disabled={!nodeOnline}>
            {getNodeLabel(node)}
            {!nodeOnline ? ` (${node.status || "OFFLINE"} - unavailable)` : ""}
        </option>
    );
}

export function TagIdCard({ tagId }) {
    return (
        <div className="form-field">
            <span>Tag ID</span>
            <div className={`tag-id-card ${tagId ? "has-tag" : "empty-tag"}`}>
                <div className="tag-id-card-header">
                    <strong>{tagId ? "RFID Tag Detected" : "No Tag Detected"}</strong>
                    <small>{tagId ? "Ready to register" : "Scan a tag at the selected node"}</small>
                </div>
                <div className="tag-id-value">{tagId || "Waiting for RFID scan ..."}</div>
            </div>
        </div>
    );
}

export function InitialPlacementSelect({ checkpointNodes, initialNodeId, setInitialNodeId, saving }) {
    return (
        <label className="form-field">
            <span>Initial Placement Room</span>
            <select value={initialNodeId} onChange={(event) => setInitialNodeId(event.target.value)} disabled={saving}>
                <option value="">Select destination checkpoint</option>
                {checkpointNodes.map((node) => (
                    <option key={node.device_id} value={node.device_id}>
                        {getNodeLabel(node)} {node.status && node.status !== "ONLINE" ? `(${node.status})` : ""}
                    </option>
                ))}
            </select>
            <small className="form-help-text">The asset will stay red until this checkpoint node detects it.</small>
        </label>
    );
}
