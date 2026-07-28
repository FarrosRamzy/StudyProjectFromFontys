/**
 * @file i_node_status_led.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

class INodeStatusLED
{
public:
    virtual ~INodeStatusLED() {}

    virtual void beginMyLEDs() = 0;
    virtual void setGreenConnected(bool) = 0;
    virtual void setRedDetecting(bool) = 0;
    virtual void startIdentifyBlink(uint8_t, uint32_t) = 0;
    virtual void updateMyLEDstate() = 0;
};
