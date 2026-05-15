/**
 * @file ui_controls.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-13

 * @Copyright (c) 2026
 */

/**
 * @file ui_controls.js
 * @description UI control functions for the ESP32 setup portal.
 */

import { byId } from "./dom_utils.js";

export function togglePassword() {
    const p = byId("pass");
    const btn = byId("toggleBtn");

    if (!p || !btn || p.disabled) return;

    if (p.type === "password") {
        p.type = "text";
        btn.innerText = "Hide password";
        return;
    }

    p.type = "password";
    btn.innerText = "Show password";
}

export function toggleDeviceInfo() {
    const panel = document.getElementById("deviceInfoPanel");
    const btn = document.querySelector(".device-toggle-btn");

    if (!panel || !btn) return;

    panel.classList.toggle("hidden");

    const hidden = panel.classList.contains("hidden");
    localStorage.setItem("deviceInfoHidden", String(hidden));

    btn.innerText = hidden
        ? "Show Device Information"
        : "Hide Device Information";
}

export function toggleWifiPassword() {
    const openChk = byId("wifi_open");
    const pass = byId("pass");
    const btn = byId("toggleBtn");

    if (!openChk || !pass || !btn) return;

    if (openChk.checked) {
        pass.disabled = true;
        pass.value = "";
        pass.type = "password";
        btn.innerText = "Show password";
        btn.disabled = true;
        btn.style.opacity = "0.65";
        btn.style.cursor = "not-allowed";
        return;
    }

    pass.disabled = false;
    btn.disabled = false;
    btn.style.opacity = "1";
    btn.style.cursor = "pointer";
}

export function showConnecting() {
    const status = document.getElementById("statusMessage");

    if (status) {
        status.innerText = "Connecting to Wi-Fi...";
    }
}