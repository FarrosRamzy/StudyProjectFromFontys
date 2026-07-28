/**
 * @file script.js
 * @author Farros Ramzy (you@domain.com)
 * @description Main JavaScript module entry point for ESP32 setup portal.
 * @version 1.5.0
 * @date 2026-04-29

 * @Copyright (c) 2026
 */

import { initializeApp } from "./js/app_init.js";

import {
    togglePassword,
    toggleDeviceInfo,
    toggleWifiPassword,
    showConnecting
} from "./js/ui_controls.js";

import {
    submitWiFiForm,
    validateForm,
    refreshNetworks,
    showNotificationFromQuery
} from "./js/wifi_form.js";

window.togglePassword = togglePassword;
window.toggleDeviceInfo = toggleDeviceInfo;
window.toggleWifiPassword = toggleWifiPassword;
window.showConnecting = showConnecting;

window.submitWiFiForm = submitWiFiForm;
window.validateForm = validateForm;
window.refreshNetworks = refreshNetworks;
window.showNotificationFromQuery = showNotificationFromQuery;

initializeApp();
