#include "../include/dashboardController/IGasPedal.hpp"
using namespace ActuatorsAndSensor;

// Implement the methods defined in IGasPedal as needed
bool IGasPedal::increaseSpeed(int gaspeddalPIN)
{
    int buttonState = digitalRead(gaspeddalPIN);

    // Check if the button is pressed
    if (buttonState == LOW)
    {
        Serial.println("Acceleration!");
        return true;
    }
    else
    {
        return false;
    }
}
