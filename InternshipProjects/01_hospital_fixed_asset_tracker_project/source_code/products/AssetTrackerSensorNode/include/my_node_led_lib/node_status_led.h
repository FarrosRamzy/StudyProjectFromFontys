/**
 * @file node_status_led.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "my_node_led_lib/interfaces/i_node_status_led.h"
#include "node_config.h"

class NodeStatusLED : public INodeStatusLED
{
private:
    uint8_t green_pin;
    uint8_t red_pin;

    bool green_active;
    bool red_detect;
    bool red_active;

    bool identify_active;
    bool identify_led_on;

    uint8_t identify_toggles_remaining;
    uint32_t identify_last_toggle_time;
    uint32_t identify_interval_ms;

    uint32_t last_red_blink_time;
    uint32_t red_blink_interval_ms;

public:
    NodeStatusLED(uint8_t, uint8_t);
    ~NodeStatusLED() override;

    void beginMyLEDs() override;
    void setGreenConnected(bool) override;
    void setRedDetecting(bool) override;
    void startIdentifyBlink(uint8_t, uint32_t);
    void updateMyLEDstate() override;
};
