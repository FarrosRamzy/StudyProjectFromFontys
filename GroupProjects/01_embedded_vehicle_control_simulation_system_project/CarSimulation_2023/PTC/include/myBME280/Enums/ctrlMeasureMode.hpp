#pragma once

namespace bmeSensor
{
    enum class myBMEctrlMeasureMode
    {
        BME_SLEEP = 0b00,
        BME_FORCED_1 = 0b01,
        BME_FORCED_2 = 0b10,
        BME_NORMAL = 0b11
    };
}