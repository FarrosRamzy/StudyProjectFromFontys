#pragma once

namespace bmeSensor
{
    enum class myBMEctrlPressOversample
    {
        BME_P_OSR_0 = 0b000,
        BME_P_OSR_1 = 0b001,
        BME_P_OSR_2 = 0b010,
        BME_P_OSR_4 = 0b011,
        BME_P_OSR_8 = 0b100,
        BME_P_OSR_16 = 0b101
    };
}