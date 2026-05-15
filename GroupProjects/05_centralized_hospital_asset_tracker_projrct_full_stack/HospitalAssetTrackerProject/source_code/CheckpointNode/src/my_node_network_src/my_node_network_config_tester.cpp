/**
 * @file my_node_network_config_tester.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_network_config.h"

/**
 * @brief 
 * 
 * @param ssid 
 * @param password 
 * @param is_open_network 
 * @param timeout_ms 
 * @param status_message 
 * @return true 
 * @return false 
 */
bool MyNodeNetworkConfig::testWiFiConnection(const String &ssid, const String &password,
                                             bool is_open_network, uint32_t timeout_ms,
                                             String &status_message)
{
    Serial.println("[NETCFG] Testing WiFi connection...");
    Serial.print("[NETCFG] SSID: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_AP_STA);

    WiFi.disconnect(false);
    delay(100);

    if (is_open_network)
    {
        WiFi.begin(ssid.c_str());
    }
    else
    {
        WiFi.begin(ssid.c_str(), password.c_str());
    }

    uint32_t start = millis();
    uint32_t last_check = 0;
    wl_status_t last_status = WL_IDLE_STATUS;

    while ((uint32_t)(millis() - start) < timeout_ms)
    {
        uint32_t now = millis();
        if ((uint32_t)(now - last_check) < MY_NODE_NETWORK_TEST_TIMER_MS)
        {
            yield();
            continue;
        }
        
        last_check = now;

        wl_status_t st = WiFi.status();

        if (st != last_status)
        {
            Serial.print("[NETCFG] WiFi status = ");
            Serial.println((int)st);
            last_status = st;
        }
        
        if (st == WL_CONNECTED)
        {
            status_message = "Connected successfully.";
            Serial.println("[NETCFG] WiFi test success.");
            Serial.print("[NETCFG] STA IP: ");
            Serial.println(WiFi.localIP());
            return true;
        }

        if (st == WL_NO_SSID_AVAIL)
        {
            status_message = "Wi-Fi name (SSID) not found.";
            Serial.println("[NETCFG] SSID not found.");
            return false;
        }
        
        if (st == WL_CONNECT_FAILED)
        {
            /* code */
            status_message = "Connection failed. Password may be wrong or the network rejected the device.";
            Serial.println("[NETCFG] Connect failed.");
            return false;
        }
    }
    
    wl_status_t final_status = WiFi.status();
    
    if (final_status == WL_CONNECTED)
    {
        /* code */
        status_message = "Connection success.";
        return true;
    }
    
    if (final_status == WL_NO_SSID_AVAIL)
    {
        /* code */
        status_message = "SSID not found. Wrong Wi-Fi name.";
        return false;
    }
    
    if (final_status == WL_CONNECT_FAILED)
    {
        /* code */
        status_message = "Connection failed. Check password or the network availability again.";
        return false;
    }
    
    status_message = "Connection timed out. Check the SSID, password, hotspot status, and signal strength.";
    Serial.println("[NETCFG] WiFi test timeout.");
    return false;
}