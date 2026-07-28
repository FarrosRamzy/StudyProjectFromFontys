/**
 * @file MqttSettingsForm.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import MqttSettingsPreview from "./MqttSettingsPreview";

export default function MqttSettingsForm({
    form, preview, saving, onFieldChange, onSubmit, onReconnect, onReset,
}) {
    return (
        <form className="settings-form" onSubmit={onSubmit}>
            <TextInput
                label="Hospital Name"
                value={form.hospitalName}
                onChange={(value) => onFieldChange("hospitalName", value)}
                placeholder="Example: Imperial Hospital"
                required
            />

            <MqttSettingsPreview preview={preview} />

            <TextInput
                label="MQTT Broker Link"
                value={form.brokerHost}
                onChange={(value) => onFieldChange("brokerHost", value)}
                placeholder="Example: broker.hivemq.com"
                required
            />

            <label>
                MQTT Port <span className="required-mark">*</span>
                <input
                    type="number" min="1" max="65535" value={form.brokerPort}
                    onChange={(event) => onFieldChange("brokerPort", event.target.value)}
                    required
                />
            </label>

            <label className="settings-checkbox-row">
                <input
                    type="checkbox" checked={form.tlsEnabled}
                    onChange={(event) => onFieldChange("tlsEnabled", event.target.checked)}
                />
                Use TLS
            </label>

            <div className="settings-actions">
                <button type="submit" className="primary-button" disabled={saving}>
                    {saving ? "Saving..." : "Save MQTT Settings"}
                </button>
                <button type="button" className="ghost-button" onClick={onReconnect} disabled={saving}>
                    Reconnect MQTT
                </button>
                <button type="button" className="ghost-button danger" onClick={onReset} disabled={saving}>
                    Reset to Default
                </button>
            </div>
        </form>
    );
}

function TextInput({ label, value, onChange, placeholder, required }) {
    return (
        <label>
            {label} {required && <span className="required-mark">*</span>}
            <input
                type="text" value={value}
                onChange={(event) => onChange(event.target.value)}
                placeholder={placeholder}
                required={required}
            />
        </label>
    );
}
