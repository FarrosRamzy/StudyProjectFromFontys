#pragma once

#include "IMyBMEsensor.hpp"

namespace bmeSensor
{
    class MyCustomBME280 : public IMyBMEsensor
    {
    private:
        uint8_t my_address;

        uint16_t dig_t1;
        int16_t dig_t2;
        int16_t dig_t3;

        uint16_t dig_p1;
        int16_t dig_p2;
        int16_t dig_p3;
        int16_t dig_p4;
        int16_t dig_p5;
        int16_t dig_p6;
        int16_t dig_p7;
        int16_t dig_p8;
        int16_t dig_p9;

        int32_t t_fine;

        myBMEctrlMeasureMode ctrl_mode;
        myBMEctrlPressOversample ctrl_pres;
        myBMEctrlTempOversample ctrl_temp;

        uint8_t BME280getID() override;
        uint8_t BME280ctrlMeasure() override;
        uint32_t pressureCalculation(int32_t, uint16_t, int16_t, int16_t, int16_t,
                                     int16_t, int16_t, int16_t, int16_t, int16_t,
                                     int32_t *);
        int32_t temperatureCalculation(int32_t, uint16_t, int16_t, int16_t, int32_t *);
        int32_t readTemperature() override;
        int32_t readPressure() override;

        void BME280ctrlMeasure(uint8_t) override;
        void BME280ctrlMeasure(myBMEctrlMeasureMode, myBMEctrlTempOversample,
                               myBMEctrlPressOversample) override;
        void BME280config() override;
        
        void calculateTemperatureCalibrationValues();
        void calculatePressureCalibrationValues();

    public:
        MyCustomBME280(uint8_t);
        ~MyCustomBME280();
        
        void sensorSetup();
        void sensorLoop();

        double getTemperature();
        double getPressure();
    };
}