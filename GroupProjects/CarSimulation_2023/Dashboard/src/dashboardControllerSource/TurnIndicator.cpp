#include "../include/dashboardController/ITurnIndicator.hpp"
using namespace ActuatorsAndSensor;

int ITurnIndicator::isRightIndicator(int pointValue, int prevValue)
{
    int difference = pointValue - prevValue;

    if ((difference == 1 || difference == -1) && pointValue < 400)
    {
        return 1; // indicate right
    }
    else if ((difference == 1 || difference == -1) && pointValue > 600)
    {
        return 0; // indicate left
    }
    else if ((difference == 1 || -1) && pointValue < 600 && pointValue > 400)
    {
        return 2; // off
    }
    return -1;
}


int ITurnIndicator::readIndiacator(int PIN)
{
    int sensorValue = analogRead(PIN);         // Read the analog value from the potentiometer
    return sensorValue;
}