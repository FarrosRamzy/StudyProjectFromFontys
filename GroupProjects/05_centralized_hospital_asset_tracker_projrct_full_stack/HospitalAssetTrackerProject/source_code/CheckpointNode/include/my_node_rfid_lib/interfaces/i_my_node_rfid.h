/**
 * @file i_my_node_rfid.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "my_node_rfid_lib/uhf_rmt_commands.h"

class IMyNodeRFID
{
public:
    virtual ~IMyNodeRFID(){}

    virtual void beginMyNodeRFID(uint32_t) = 0;
    virtual void enableMyRFID() = 0;
    virtual void disableMyRFID() = 0;
    virtual void clearBuffer() = 0;

    virtual bool pollFrame() = 0;
    virtual bool readDetectedTag(char *, size_t) = 0;

    virtual void configureRFID() = 0;
    
    virtual void startRFIDConfiguration(uint16_t) = 0;
    virtual void runRFIDConfiguration() = 0;
    virtual bool isRFIDConfigurationFinished() const = 0;
};