/**
 * @file my_node_network_config_web_wifi_option_builder.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

String MyNodeNetworkConfig::buildWiFiOptionsHtml()
{
    WiFi.disconnect(true);
    
    WiFi.mode(WIFI_AP_STA);

    String my_html_options;

    int my_network_count = WiFi.scanNetworks();

    if (my_network_count <= 0)
    {
        my_html_options += "<option value=''>No networks found</option>";
        return my_html_options;
    }

    bool is_selected_written = false;

    for (int i = 0; i < my_network_count; i++)
    {
        String available_ssid = WiFi.SSID(i);
        int32_t available_rssi = WiFi.RSSI(i);

        if (available_ssid.length() == 0)
        {
            continue;
        }

        my_html_options += "<option value='";
        my_html_options += htmlEscape(available_ssid);
        my_html_options += "'";

        if (!is_selected_written && available_ssid == my_bootstrap_config.wifi_ssid)
        {
            my_html_options += " selected";
            is_selected_written = true;
        }

        my_html_options += ">";
        my_html_options += htmlEscape(available_ssid);
        my_html_options += " (";
        my_html_options += String(available_rssi);
        my_html_options += " dBm)";
        my_html_options += "</option>";
    }

    if (my_html_options.length() == 0)
    {
        my_html_options = "<option value=''>No visible SSIDs</option>";
    }

    WiFi.scanDelete();

    return my_html_options;
}

void MyNodeNetworkConfig::serveFile(const char *path, const char *content_type)
{
    File my_little_file = LittleFS.open(path, "r");
    if (!my_little_file)
    {
        String msg = "File not found: ";
        msg += path;
        my_web_server.send(404, "text/plain", msg);
        return;
    }

    my_web_server.streamFile(my_little_file, content_type);
    my_little_file.close();
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::handleStyle()
{
    serveFile("/style.css", "text/css");
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::handleScript()
{
    serveFile("/script.js", "application/javascript");
}