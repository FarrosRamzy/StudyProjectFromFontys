#include "../include/dashboardController/IHandBreak.hpp"
using namespace ActuatorsAndSensor;


bool IHandBreak::IsHandBreakPulled(int pin)
{
    int buttonState = digitalRead(pin);

    // Check if the button is pressed
    if (buttonState == LOW)
    {
        Serial.println("HANDBREAK!");
        return true;
    }
    else
    {
        return false;
    }
}
