/**
 * @file script.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.5.0
 * @date 2026-04-29

 * @Copyright (c) 2026
 */

/**
 * @file script.js
 * @description Main JavaScript module entry point for ESP32 setup portal.
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

// function byId(id) { return document.getElementById(id); }

// function togglePassword() {
//     const p = byId('pass');
//     const btn = byId('toggleBtn');
//     if (!p || !btn || p.disabled) return;

//     if (p.type === 'password') {
//         p.type = 'text';
//         btn.innerText = 'Hide password';
//         return;
//     }

//     p.type = 'password';
//     btn.innerText = 'Show password';
// }

// function toggleDeviceInfo() {
//     const panel = document.getElementById("deviceInfoPanel");
//     const btn = document.querySelector(".device-toggle-btn");

//     if (!panel || !btn) return;

//     panel.classList.toggle("hidden");

//     const hidden = panel.classList.contains("hidden");
//     localStorage.setItem("deviceInfoHidden", String(hidden));

//     btn.innerText = hidden
//         ? "Show Device Information"
//         : "Hide Device Information";
// }

// function toggleWifiPassword() {
//     const openChk = byId('wifi_open');
//     const pass = byId('pass');
//     const btn = byId('toggleBtn');
//     if (!openChk || !pass || !btn) return;

//     if (openChk.checked) {
//         pass.disabled = true;
//         pass.value = '';
//         pass.type = 'password';
//         btn.innerText = 'Show password';
//         btn.disabled = true;
//         btn.style.opacity = '0.65';
//         btn.style.cursor = 'not-allowed';
//         return;
//     }
//     pass.disabled = false;
//     btn.disabled = false;
//     btn.style.opacity = '1';
//     btn.style.cursor = 'pointer';
// }

// function showConnecting() {
//     var status = document.getElementById("statusMessage");
//     if (status) {
//         status.innerText = "Connecting to Wi-Fi..."
//     }
// }

// async function submitWiFiForm(event) {
//     event.preventDefault();

//     if (!validateForm()) {
//         return false;
//     }

//     var form = byId("wifiForm");
//     var formData = new FormData(form);
//     var status = byId("statusMessage");

//     if (status) {
//         status.innerText = "Saving configuration and connecting to Wi-Fi...";
//     }

//     try {
//         var response = await fetch("/save", {
//             method: "POST",
//             body: formData
//         });

//         var text = await response.text();

//         if (status) {
//             status.innerText = "Configuration saved. Device may reboot now.";
//         }

//         console.log(text);
//     } catch (error) {
//         if (status) {
//             status.innerText = "Failed to save configuration. Please try again.";
//         }
//     }

//     return false;

// }

// function validateForm() {
//     var ssid = byId('ssid_input');
//     var openChk = byId('wifi_open');
//     var pass = byId('pass');

//     var ssidValue = ssid ? ssid.value.trim() : '';

//     if (!ssidValue) {
//         alert('Please select a Wi‑Fi network or type the SSID manually.');
//         return false;
//     }

//     if (ssid && ssidValue !== ssid.value) {
//         ssid.value = ssidValue;
//     }

//     if (openChk && !openChk.checked && pass && pass.value.length > 0 && pass.value.length < 8) {
//         var proceed = confirm('The password is shorter than 8 characters. Continue anyway?');
//         if (!proceed) return false;
//     }

//     return true;
// }

// function getQueryParam(name) {
//     var params = new URLSearchParams(window.location.search);
//     return params.get(name);
// }

// async function refreshNetworks() {
//     var list = byId("ssid_list");
//     var status = byId("statusMessage");

//     if (!list) return;

//     if (status) {
//         status.innerText = "Refreshing Wi-Fi list...";
//     }

//     try {
//         const response = await fetch("/refresh", { cache: "no-store" });

//         if (!response.ok) {
//             throw new Error("Refresh failed");
//         }
//         const optionsHtml = await response.text();
//         list.innerHTML = optionsHtml;

//         if (status) {
//             status.innerText = "Wi-Fi list refreshed.";
//         }
//     } catch (error) {
//         if (status) {
//             status.innerText = "Failed to refresh Wi-Fi list.";
//         }
//     }
// }

// function showNotificationFromQuery() {
//     var msg = getQueryParam("msg");
//     var type = getQueryParam("type");

//     if (!msg) return;

//     var decoded = decodeURIComponent(msg);
//     var status = byId("statusMessage");
//     var box = byId("statusBox");

//     if (status) {
//         status.innerText = decoded;
//     }

//     if (box && type === "error") {
//         box.style.borderColor = "#dc2626";
//         box.style.background = "#fef2f2";
//     }

//     alert(decoded);

//     refreshNetworks();

//     var cleanUrl = window.location.origin + window.location.pathname;
//     window.history.replaceState({}, document.title, cleanUrl);
// }

// window.onload = function () {
//     toggleWifiPassword();
//     showNotificationFromQuery();

//     const hidden = localStorage.getItem("deviceInfoHidden") === "true";
//     const panel = document.getElementById("deviceInfoPanel");

//     const btn = document.querySelector(".device-toggle-btn");

//     if (hidden && panel) {
//         panel.classList.add("hidden");
//     }

//     if (btn) {
//         btn.innerText = hidden
//             ? "Show Device Information"
//             : "Hide Device Information";
//     }
// };