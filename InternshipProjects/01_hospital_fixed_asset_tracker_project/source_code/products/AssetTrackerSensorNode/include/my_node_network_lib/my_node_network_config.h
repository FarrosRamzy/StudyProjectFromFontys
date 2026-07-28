/**
 * @file my_node_network_config.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <functional>
#include <LittleFS.h>
#include "my_node_network_lib/interfaces/i_my_node_network_config.h"
#include "node_config.h"

class MyNodeNetworkConfig : public IMyNodeNetworkConfig
{
private:
    Preferences my_preferences;
    WebServer my_web_server;

    myNodeBootstrapConfig my_bootstrap_config;
    myNodeRemoteConfig my_remote_config;

    bool my_restart_pending;
    uint32_t my_restart_at_ms;

    bool my_setup_mode;

public:
    MyNodeNetworkConfig();
    ~MyNodeNetworkConfig() override;

    void beginMyNetConfig() override;
    void loopMyNetConfig() override;

    bool isConfigured() const override;
    bool isSetupMode() const override;

    const myNodeBootstrapConfig &getBootstrapConfig() const override;
    const myNodeRemoteConfig &getRemoteConfig() const override;

    void setRemoteConfig(const String &, const String &, const String &, const String &, uint16_t, bool) override;

    void resetConfiguration() override;

private:
    void loadConfig();
    void saveConfig();

    void startAccessPoint();
    void startWebServer();

    String makeAccessPointName() const;
    String generateDeviceId() const;

    void handleRoot();
    void handleSave();
    void handleRefresh();

    void serveFile(const char *, const char *);
    void handleStyle();
    void handleScript();

    void clearBootstrapConfig(bool);
    void clearRemoteConfig();

    void handleDebugFiles();

    String buildWiFiOptionsHtml();
    String htmlEscape(const String &) const;
    String readFile(const char *);
    String makeUrlSafe(const String &) const;

    bool testWiFiConnection(const String &, const String &, bool, uint32_t, String &);
};
