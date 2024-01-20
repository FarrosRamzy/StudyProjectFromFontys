#ifndef LED_MASK_H
#define LED_MASK_H

#include <Arduino.h>

// LEDs' masks for part a.
#define BUILTIN_LED_OUTPUT_MASK (1 << PB5)
#define EXTERNAL_LED_OUTPUT_MASK (1 << PB0)

//#define LED_MASK (LED_1_MASK | LED_2_MASK | LED_3_MASK | LED_4_MASK)
#define CREATE_MASK(SIZE, SHIFT) ((1 << SIZE) - 1) << SHIFT
#define SET_MASK(MASK_A, MASK_B) (MASK_A) | (MASK_B)

// Button's mask for part a.
#define BTN_INPUT_A_MASK (1 << PD5)

// Button's mask for part b.
#define BTN_INPUT_B_MASK (1 << PD2)

// Timer for debouncing.
#define PRESS_TIMER 20
#define EXTERNAL_LED_TIMER 250
#define SWEEP_LED_TIMER 500

typedef unsigned long long ULL;

void BlinkExternalLED(ULL *);
void changeBuiltInLED();
void SweepA(ULL *, bool *, uint8_t *, uint16_t *);
void SweepB(ULL *, bool *, uint8_t *, uint16_t *, uint16_t, uint8_t *);
void BIT8_BinaryPrintf(uint8_t);
void BIT16_BinaryPrintf(uint16_t);

#endif
