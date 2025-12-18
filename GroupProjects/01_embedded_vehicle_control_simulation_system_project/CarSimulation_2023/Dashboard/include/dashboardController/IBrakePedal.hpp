#pragma once


#include <Arduino.h>
namespace ActuatorsAndSensor
{
    class IBrakePedal
    {
    public:
        virtual bool decreaseSpeed(int pin);
    };
}
