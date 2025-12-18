#pragma once

#include "IMyBMEpressure.hpp"
#include "IMyBMEtemperature.hpp"

namespace bmeSensor
{
    class IMyBMEsensor : public IMyBMEtemperature, public IMyBMEpressure
    {
    public:
        virtual uint8_t BME280getID() = 0;
        virtual uint8_t BME280ctrlMeasure() = 0;
        virtual void BME280ctrlMeasure(uint8_t) = 0;
        virtual void BME280ctrlMeasure(myBMEctrlMeasureMode, myBMEctrlTempOversample, myBMEctrlPressOversample) = 0;
        virtual void BME280config() = 0;
    };
}