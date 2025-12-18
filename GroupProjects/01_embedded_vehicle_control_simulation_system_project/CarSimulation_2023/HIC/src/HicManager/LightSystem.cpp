#include "../include/Hic/LightSystem.hpp"

void LightSystem::blink(uint8_t pin_nr, uint32_t duration)
{
    unsigned long currentMillis = millis();
    static unsigned long previousMillis = 0;

    if (currentMillis - previousMillis >= duration)
    {
        previousMillis = currentMillis;
        if (digitalRead(pin_nr) == LOW)
        {
            digitalWrite(pin_nr, HIGH);
        }
        else
        {
            digitalWrite(pin_nr, LOW);
        }
    }
}

LightSystem::LightSystem(uint8_t leftIndicator, uint8_t rightIndicator, uint8_t leftHeadlight, uint8_t rightHeadlight)
    : leftIndicatorPin(leftIndicator), rightIndicatorPin(rightIndicator),
      headlightLeftPin(leftHeadlight), headlightRightPin(rightHeadlight), isHeadlightsOn(false)
{
    // Initialize the pin modes for the indicators and headlights
    pinMode(leftIndicatorPin, OUTPUT);
    pinMode(rightIndicatorPin, OUTPUT);
    pinMode(headlightLeftPin, OUTPUT);
    pinMode(headlightRightPin, OUTPUT);

    // Set the initial state of the lights (e.g., all off)
    digitalWrite(leftIndicatorPin, LOW);
    digitalWrite(rightIndicatorPin, LOW);
    digitalWrite(headlightLeftPin, LOW);
    digitalWrite(headlightRightPin, LOW);
}

void LightSystem::blinkIndicator(uint8_t pin_nr, uint32_t delay)
{
    blink(pin_nr, delay);
    
    if (pin_nr == leftIndicatorPin)
        Serial.println("Blinking Left Indicator");
    else if (pin_nr == rightIndicatorPin)
        Serial.println("Blinking Right Indicator");
}

void LightSystem::turnOffIndicators()
{
    digitalWrite(leftIndicatorPin, LOW);
    digitalWrite(rightIndicatorPin, LOW);

    // if (pin_nr == leftIndicatorPin)
    // {
    //     isTurningToLeft = false;
    // }
    // else if (pin_nr == rightIndicatorPin)
    // {
    //     isTurningToRight = false;
    // }
}

void LightSystem::turnOnHeadlights()
{
    if (!isHeadlightsOn)
    {
        digitalWrite(headlightLeftPin, HIGH);
        digitalWrite(headlightRightPin, HIGH);
        isHeadlightsOn = true;
    }
}

void LightSystem::turnOffHeadlights()
{
    if (isHeadlightsOn)
    {
        digitalWrite(headlightLeftPin, LOW);
        digitalWrite(headlightRightPin, LOW);
        isHeadlightsOn = false;
    }
}
