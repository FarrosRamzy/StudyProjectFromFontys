#include "../include/dashboardController/IDisplay.hpp"
using namespace ActuatorsAndSensor;

// Implement the methods defined in IDashboardInterface as needed
void IDisplay::displaySpeed(String value)
{
    lcd.setCursor(1, 1);
    lcd.print(value);
}

void IDisplay::displayConnectionError(String error_message)
{
    // Implement displayConnectionError
    // set cursor to first column, first row
    lcd.setCursor(2, 0);
    lcd.print(error_message);
}

void IDisplay::displayAlert(String danger_notice)
{
    // set cursor to first column, first row
    lcd.setCursor(2, 0);
    lcd.print(danger_notice);
}

void IDisplay::clearLCD()
{
    lcd.clear();
}