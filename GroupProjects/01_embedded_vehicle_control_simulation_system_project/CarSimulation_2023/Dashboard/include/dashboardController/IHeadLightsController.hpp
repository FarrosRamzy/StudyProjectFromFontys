#pragma once

#include <Arduino.h>

namespace ActuatorsAndSensor
{
    class IHeadLightsController
    {
    public:
        bool doHeadlightsNeedToTurnOn(int pin);
    };
}
