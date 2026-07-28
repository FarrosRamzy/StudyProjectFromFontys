/**
 * @file my_node_network_config_web.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.3
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
void MyNodeNetworkConfig::handleRefresh()
{
    Serial.println("[NETCFG] /refresh requested");

    String options_html = buildWiFiOptionsHtml();

    Serial.print("[NETCFG] refresh result: ");
    Serial.println(options_html);
    my_web_server.send(200, "text/plain", options_html);
}

/**
 * @brief
 *
 * @param input
 * @return String
 */
String MyNodeNetworkConfig::htmlEscape(const String &input) const
{
    String out;
    out.reserve(input.length() + 16);

    for (size_t i = 0; i < input.length(); i++)
    {
        char c = input[i];

        switch (c)
        {
        case '&':
            out += "&amp;";
            break;
        case '<':
            out += "&lt;";
            break;
        case '>':
            out += "&gt;";
            break;
        case '"':
            out += "&quot;";
            break;
        case '\'':
            out += "&#39;";
            break;
        default:
            out += c;
            break;
        }
    }

    return out;
}

/**
 * @brief
 *
 * @param path
 * @return String
 */
String MyNodeNetworkConfig::readFile(const char *path)
{
    File file = LittleFS.open(path, "r");
    if (!file || file.isDirectory())
    {
        return String();
    }

    String content = file.readString();
    file.close();
    return content;
}

void MyNodeNetworkConfig::handleDebugFiles()
{
    String output;

    File root = LittleFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
        output += file.name();
        output += "\n";
        file = root.openNextFile();
    }

    my_web_server.send(200, "text/plain", output);
}
