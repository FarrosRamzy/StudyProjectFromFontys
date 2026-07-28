/**
 * @file AssetRegisterForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */


import { isNodeOnline } from "../../utils/nodeHelpers";
import {
    InitialPlacementSelect,
    LatestScanCard,
    RegistrationNodeSelect,
    TagIdCard,
} from "./AssetRegisterFields";

export default function AssetRegisterForm({
    registrationNodes,
    checkpointNodes = [],
    selectedNodeId,
    setSelectedNodeId,
    initialNodeId,
    setInitialNodeId,
    tagId,
    assetName,
    setAssetName,
    latestScan,
    saving,
    onSubmit,
}) {
    const latestScanNode = latestScan
        ? registrationNodes.find((node) => node.device_id === latestScan.device_id)
        : null;
    const selectedRegistrationNode = registrationNodes.find(
        (node) => node.device_id === selectedNodeId
    );
    const selectedRegistrationNodeIsOnline = selectedRegistrationNode
        ? isNodeOnline(selectedRegistrationNode)
        : false;

    return (
        <div>
            <form className="asset-form" onSubmit={onSubmit}>
                <div className="section-header">
                    <h2>Register New Asset</h2>
                    <p>Select a registration node, scan a tag, enter the asset name, then choose the first placement room.</p>
                </div>

                {latestScan && <LatestScanCard latestScan={latestScan} latestScanNode={latestScanNode} />}

                <div className="form-grid">
                    <RegistrationNodeSelect
                        registrationNodes={registrationNodes}
                        selectedNodeId={selectedNodeId}
                        setSelectedNodeId={setSelectedNodeId}
                        saving={saving}
                        selectedRegistrationNodeIsOnline={selectedRegistrationNodeIsOnline}
                    />
                    <TagIdCard tagId={tagId} />
                    <label className="form-field">
                        <span>Asset Name</span>
                        <input
                            value={assetName}
                            onChange={(event) => setAssetName(event.target.value)}
                            placeholder="Example: Wheelchair ICU 02"
                            disabled={saving}
                        />
                    </label>
                    <InitialPlacementSelect
                        checkpointNodes={checkpointNodes}
                        initialNodeId={initialNodeId}
                        setInitialNodeId={setInitialNodeId}
                        saving={saving}
                    />
                </div>

                <div className="form-actions">
                    <button
                        type="submit"
                        className="primary-button"
                        disabled={
                            saving ||
                            !selectedNodeId ||
                            !selectedRegistrationNodeIsOnline ||
                            !tagId ||
                            !assetName.trim() ||
                            !initialNodeId
                        }
                    >
                        {saving ? "Registering..." : "Register Asset"}
                    </button>
                </div>
            </form>
        </div>
    );
}
