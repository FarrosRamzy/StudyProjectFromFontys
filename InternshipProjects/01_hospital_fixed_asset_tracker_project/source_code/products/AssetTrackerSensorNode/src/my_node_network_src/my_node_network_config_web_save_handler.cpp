/**
 * @file my_node_network_config_web_save_handler.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::handleSave()
{
    // NOTE - read one of the options.
    String my_ssid = my_web_server.hasArg("ssid") ? my_web_server.arg("ssid") : "";

    if (my_ssid.length() == 0)
    {
        my_web_server.send(400, "text/plain", "SSID is required.");
        return;
    }

    my_ssid.trim();

    bool wifi_open = my_web_server.hasArg("wifi_open");
    String new_password = my_web_server.hasArg("pass") ? my_web_server.arg("pass") : "";
    new_password.trim();

    my_bootstrap_config.wifi_ssid = my_ssid;

    if (wifi_open)
    {
        my_bootstrap_config.wifi_password = "";
    }
    else if (new_password.length() > 0)
    {
        my_bootstrap_config.wifi_password = new_password;
    }
    else
    {
        // keep existing saved password;
    }

    String status_message;
    bool ok = testWiFiConnection(my_bootstrap_config.wifi_ssid, my_bootstrap_config.wifi_password,
                                 wifi_open, MY_NODE_NETWORK_TIMER_MS, status_message);

    if (!ok)
    {
        String location = "/?msg=" + makeUrlSafe(status_message) + "&type=error";
        my_web_server.sendHeader("Location", location, true);
        my_web_server.send(302, "text/plain", "");
        return;
    }

    my_bootstrap_config.is_configured = true;

    saveConfig();

    String html = readFile(MY_BOOTSTRAP_RESULT_FILE);

    if (html.length() == 0)
    {
        my_web_server.send(500, "text/plain", "Failed to load esp_boot_result.html");
        return;
    }

    html.replace("{{status_message}}", "Wi-Fi settings saved. Connecting...");
    html.replace("{{saved_ssid}}", htmlEscape(my_bootstrap_config.wifi_ssid));
    html.replace("{{device_id}}", htmlEscape(my_bootstrap_config.device_id));

    my_web_server.send(200, "text/html", html);

    my_restart_pending = true;
    my_restart_at_ms = millis() + 10000;
}
