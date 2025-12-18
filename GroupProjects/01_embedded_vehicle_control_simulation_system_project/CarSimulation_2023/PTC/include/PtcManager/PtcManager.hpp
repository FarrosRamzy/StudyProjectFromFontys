#pragma once

#include "..\include\myBME280\Headers\MyCustomBME280.hpp"
#include "..\include\canCommunication\Headers\canManager.hpp"

namespace myPTC
{
    using namespace canCommunication;
    using namespace bmeSensor;
    class PtcManager
    {
    private:
        uint8_t bme1_address;
        double pressure_val;
        double temperature_val;

        String temperature_to_send;
        String pressure_to_send;

        bool overheat;
        bool flatted;
        // uint8_t bme2_address;

        canCommunication::canManager my_can_manager;
        bmeSensor::MyCustomBME280 my_custom_bme1;
        // bmeSensor::MyCustomBME280 my_custom_bme2;

        void handleCAN();
        void handleTemperature();
        void handlePressure();

    public:
        PtcManager(uint8_t);
        ~PtcManager();

        void myPtcConfig();
        void myPtcLoop();
    };
}