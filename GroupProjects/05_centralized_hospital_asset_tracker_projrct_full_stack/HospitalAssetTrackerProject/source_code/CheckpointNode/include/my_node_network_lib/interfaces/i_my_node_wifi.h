/**
 * @file i_my_node_wifi.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

class IMyNodeWiFi
{
public:
   virtual ~IMyNodeWiFi() {};

   virtual void setCredentials(const char *, const char *) = 0;
   virtual bool hasCredentials() const = 0;

   virtual void startWiFi() = 0;
   virtual void loopNetWiFi() = 0;
   virtual bool amIConnected() = 0;
   virtual void reconnectWiFi() = 0;
   virtual void disconnectWiFi() = 0;
};