/**
 * @file app_init.js
 * @author Farros Ramzy (you@domain.com)
 * @description Page startup logic.
 * @version 1.0.0
 * @date 2026-05-13

 * @Copyright (c) 2026
 */

import { toggleWifiPassword } from "./ui_controls.js";
import { showNotificationFromQuery } from "./wifi_form.js";

export function initializeApp() {
    toggleWifiPassword();
    showNotificationFromQuery();

    const hidden = localStorage.getItem("deviceInfoHidden") === "true";
    const panel = document.getElementById("deviceInfoPanel");
    const btn = document.querySelector(".device-toggle-btn");

    if (hidden && panel) {
        panel.classList.add("hidden");
    }

    if (btn) {
        btn.innerText = hidden
            ? "Show Device Information"
            : "Hide Device Information";
    }
}
