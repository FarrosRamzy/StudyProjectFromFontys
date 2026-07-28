/**
 * @file AssetRegisterForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */

import { getNodeLabel } from "../../utils/nodeHelpers";

export default function AssetRegisterForm({
    registrationNodes,
    selectedNodeId,
    setSelectedNodeId,
    tagId,
    // setTagId,
    assetName,
    setAssetName,
    latestScan,
    saving,
    onSubmit,
}) {
    const latestScanNode = latestScan
        ? registrationNodes.find((node) => node.device_id === latestScan.device_id)
        : null;

    const latestScanNodeLabel = latestScanNode
        ? getNodeLabel(latestScanNode)
        : latestScan?.device_id || "-";

    return (
        <div>
            <form className="asset-form" onSubmit={onSubmit}>
                <div className="section-header">
                    <h2>Register New Asset</h2>
                    <p>
                        Select a registration node, scan a tag, then enter the asset name.
                    </p>
                </div>

                {latestScan && (
                    <div
                        className="scan-card"
                        key={`${latestScan.tag_id}-${latestScan.received_at || latestScan.timestamp}`}
                    >
                        <strong>Latest scanned tag</strong>
                        <span>{latestScan.tag_id}</span>
                        <small>
                            Node: {latestScanNodeLabel} · {latestScan.timestamp || "-"}
                        </small>
                    </div>
                )}

                <div className="form-grid">
                    <label className="form-field">
                        <span>Registration Node</span>
                        <select
                            value={selectedNodeId}
                            onChange={(event) => setSelectedNodeId(event.target.value)}
                            disabled={saving}
                        >
                            <option value="">Select registration node</option>

                            {registrationNodes.map((node) => (
                                <option key={node.device_id} value={node.device_id}>
                                    {getNodeLabel(node)}
                                </option>
                            ))}
                        </select>
                    </label>

                    <div className="form-field">
                        <span>Tag ID</span>

                        <div className={`tag-id-card ${tagId ? "has-tag" : "empty-tag"}`}>
                            <div className="tag-id-card-header">
                                <strong>
                                    {tagId ? "RFID Tag Detected" : "No Tag Detected"}
                                </strong>
                                <small>
                                    {tagId
                                        ? "Ready to register"
                                        : "Scan a tag at the selected node"}
                                </small>
                            </div>

                            <div className="tag-id-value">
                                {tagId || "Waiting for RFID scan ..."}
                            </div>
                        </div>
                    </div>

                    <label className="form-field">
                        <span>Asset Name</span>
                        <input
                            value={assetName}
                            onChange={(event) => setAssetName(event.target.value)}
                            placeholder="Example: Wheelchair ICU 02"
                            disabled={saving}
                        />
                    </label>
                </div>

                <div className="form-actions">
                    <button
                        type="submit"
                        className="primary-button"
                        disabled={saving || !selectedNodeId || !tagId || !assetName.trim()}
                    >
                        {saving ? "Registering..." : "Register Asset"}
                    </button>
                </div>
            </form>
        </div>
    );
}