/**
 * @file IMyNetworkConnector.hpp
 * @author farros ramzy (424848@student.fontys.nl)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <Arduino.h>
#include "IMyNetCommPublisher.hpp"
#include "IMyNetCommSubscriber.hpp"

class IMyNetworkConnector : public IMyNetCommPublisher, public IMyNetCommSubscriber
{
public:
    virtual ~IMyNetworkConnector(){};
    virtual void setServer(const char *) = 0;
    virtual void setPort(int) = 0;
    virtual void myCallBackFunction(MQTT_CALLBACK_SIGNATURE) = 0;
    virtual void connectToMyNetwork() = 0;
    virtual void myNetLoop() = 0;
    virtual bool amIconnected() = 0;
};
