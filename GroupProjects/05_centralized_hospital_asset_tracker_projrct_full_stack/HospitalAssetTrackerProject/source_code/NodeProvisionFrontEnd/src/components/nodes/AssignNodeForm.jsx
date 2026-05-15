/**
 * @file AssignNodeForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description Form for assigning, editing, unassigning, or deleting a node.
 * @version 1.5.0
 * @date 2026-04-30

 * @Copyright (c) 2026
 */

import {
    NODE_ROLES,
    canDeleteNode,
    canEditNode,
    canUnassignNode,
} from "../../utils/nodeHelpers";

import {
    formatNodeId,
    formatNodeStatus,
} from "../../utils/nodeFormatters";

export default function AssignNodeForm({
    selectedNode,
    alias, setAlias,
    role, setRole,
    hospitalName, setHospitalName,
    roomName, setRoomName,
    mqttHost, setMqttHost,
    mqttPort, setMqttPort,
    assigning, unassigning, deleting,
    onAssignSubmit, onUnassign, onDelete, onCancel,
}) {
    const isCheckpointRole = role === NODE_ROLES.CHECKPOINT;
    const hasSelectedNode = Boolean(selectedNode?.device_id);

    const isEditMode = hasSelectedNode && canEditNode(selectedNode);
    const showUnassign = hasSelectedNode && canUnassignNode(selectedNode);
    const showDelete = hasSelectedNode && canDeleteNode(selectedNode);

    return (
        <section className="panel assignment-panel narrow-panel">
            <div className="section-header">
                <div>
                    <h2>{isEditMode ? "Edit Node" : "Assign Node"}</h2>
                    <p>
                        Select a discovered node, assign its role, and bind it
                        to a hospital location.
                    </p>
                </div>
            </div>

            {!hasSelectedNode ? (
                <div className="empty-state">
                    <h2>No node selected</h2>
                    <p>
                        Choose a node from the table below before assigning or
                        editing it.
                    </p>
                </div>
            ) : (
                <div className="tag-card">
                    <span className="tag-card-label">Selected Node</span>
                    <strong>{formatNodeId(selectedNode)}</strong>
                    <small>Status: {formatNodeStatus(selectedNode.status)}</small>
                </div>
            )}

            <form className="asset-form" onSubmit={onAssignSubmit}>
                <label>
                    Node Alias
                    <input
                        type="text"
                        value={alias}
                        onChange={(event) => setAlias(event.target.value)}
                        placeholder="Example: ICU Room 2 Reader"
                    />
                </label>

                <label>
                    Node Role
                    <select
                        value={role}
                        onChange={(event) => setRole(event.target.value)}
                    >
                        <option value={NODE_ROLES.CHECKPOINT}>
                            Checkpoint Node
                        </option>
                        <option value={NODE_ROLES.REGISTRATION}>
                            Registration Desk
                        </option>
                    </select>
                </label>

                <label>
                    Hospital Name <span className="required-mark">*</span>
                    <input
                        type="text"
                        value={hospitalName}
                        onChange={(event) => setHospitalName(event.target.value)}
                        placeholder="Example: Central Hospital"
                        required
                    />
                </label>

                <label>
                    Room Name {isCheckpointRole && <span className="required-mark">*</span>}
                    <input
                        type="text"
                        value={roomName}
                        onChange={(event) => setRoomName(event.target.value)}
                        placeholder={
                            isCheckpointRole
                                ? "Example: ICU Room 2"
                                : "Not required for registration desk"
                        }
                        disabled={!isCheckpointRole}
                        required={isCheckpointRole}
                    />
                </label>

                <label>
                    MQTT Host <span className="required-mark">*</span>
                    <input
                        type="text"
                        value={mqttHost}
                        onChange={(event) => setMqttHost(event.target.value)}
                        placeholder="Example: broker.hospital.local"
                        required
                    />
                </label>

                <label>
                    MQTT Port <span className="required-mark">*</span>
                    <input
                        type="number"
                        min="1"
                        max="65535"
                        step="1"
                        value={mqttPort}
                        onChange={(event) => setMqttPort(event.target.value)}
                        placeholder="1883"
                        required
                    />
                </label>

                <div className="form-actions">
                    <button
                        type="submit"
                        className="primary-button"
                        disabled={!hasSelectedNode || assigning}
                    >
                        {assigning
                            ? "Saving..."
                            : isEditMode
                                ? "Save Changes"
                                : "Assign Node"}
                    </button>

                    {showUnassign && (
                        <button
                            type="button"
                            className="danger-button"
                            disabled={unassigning}
                            onClick={onUnassign}
                        >
                            {unassigning ? "Unassigning..." : "Unassign"}
                        </button>
                    )}

                    {showDelete && (
                        <button
                            type="button"
                            className="danger-button"
                            disabled={deleting}
                            onClick={onDelete}
                        >
                            {deleting ? "Deleting..." : "Delete"}
                        </button>
                    )}

                    <button
                        type="button"
                        className="ghost-button"
                        onClick={onCancel}
                    >
                        Cancel
                    </button>
                </div>
            </form>
        </section>
    );
}