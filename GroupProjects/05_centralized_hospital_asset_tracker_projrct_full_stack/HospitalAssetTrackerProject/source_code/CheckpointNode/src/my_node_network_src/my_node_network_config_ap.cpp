/**
 * @file my_node_network_config_ap.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::startAccessPoint()
{
    String ap_name = makeAccessPointName();
    WiFi.mode(WIFI_AP);

    const char *ap_password = MY_DEFAULT_ACCESS_POINT_PASSWORD;
    bool ok = WiFi.softAP(ap_name.c_str(), ap_password);

    if (!ok)
    {
        Serial.println("[NETCFG] Failed to start SoftAP.");
        return;
    }

    IPAddress ip = WiFi.softAPIP();

    Serial.println("[NETCFG] SoftAP started.");
    Serial.print("[NETCFG] AP Name: ");
    Serial.println(ap_name);
    Serial.print("[NETCFG] AP IP: ");
    Serial.println(ip);
}

/**
 * @brief
 *
 */
void MyNodeNetworkConfig::startWebServer()
{
    my_web_server.on("/", HTTP_GET, std::bind(&MyNodeNetworkConfig::handleRoot, this));
    my_web_server.on("/save", HTTP_POST, std::bind(&MyNodeNetworkConfig::handleSave, this));
    my_web_server.on("/refresh", HTTP_GET, std::bind(&MyNodeNetworkConfig::handleRefresh, this));

    my_web_server.on("/style.css", HTTP_GET, std::bind(&MyNodeNetworkConfig::handleStyle, this));
    my_web_server.on("/script.js", HTTP_GET, std::bind(&MyNodeNetworkConfig::handleScript, this));

    // New routes for split CSS files
    my_web_server.serveStatic("/css/variables.css", LittleFS, "/css/variables.css", "text/css");
    my_web_server.serveStatic("/css/base.css", LittleFS, "/css/base.css", "text/css");
    my_web_server.serveStatic("/css/layout.css", LittleFS, "/css/layout.css", "text/css");
    my_web_server.serveStatic("/css/hero.css", LittleFS, "/css/hero.css", "text/css");
    my_web_server.serveStatic("/css/panels.css", LittleFS, "/css/panels.css", "text/css");
    my_web_server.serveStatic("/css/forms.css", LittleFS, "/css/forms.css", "text/css");
    my_web_server.serveStatic("/css/buttons.css", LittleFS, "/css/buttons.css", "text/css");
    my_web_server.serveStatic("/css/device_info.css", LittleFS, "/css/device_info.css", "text/css");
    my_web_server.serveStatic("/css/status.css", LittleFS, "/css/status.css", "text/css");
    my_web_server.serveStatic("/css/utilities.css", LittleFS, "/css/utilities.css", "text/css");
    my_web_server.serveStatic("/css/responsive.css", LittleFS, "/css/responsive.css", "text/css");

    // New routes for split JavaScript files
    my_web_server.serveStatic("/js/dom_utils.js", LittleFS, "/js/dom_utils.js", "application/javascript");
    my_web_server.serveStatic("/js/ui_controls.js", LittleFS, "/js/ui_controls.js", "application/javascript");
    my_web_server.serveStatic("/js/wifi_form.js", LittleFS, "/js/wifi_form.js", "application/javascript");
    my_web_server.serveStatic("/js/app_init.js", LittleFS, "/js/app_init.js", "application/javascript");

    my_web_server.on("/debug/files", HTTP_GET, std::bind(&MyNodeNetworkConfig::handleDebugFiles, this));

    my_web_server.begin();
    Serial.println("[NETCFG] Web server started.");
}

/**
 * @brief
 *
 * @return String
 */
String MyNodeNetworkConfig::makeAccessPointName() const
{
    uint64_t chip_id = ESP.getEfuseMac();

    char ap_name[MY_ACCESS_POINT_SIZE];
    snprintf(ap_name, sizeof(ap_name), "Med-Tracker-Node-%04X", (uint16_t)(chip_id & 0xFFFF));

    return String(ap_name);
}

/**
 * @brief
 *
 * @param input
 * @return String
 */
String MyNodeNetworkConfig::makeUrlSafe(const String &input) const
{
    String out;
    out.reserve(input.length() * 3);

    const char *hex = "0123456789ABCDEF";

    for (size_t i = 0; i < input.length(); i++)
    {
        unsigned char c = (unsigned char)input[i];

        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '-' || c == '_' || c == '.' || c == '~')
        {
            out += (char)c;
        }
        else if (c == ' ')
        {
            out += "%20";
        }
        else
        {
            out += '%';
            out += hex[(c >> 4) & 0x0F];
            out += hex[c & 0x0F];
        }
    }

    return out;
}