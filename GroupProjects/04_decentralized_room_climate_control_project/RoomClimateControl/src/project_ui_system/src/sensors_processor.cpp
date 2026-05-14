#include <room_system.h>

float highTVOC = 400;
float highCO2 = 1500;

float lowTVOC = 100;
float lowCO2 = 600;

void processGasSensors(float coVal, float co2Val, float vocVal, int16_t cjmcuData, char gasStatus[])
{
    if (cjmcuData == 0)
    {
        strcpy(gasStatus, "Error");
    }
    else
    {
        if (vocVal >= highTVOC)
        {
            highTVOC = vocVal;
        }
        if (co2Val >= highCO2)
        {
            highCO2 = co2Val;
        }

        if (coVal > 200)
        {
            strcpy(gasStatus, "Danger");
        }
        else if (highCO2 != 0 || highTVOC != 0)
        {
            if (vocVal >= highTVOC || co2Val >= highCO2)
            {
                strcpy(gasStatus, "Danger");
            }
            else if (vocVal < highTVOC && co2Val < highCO2)
            {
                strcpy(gasStatus, "Normal");
            }
            else if (vocVal < lowTVOC && co2Val < lowCO2)
            {
                highCO2 = 1500;
                highTVOC = 400;
                strcpy(gasStatus, "Clear");
            }
        }
        else
        {
            strcpy(gasStatus, "Clear");
        }
    }
}
