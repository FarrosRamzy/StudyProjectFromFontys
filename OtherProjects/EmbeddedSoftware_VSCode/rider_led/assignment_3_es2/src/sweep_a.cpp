#include <led_mask.h>

/**
 * @brief A single sweep of the 4 LEDs (sweep to right, or to left).
 * 
 * @param startTimer the start millis value,
 *        transferred from main.cpp by pointer.
 * @param sweepToLeft a boolean state of sweep direction condition,
 *        transferred from main.cpp by pointer.
 * @param sweepCounter a counter for the sweep,
 *        transferred from main.cpp by pointer.
 * @param sweepAmask mask value for sweep A,
 *        transferred from main.cpp by pointer.
 */
void SweepA(ULL *startTimer, bool *sweepToLeft, uint8_t *sweepCounter, uint16_t *sweepAmask)
{
    if ((millis() - *startTimer) >= SWEEP_LED_TIMER)
    {
        PORTB = (PORTB & ~CREATE_MASK(4,PB1));
        if (*sweepToLeft)
        {
            *sweepAmask = *sweepAmask << 1;
            PORTB ^= *sweepAmask;
            *sweepCounter += 1;
            if (*sweepCounter >= 4)
            {
                *sweepToLeft = false;
            }
        }
        else
        {
            *sweepAmask = *sweepAmask >> 1;
            PORTB ^= *sweepAmask;
            *sweepCounter -= 1;
            if (*sweepCounter <= 1)
            {
                *sweepToLeft = true;
            }
        }
        *startTimer = millis();
    }
}