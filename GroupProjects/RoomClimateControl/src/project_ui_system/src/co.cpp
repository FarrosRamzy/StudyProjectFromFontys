#include <room_system.h>

int readVal;
float gasVal;
float readVoltage;
float ratio;

void readCarbonMonoxide(float *coVal, int16_t *dataReceived)
{
    readVal = analogRead(CO_PIN);
    readVoltage = ((float)readVal / TEN_BIT_ANALOG_VAL) * CO_V;
    gasVal = (CO_V - readVoltage) / readVoltage;
    ratio = gasVal / CO_GAS_RATIO;

    if (ratio < 2 || ratio >= 0.7)
    {
        *dataReceived = 1;
        *coVal = gasVal;
    }
    else
    {
        *dataReceived = 0;
    }
}