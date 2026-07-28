/**
 * @file useMqttSettingsForm.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useEffect, useMemo, useState } from "react";

import {
    buildMqttClientId,
    buildMqttSettingsPayload,
    buildMqttTopicNamespace,
    getHospitalNameFromSettings,
    hospitalNameToSlug,
} from "../../utils/settings/mqttSettingsFormatters";
import {
    getMqttSettings,
    reconnectMqtt,
    resetMqttSettings,
    updateMqttSettings,
} from "../../services/settingsApi";

const DEFAULT_FORM = {
    hospitalName: "",
    brokerHost: "",
    brokerPort: 1883,
    tlsEnabled: false,
    username: "",
    password: "",
    enabled: true,
};

export function useMqttSettingsForm() {
    const [form, setForm] = useState(DEFAULT_FORM);
    const [loading, setLoading] = useState(true);
    const [saving, setSaving] = useState(false);
    const [message, setMessage] = useState("");
    const [error, setError] = useState("");

    const preview = useMemo(() => {
        const hasName = Boolean(String(form.hospitalName || "").trim());

        return {
            hospitalId: hasName ? hospitalNameToSlug(form.hospitalName) : "-",
            topicNamespace: hasName
                ? buildMqttTopicNamespace(form.hospitalName)
                : "-",
            clientId: hasName ? buildMqttClientId(form.hospitalName) : "-",
        };
    }, [form.hospitalName]);

    function updateField(field, value) {
        setForm((current) => ({ ...current, [field]: value }));
    }

    async function loadSettings() {
        setLoading(true);
        setError("");

        try {
            const settings = await getMqttSettings();
            setForm(mapSettingsToForm(settings));
        } catch (err) {
            setError(err.message || "Failed to load MQTT settings.");
        } finally {
            setLoading(false);
        }
    }

    async function saveSettings(event) {
        event.preventDefault();
        await runAction(async () => {
            const result = await updateMqttSettings(buildMqttSettingsPayload(form));
            setMessage(result?.message || "MQTT settings saved.");
        });
    }

    async function reconnect() {
        await runAction(async () => {
            const result = await reconnectMqtt();
            setMessage(result?.message || "MQTT reconnect requested.");
        });
    }

    async function resetToDefault() {
        if (!window.confirm("Reset MQTT settings to backend defaults?")) {
            return;
        }

        await runAction(async () => {
            const result = await resetMqttSettings();
            setForm(mapSettingsToForm(result?.settings || {}));
            setMessage(result?.message || "MQTT settings reset to default.");
        });
    }

    async function runAction(action) {
        setSaving(true);
        setError("");
        setMessage("");

        try {
            await action();
        } catch (err) {
            setError(err.message || "MQTT settings action failed.");
        } finally {
            setSaving(false);
        }
    }

    useEffect(() => {
        loadSettings();
    }, []);

    return {
        form, preview, loading, saving, message, error,
        updateField, saveSettings, reconnect, resetToDefault,
        reloadSettings: loadSettings,
    };
}

function mapSettingsToForm(settings) {
    return {
        hospitalName: getHospitalNameFromSettings(settings),
        brokerHost: settings?.broker_host || "",
        brokerPort: settings?.broker_port || 1883,
        tlsEnabled: Boolean(settings?.tls_enabled),
        username: settings?.username || "",
        password: "",
        enabled: settings?.enabled !== false,
    };
}
