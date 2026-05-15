/**
 * @file wifi_form.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-13

 * @Copyright (c) 2026
 */

/**
 * @file wifi_form.js
 * @description Wi-Fi setup form behavior.
 */

import { byId, getQueryParam } from "./dom_utils.js";

export async function submitWiFiForm(event) {
    event.preventDefault();

    if (!validateForm()) {
        return false;
    }

    const form = byId("wifiForm");
    const formData = new FormData(form);
    const status = byId("statusMessage");

    if (status) {
        status.innerText = "Saving configuration and connecting to Wi-Fi...";
    }

    try {
        const response = await fetch("/save", {
            method: "POST",
            body: formData
        });

        const text = await response.text();

        if (status) {
            status.innerText = "Configuration saved. Device may reboot now.";
        }

        console.log(text);
    } catch (error) {
        if (status) {
            status.innerText = "Failed to save configuration. Please try again.";
        }

        console.error(error);
    }

    return false;
}

export function validateForm() {
    const ssid = byId("ssid_input");
    const openChk = byId("wifi_open");
    const pass = byId("pass");

    const ssidValue = ssid ? ssid.value.trim() : "";

    if (!ssidValue) {
        alert("Please select a Wi-Fi network or type the SSID manually.");
        return false;
    }

    if (ssid && ssidValue !== ssid.value) {
        ssid.value = ssidValue;
    }

    if (
        openChk &&
        !openChk.checked &&
        pass &&
        pass.value.length > 0 &&
        pass.value.length < 8
    ) {
        const proceed = confirm(
            "The password is shorter than 8 characters. Continue anyway?"
        );

        if (!proceed) return false;
    }

    return true;
}

export async function refreshNetworks() {
    const list = byId("ssid_list");
    const status = byId("statusMessage");

    if (!list) return;

    if (status) {
        status.innerText = "Refreshing Wi-Fi list...";
    }

    try {
        const response = await fetch("/refresh", {
            cache: "no-store"
        });

        if (!response.ok) {
            throw new Error("Refresh failed");
        }

        const optionsHtml = await response.text();
        list.innerHTML = optionsHtml;

        if (status) {
            status.innerText = "Wi-Fi list refreshed.";
        }
    } catch (error) {
        if (status) {
            status.innerText = "Failed to refresh Wi-Fi list.";
        }

        console.error(error);
    }
}

export function showNotificationFromQuery() {
    const msg = getQueryParam("msg");
    const type = getQueryParam("type");

    if (!msg) return;

    const decoded = decodeURIComponent(msg);
    const status = byId("statusMessage");
    const box = byId("statusBox");

    if (status) {
        status.innerText = decoded;
    }

    if (box && type === "error") {
        box.style.borderColor = "#dc2626";
        box.style.background = "#fef2f2";
    }

    alert(decoded);

    refreshNetworks();

    const cleanUrl = window.location.origin + window.location.pathname;
    window.history.replaceState({}, document.title, cleanUrl);
}