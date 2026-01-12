/**
 * @file IMyNetCommSubscriber.hpp
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
#include "robotMain.hpp"

class IMyNetCommSubscriber
{
public:
    virtual ~IMyNetCommSubscriber(){};
    virtual bool subscribeToMyNetwork(const char *) = 0;
    virtual void unsubscribeTheNetwork(const char *) = 0;
};
