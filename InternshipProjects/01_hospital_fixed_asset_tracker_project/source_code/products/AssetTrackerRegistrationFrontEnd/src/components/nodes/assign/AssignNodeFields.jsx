/**
 * @file AssignNodeFields.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-19

 * @Copyright (c) 2026
 */


import { NODE_ROLES } from "../../../utils/nodeHelpers";
import { getHospitalNameFromSettings } from "../../../utils/settings/mqttSettingsFormatters";

export default function AssignNodeFields({
    alias,
    setAlias,
    role,
    setRole,
    roomName,
    setRoomName,
    mqttSettings,
    mqttSettingsLoading,
}) {
    const isCheckpointRole = role === NODE_ROLES.CHECKPOINT;
    const roomNameDisplayValue = isCheckpointRole
        ? roomName
        : "Not required for registration desk";

    return (
        <>
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
                <select value={role} onChange={(event) => setRole(event.target.value)}>
                    <option value={NODE_ROLES.CHECKPOINT}>Checkpoint Node</option>
                    <option value={NODE_ROLES.REGISTRATION}>Registration Desk</option>
                </select>
            </label>

            <MqttAssignmentSummary
                settings={mqttSettings}
                loading={mqttSettingsLoading}
            />

            <label>
                Room Name {isCheckpointRole && <span className="required-mark">*</span>}
                <input
                    type="text"
                    value={roomNameDisplayValue}
                    onChange={(event) => isCheckpointRole && setRoomName(event.target.value)}
                    placeholder={isCheckpointRole ? "Example: ICU Room 2" : "Not required"}
                    disabled={!isCheckpointRole}
                    required={isCheckpointRole}
                />
            </label>
        </>
    );
}

function MqttAssignmentSummary({ settings, loading }) {
    if (loading) {
        return <p className="assignment-readonly-note">Loading MQTT settings...</p>;
    }

    return (
        <>
            <div className="assignment-readonly-grid">
                <ReadOnlyItem label="Hospital" value={getHospitalNameFromSettings(settings)} />
                <ReadOnlyItem label="Hospital ID" value={settings?.hospital_id} />
                <ReadOnlyItem label="MQTT Broker" value={settings?.broker_host} />
                <ReadOnlyItem label="MQTT Port" value={settings?.broker_port} />
                <ReadOnlyItem label="Namespace" value={settings?.topic_namespace} />
            </div>
            <p className="assignment-readonly-note">
                Hospital and MQTT settings are managed in System Settings.
            </p>
        </>
    );
}

function ReadOnlyItem({ label, value }) {
    return (
        <div className="assignment-readonly-item">
            <span>{label}</span>
            <strong>{value || "-"}</strong>
        </div>
    );
}
