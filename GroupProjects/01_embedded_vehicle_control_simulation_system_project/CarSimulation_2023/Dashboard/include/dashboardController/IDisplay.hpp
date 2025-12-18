#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

namespace ActuatorsAndSensor
{
    class IDisplay
    {
    private:
        // set the LCD number of columns and rows
        int lcdColumns = 16;
        int lcdRows = 2;
        int pos = 0; // variable to store the servo position

    public:
        LiquidCrystal_I2C lcd;
        IDisplay() : lcd(0x27, lcdColumns, lcdRows)
        {
        }

        void displaySpeed(String value);
        void displayConnectionError(String errorMessage);
        void displayAlert(String dangerNotice);
        void clearLCD();
    };
}
