#include <Arduino.h>
#include "../include/engineManager/engineManager.hpp"

EngineCanManager engineCanManager;

void setup()
{
    Serial.begin(9600);
    engineCanManager.engineCanManagerSetup();
}

void loop()
{
    engineCanManager.handleCanMessage();
}
