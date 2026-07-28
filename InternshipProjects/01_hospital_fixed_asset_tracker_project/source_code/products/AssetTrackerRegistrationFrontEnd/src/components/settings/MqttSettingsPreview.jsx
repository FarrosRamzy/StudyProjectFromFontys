/**
 * @file MqttSettingsPreview.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


export default function MqttSettingsPreview({ preview }) {
    return (
        <div className="settings-preview-card">
            <h3>Generated MQTT Identity</h3>

            <dl>
                <PreviewRow label="Hospital ID" value={preview.hospitalId} />
                <PreviewRow
                    label="MQTT Topic Namespace"
                    value={preview.topicNamespace}
                />
                <PreviewRow label="Backend Client ID" value={preview.clientId} />
            </dl>

            <p>
                The system generates these values from the hospital name.
                The namespace must stay unique for each hospital.
            </p>
        </div>
    );
}

function PreviewRow({ label, value }) {
    return (
        <div>
            <dt>{label}</dt>
            <dd>{value}</dd>
        </div>
    );
}
