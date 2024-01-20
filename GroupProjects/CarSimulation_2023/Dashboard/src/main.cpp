#include "../include/dashboardController/ActuatorsAndSensorManager.hpp"  // Include the header file

using namespace canCommunication;
using namespace ActuatorsAndSensor;

Manager actuatorsAndSensorManager;  // Instantiate an object of the Manager class

void setup()
{
    Serial.begin(9600);
    actuatorsAndSensorManager.ActuatorsAndSensorSetup();
}

void loop()
{
    actuatorsAndSensorManager.loopManager();
}
