#pragma once

#include "main_ptc.hpp"

namespace bmeSensor
{
    class IMyBMEpressure
    {
    public:
        virtual int32_t readPressure() = 0;
    };
}