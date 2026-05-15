/**
 * @file node_status_led.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_led_lib/node_status_led.h"

/**
 * @brief Construct a new Node Status L E D:: Node Status L E D object
 *
 * @param green_pin
 * @param red_pin
 */
NodeStatusLED::NodeStatusLED(uint8_t green_pin, uint8_t red_pin)
    : green_pin(green_pin), red_pin(red_pin), green_active(false),
      red_active(false), red_detect(false), last_red_blink_time(LED_START_TIMER),
      red_blink_interval_ms(BLINK_DURATION_MS)
{
}

/**
 * @brief Destroy the Node Status L E D:: Node Status L E D object
 *
 */
NodeStatusLED::~NodeStatusLED()
{
}

/**
 * @brief
 *
 */
void NodeStatusLED::beginMyLEDs()
{
    pinMode(green_pin, OUTPUT);
    pinMode(red_pin, OUTPUT);

    digitalWrite(green_pin, LOW);
    digitalWrite(red_pin, LOW);
    Serial.println("led_setup");
}

/**
 * @brief
 *
 * @param connected
 */
void NodeStatusLED::setGreenConnected(bool connected)
{
    green_active = connected;
    digitalWrite(green_pin, connected ? HIGH : LOW);
}

/**
 * @brief
 *
 * @param detect
 */
void NodeStatusLED::setRedDetecting(bool detect)
{
    red_detect = detect;

    if (!red_detect)
    {
        red_active = false;
        digitalWrite(red_pin, LOW);
    }
}

/**
 * @brief
 *
 */
void NodeStatusLED::updateMyLEDstate()
{
    if (!red_detect)
    {
        return;
    }

    uint32_t now = millis();
    if ((uint32_t)(now - last_red_blink_time) >= red_blink_interval_ms)
    {
        last_red_blink_time = now;
        red_active = !red_active;
        digitalWrite(red_pin, red_active ? HIGH : LOW);
    }
    
}