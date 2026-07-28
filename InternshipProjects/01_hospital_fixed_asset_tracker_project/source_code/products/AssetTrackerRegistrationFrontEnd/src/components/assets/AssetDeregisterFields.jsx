/**
 * @file AssetDeregisterFields.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { getNodeLabel, isNodeOnline } from "../../utils/nodeHelpers";

export function DeregisterTagCard({
    effectiveTagId,
    selectedAsset,
    scannedTagId,
    deregisterTagId,
    saving,
    handleUseScannedTag,
    handleClearTag,
}) {
    return (
        <div className="form-field">
            <span>Asset Tag</span>
            <div className={`tag-id-card deregister-tag-card ${effectiveTagId ? "has-tag" : "empty-tag"}`}>
                <div className="tag-id-card-header">
                    <strong>{effectiveTagId ? "Asset Tag Selected" : "No Asset Tag Selected"}</strong>
                    <small>{effectiveTagId ? "Ready to deregister" : "Scan a tag or click Deregister from the table"}</small>
                </div>
                <div className="tag-id-value tag-id-value-with-name">
                    <span>{effectiveTagId || "Waiting for tag ..."}</span>
                    {effectiveTagId && <strong>{selectedAsset?.item_name || "unknown asset"}</strong>}
                </div>
            </div>

            {scannedTagId && scannedTagId !== deregisterTagId && (
                <button type="button" className="small-button" onClick={handleUseScannedTag} disabled={saving}>
                    Use latest scanned tag
                </button>
            )}
            {effectiveTagId && (
                <button type="button" className="small-button" onClick={handleClearTag} disabled={saving}>
                    Clear selected tag
                </button>
            )}
        </div>
    );
}

export function DeregisterNodeSelect({
    registrationNodes,
    deregisterNodeId,
    setDeregisterNodeId,
    saving,
    selectedDeregisterNodeIsOnline,
}) {
    return (
        <label className="form-field">
            <span>Registration Node</span>
            <select value={deregisterNodeId} onChange={(event) => setDeregisterNodeId(event.target.value)} disabled={saving}>
                <option value="">Select registration node</option>
                {registrationNodes.map((node) => {
                    const nodeOnline = isNodeOnline(node);
                    return (
                        <option key={node.device_id} value={node.device_id} disabled={!nodeOnline}>
                            {getNodeLabel(node)}
                            {!nodeOnline ? ` (${node.status || "OFFLINE"} - unavailable)` : ""}
                        </option>
                    );
                })}
            </select>
            {deregisterNodeId && !selectedDeregisterNodeIsOnline && (
                <small className="form-warning-text">This registration node is offline. Choose an online registration node.</small>
            )}
        </label>
    );
}

export function DeregisterReasonField({ deregisterReason, setDeregisterReason, saving }) {
    return (
        <label className="form-field">
            <span>Reason<strong className="required-marker">*</strong></span>
            <input
                value={deregisterReason}
                onChange={(event) => setDeregisterReason(event.target.value)}
                placeholder="Required: Asset retired, damaged, transferred, or removed"
                disabled={saving}
            />
        </label>
    );
}
