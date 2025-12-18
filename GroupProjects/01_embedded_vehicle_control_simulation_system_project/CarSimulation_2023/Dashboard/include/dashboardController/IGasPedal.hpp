#pragma once

#include <Arduino.h>
namespace ActuatorsAndSensor
{
    class IGasPedal
    {
    public:
        virtual bool increaseSpeed(int pin);
    };
}
