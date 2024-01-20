#include "..\include\PtcManager\PtcManager.hpp"

namespace myPTC
{
    PtcManager::PtcManager(uint8_t bme1) : bme1_address(bme1), my_custom_bme1(bme1_address)
    {
        ;
    }

    PtcManager::~PtcManager()
    {
        ;
    }

    void PtcManager::myPtcConfig()
    {
        overheat = false;
        flatted = false;
        my_can_manager.canConfig();
        my_custom_bme1.sensorSetup();
    }

    void PtcManager::myPtcLoop()
    {
        my_custom_bme1.sensorLoop();
        handleTemperature();
        handlePressure();
        handleCAN();
    }

    void PtcManager::handleCAN()
    {
        if (overheat)
        {
            Serial.println("overheat");
            my_can_manager.sendMessage(MessageId::MESSAGE_ID_ENGINE_TEMPERATURE_TOO_HIGH, MessageValue::MESSAGE_VALUE_ON);
        }

        if (flatted)
        {
            Serial.println("flatted");
            my_can_manager.sendMessage(MessageId::MESSAGE_ID_TIRE_PRESSURE_TOO_LOW, MessageValue::MESSAGE_VALUE_ON);
        }

        my_can_manager.sendMessage(MessageId::MESSAGE_ID_SHOW_TEMPERATURE, temperature_to_send);
        my_can_manager.sendMessage(MessageId::MESSAGE_ID_SHOW_PRESSURE, pressure_to_send);
    }

    void PtcManager::handleTemperature()
    {
        temperature_to_send = "";
        temperature_val = my_custom_bme1.getTemperature();
        Serial.print("Temp: ");
        temperature_to_send = temperature_val;
        Serial.println(temperature_to_send);
        // temperature_to_send.concat(temperature_val);
        if (temperature_val > MAX_TEMPERATURE)
        {
            overheat = true;
        }
        else
        {
            overheat = false;
        }
    }

    void PtcManager::handlePressure()
    {
        pressure_to_send = "";
        pressure_val = my_custom_bme1.getPressure();
        Serial.print("Press: ");
        pressure_to_send = pressure_val;
        Serial.println(pressure_to_send);
        // pressure_to_send.concat(pressure_val);
        if (pressure_val > MAX_PRESSURE)
        {
            flatted = true;
        }
        else
        {
            flatted = false;
        }
    }
}