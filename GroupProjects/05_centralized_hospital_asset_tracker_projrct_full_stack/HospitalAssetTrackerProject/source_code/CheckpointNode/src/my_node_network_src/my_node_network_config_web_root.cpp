/**
 * @file my_node_network_config_web_root.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

void MyNodeNetworkConfig::handleRoot()
{
    Serial.println("[NETCFG] handleRoot called");

    String html = readFile(MY_BOOTSTRAP_BASE_FILE);

    if (html.length() == 0)
    {
        Serial.println("[NETCFG] esp_index.html failed to load");
        my_web_server.send(500, "text/plain", "Failed to load esp_index.html");
        return;
    }

    Serial.println("[NETCFG] index.html loaded.");

    String options_html = buildWiFiOptionsHtml();

    String device_id = htmlEscape(my_bootstrap_config.device_id);
    String firmware_version = htmlEscape(String(MY_FIRMWARE_VERSION));
    String mac_address = htmlEscape(WiFi.macAddress());

    String wifi_open_checked = (my_bootstrap_config.wifi_password.length() == 0)
                                   ? "checked"
                                   : "";
    String wifi_status = (WiFi.status() == WL_CONNECTED)
                             ? "Connected"
                             : "Disconnected";
    String ip_address = (WiFi.status() == WL_CONNECTED)
                            ? WiFi.localIP().toString()
                            : WiFi.softAPIP().toString();

    html.replace("{{wifi_options}}", options_html);
    html.replace("{{wifi_open_checked}}", wifi_open_checked);
    html.replace("{{wifi_status}}", htmlEscape(wifi_status));
    html.replace("{{ip_address}}", htmlEscape(ip_address));
    html.replace("{{device_id}}", device_id);
    html.replace("{{firmware_version}}", firmware_version);
    html.replace("{{mac_address}}", mac_address);

    my_web_server.send(200, "text/html", html);
}