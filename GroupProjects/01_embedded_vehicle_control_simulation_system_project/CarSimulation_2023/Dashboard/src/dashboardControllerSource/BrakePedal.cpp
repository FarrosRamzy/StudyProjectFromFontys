#include "../include/dashboardController/IBrakePedal.hpp"

using namespace ActuatorsAndSensor;

// Implement the methods defined in IBrakePedal as needed
bool IBrakePedal::decreaseSpeed(int gaspeddalPIN)
{
    int buttonState = digitalRead(gaspeddalPIN);

    // Check if the button is pressed
    if (buttonState == LOW)
    {
        Serial.println("Break!");
        return true;
    }
    else
    {
        return false;
    }
}