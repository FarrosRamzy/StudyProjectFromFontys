#include <led_mask.h>

/**
 * @brief Blink the external LED automatically per half second.
 * 
 * @param startTimer the start millis value, 
 *        transferred from main.cpp by pointer.
 */
void BlinkExternalLED(ULL *startTimer)
{
    if ((millis() - *startTimer) >= EXTERNAL_LED_TIMER)
    {
        PORTB ^= EXTERNAL_LED_OUTPUT_MASK;
        *startTimer = millis();
    }
}

/**
 * @brief change the state of built-in LED,
 *        based on the button press condition.
 * 
 */
void changeBuiltInLED()
{
    PORTB ^= BUILTIN_LED_OUTPUT_MASK;
}