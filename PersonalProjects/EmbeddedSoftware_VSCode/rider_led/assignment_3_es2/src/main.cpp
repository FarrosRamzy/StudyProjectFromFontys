#include <led_mask.h>

ULL startTimer = millis();
ULL blinkStartTimer = millis();
ULL sweepStartTimer = millis();
ULL currentTimer;

bool sweepALeft = true;
bool sweepBLeft = true;

int lastBTNstate = LOW;

uint8_t sweepAcounter = 0;
uint8_t sweepBcounter = 1;

uint16_t sweepBmask = 0b0000000000001111;
uint16_t sweepAmask = 0b0000000000000001;
uint16_t desiredMask = 0b0000000011110000;
uint8_t sweepSizeMask = 0b00000000;

void setup()
{
  Serial.begin(9600);
  // setup LEDs for assignment a:

  DDRB |= SET_MASK(CREATE_MASK(1, PB5), CREATE_MASK(1, PB0));

  // setup LEDs for assignment b:
  DDRB |= CREATE_MASK(4, PB1);

  // setup the buttons' pins:
  DDRD &= ((~BTN_INPUT_A_MASK) & (~BTN_INPUT_B_MASK));
  PORTD |= BTN_INPUT_B_MASK;

  // DDRD ^= (BTN_INPUT_A_MASK | BTN_INPUT_B_MASK);
  // DDRD |= (BTN_INPUT_A_MASK);

  BIT16_BinaryPrintf(DDRD);
  BIT16_BinaryPrintf(PORTD);
  BIT16_BinaryPrintf(PIND);
}

void loop()
{
  // Declare local current timer.
  currentTimer = millis();

  // External LED blinking. (constantly happen in a loop)
  BlinkExternalLED(&blinkStartTimer);

  if ((currentTimer - startTimer) >= PRESS_TIMER)
  {
    // Turn on the builtin LED if button is pressed.
    if ((PIND & BTN_INPUT_A_MASK) != lastBTNstate)
    {
      changeBuiltInLED();
      BIT16_BinaryPrintf(PIND);
    //   PORTB |= BUILTIN_LED_OUTPUT_MASK;
    // }
    // else
    // {
    //   PORTB &= ~BUILTIN_LED_OUTPUT_MASK;
      lastBTNstate = (PIND & BTN_INPUT_A_MASK);
    }

    // Do sweep B if button is pressed.
    // Do sweep A if button is released.
    if (((PIND & BTN_INPUT_B_MASK) >> PD2) == LOW)
    {
      SweepB(&sweepStartTimer, &sweepBLeft, &sweepBcounter, &sweepBmask, desiredMask, &sweepSizeMask);
    }
    else
    {
      SweepA(&sweepStartTimer, &sweepALeft, &sweepAcounter, &sweepAmask);
    }
    startTimer = currentTimer;
  }
}