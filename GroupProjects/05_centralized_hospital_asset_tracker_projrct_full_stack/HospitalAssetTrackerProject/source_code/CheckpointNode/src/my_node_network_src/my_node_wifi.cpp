/**
 * @file my_node_wifi.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_network_lib/my_node_wifi.h"

/**
 * @brief Construct a new My Node Wi Fi:: My Node Wi Fi object
 * 
 */
MyNodeWiFi::MyNodeWiFi()
    : ssid(""), password(""), last_reconnect_attempt(FIRST_RECONNECT_ATTEMPT),
      reconnect_interval(NET_RECONNECT_INTERVAL_MS)
{
}

/**
 * @brief Destroy the My Node Wi Fi:: My Node Wi Fi object
 *
 */
MyNodeWiFi::~MyNodeWiFi()
{
}

/**
 * @brief
 *
 */
void MyNodeWiFi::setCredentials(const char *my_ssid, const char *my_password)
{
    ssid = my_ssid;
    password = my_password;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeWiFi::hasCredentials() const
{
    return ssid.length() > 0;
}

/**
 * @brief
 *
 */
void MyNodeWiFi::startWiFi()
{
    Serial.println("wifi_setup");
    if (!hasCredentials())
    {
        Serial.println("[WiFi] has no credentials set.");
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    last_reconnect_attempt = millis();

    Serial.print("[WiFi] connecting to: ");
    Serial.println(ssid);
    Serial.println(WiFi.status());
}

/**
 * @brief
 *
 */
void MyNodeWiFi::loopNetWiFi()
{
    if (amIConnected())
    {
        return;
    }

    reconnectWiFi();
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool MyNodeWiFi::amIConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

/**
 * @brief
 *
 */
void MyNodeWiFi::reconnectWiFi()
{
    if (!hasCredentials())
    {
        return;
    }

    uint32_t now = millis();

    if ((uint32_t)(now - last_reconnect_attempt) < reconnect_interval)
    {
        return;
    }

    last_reconnect_attempt = now;
    disconnectWiFi();
    Serial.println("[WiFi] reconnecting ... ");
    startWiFi();
}

/**
 * @brief
 *
 */
void MyNodeWiFi::disconnectWiFi()
{
    WiFi.disconnect(true, false);
}