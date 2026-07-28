/**
 * @file useMqttSettings.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import { useCallback, useEffect, useState } from "react";

import { getMqttSettings } from "../../services/settingsApi";

export function useMqttSettings() {
    const [settings, setSettings] = useState(null);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState("");

    const loadSettings = useCallback(async () => {
        setError("");

        try {
            const result = await getMqttSettings();
            setSettings(result);
        } catch (err) {
            setError(err.message || "Failed to load MQTT settings.");
        } finally {
            setLoading(false);
        }
    }, []);

    useEffect(() => {
        loadSettings();
    }, [loadSettings]);

    return {
        settings,
        loading,
        error,
        reloadSettings: loadSettings,
    };
}
