#pragma once

#include <Arduino.h>
namespace ActuatorsAndSensor
{
    class IHandBreak
    {
    public:
        virtual bool IsHandBreakPulled(int pin);
    };
}
