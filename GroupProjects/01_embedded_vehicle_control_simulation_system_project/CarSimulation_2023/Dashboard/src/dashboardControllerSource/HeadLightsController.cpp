#include "../include/dashboardController/IHeadLightsController.hpp"

using namespace ActuatorsAndSensor;

bool ActuatorsAndSensor::IHeadLightsController::doHeadlightsNeedToTurnOn(int headlightsPIN)
{
    int buttonState = digitalRead(headlightsPIN);

    if (buttonState == LOW)
    {
        return true;
    }
    else
    {
        return false;
    }
}
