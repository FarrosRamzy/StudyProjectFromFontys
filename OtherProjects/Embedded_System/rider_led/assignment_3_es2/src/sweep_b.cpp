#include <led_mask.h>

/**
 * @brief A multiple sweep of the 4 LEDs by sequences (sweep to right, or to left).
 * 
 * @param startTimer the start millis value,
 *        transferred from main.cpp by pointer.
 * @param sweepToLeft a boolean state of sweep direction condition,
 *        transferred from main.cpp by pointer.
 * @param sweepCounter a counter for the sweep,
 *        transferred from main.cpp by pointer.
 * @param sweepBmask mask value for sweep B,
 *        transferred from main.cpp by pointer. 
 * @param desiredMask a value of the desired mask area from what has been stated in main.cpp.
 * @param sizeOfMask a value of the desired mask size that could be increased or decreased,
 *        depending on the counter and position.
 */
void SweepB(ULL *startTimer, bool *sweepToLeft, uint8_t *sweepCounter, uint16_t *sweepBmask, uint16_t desiredMask, uint8_t *sizeOfMask)
{
    if ((millis() - *startTimer) >= SWEEP_LED_TIMER)
    {
        PORTB = (PORTB & ~CREATE_MASK(4,PB1));
        if (*sweepToLeft)
        {
            *sweepBmask = *sweepBmask << 1;
            *sweepCounter += 1;
            *sizeOfMask = desiredMask & *sweepBmask;
            *sizeOfMask = *sizeOfMask >> 3;

            PORTB |= (*sizeOfMask | (1 << PB7));

            if (*sweepCounter >= 8)
            {
                *sweepToLeft = false;
            }
        }
        else
        {
            *sweepBmask = *sweepBmask >> 1;
            *sweepCounter -= 1;
            *sizeOfMask = desiredMask & *sweepBmask;
            *sizeOfMask = *sizeOfMask >> 3;

            PORTB |= (*sizeOfMask | (1 << PB7));

            if (*sweepCounter <= 2)
            {
                *sweepToLeft = true;
            }
        }
        *startTimer = millis();
    }
}