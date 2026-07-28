/**
 * @file MovementRequestToolbar.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { getNodeLabel, isOnlineRegistrationNode } from "../../../hooks/assets/movement/movementRequestHelpers";

export default function MovementRequestToolbar({
    loading,
    registrationNodes,
    registrationNodeId,
    setRegistrationNodeId,
    selectedRegistrationNodeIsOnline,
}) {
    return (
        <div className="movement-request-toolbar">
            <label className="compact-node-picker">
                <span>Registration Node</span>
                <select
                    value={registrationNodeId}
                    onChange={(event) => setRegistrationNodeId?.(event.target.value)}
                    disabled={loading}
                >
                    <option value="">Select registration node</option>
                    {registrationNodes.map((node) => {
                        const nodeOnline = isOnlineRegistrationNode(node);
                        return (
                            <option key={node.device_id} value={node.device_id} disabled={!nodeOnline}>
                                {getNodeLabel(node)}
                                {!nodeOnline ? ` (${node.status || "OFFLINE"} - unavailable)` : ""}
                            </option>
                        );
                    })}
                </select>
            </label>

            {registrationNodeId && selectedRegistrationNodeIsOnline && (
                <div className="selected-node-note">Approval node selected</div>
            )}
            {registrationNodeId && !selectedRegistrationNodeIsOnline && (
                <div className="selected-node-note warning">Selected node is offline</div>
            )}
        </div>
    );
}
