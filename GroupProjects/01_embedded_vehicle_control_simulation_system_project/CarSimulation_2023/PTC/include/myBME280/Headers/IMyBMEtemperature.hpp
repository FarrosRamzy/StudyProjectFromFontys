#pragma once

#include "main_ptc.hpp"

namespace bmeSensor
{
    class IMyBMEtemperature
    {
    public:
        virtual int32_t readTemperature() = 0;
    };
}