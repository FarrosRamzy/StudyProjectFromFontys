#pragma once

#include <Arduino.h>

namespace ActuatorsAndSensor
{
    class ITurnIndicator
    {
    public:
        virtual int isRightIndicator(int pointValue, int prevValue);
        virtual int readIndiacator(int PIN);
    };
}