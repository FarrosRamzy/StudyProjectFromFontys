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
      red_active(false), red_detect(false), identify_active(false),
      identify_led_on(false), identify_toggles_remaining(0),
      identify_last_toggle_time(LED_START_TIMER),
      identify_interval_ms(IDENTIFY_BLINK_INTERVAL_MS),
      last_red_blink_time(LED_START_TIMER),
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

    // During identify blink, both LEDs are controlled by updateMyLEDstate().
    // Do not let the normal connection indicator override the blink pattern.
    if (identify_active)
    {
        return;
    }

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
 * @param blink_count
 * @param interval_ms
 */
void NodeStatusLED::startIdentifyBlink(uint8_t blink_count, uint32_t interval_ms)
{
    if (blink_count == 0)
    {
        blink_count = IDENTIFY_BLINK_COUNT;
    }

    if (blink_count > 20)
    {
        blink_count = 20;
    }

    if (interval_ms < 50)
    {
        interval_ms = IDENTIFY_BLINK_INTERVAL_MS;
    }

    if (interval_ms > 2000)
    {
        interval_ms = 2000;
    }

    identify_active = true;
    identify_led_on = false;
    identify_toggles_remaining = blink_count * 2;
    identify_interval_ms = interval_ms;
    identify_last_toggle_time = millis();

    digitalWrite(green_pin, LOW);
    digitalWrite(red_pin, LOW);
}

/**
 * @brief
 *
 */
void NodeStatusLED::updateMyLEDstate()
{
    uint32_t now = millis();

    if (identify_active)
    {
        if ((uint32_t)(now - identify_last_toggle_time) >= identify_interval_ms)
        {
            identify_last_toggle_time = now;
            identify_led_on = !identify_led_on;

            digitalWrite(green_pin, identify_led_on ? HIGH : LOW);
            digitalWrite(red_pin, identify_led_on ? HIGH : LOW);

            if (identify_toggles_remaining > 0)
            {
                identify_toggles_remaining--;
            }

            if (identify_toggles_remaining == 0)
            {
                identify_active = false;
                identify_led_on = false;
                red_active = false;

                digitalWrite(green_pin, green_active ? HIGH : LOW);
                digitalWrite(red_pin, LOW);
            }
        }

        return;
    }

    if (!red_detect)
    {
        return;
    }

    if ((uint32_t)(now - last_red_blink_time) >= red_blink_interval_ms)
    {
        last_red_blink_time = now;
        red_active = !red_active;
        digitalWrite(red_pin, red_active ? HIGH : LOW);
    }
}
