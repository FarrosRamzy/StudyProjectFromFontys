#include <room_system.h>

void setupCJMCUMeasure()
{
    Wire.beginTransmission(CJMCU_ADDRESS);
    Wire.write(CJMCU_MEAS_MODE);
    Wire.write(CJMCU_MEAS_THRESHOLD);
    Wire.endTransmission();
}

void startAppCJMCU()
{
    Wire.beginTransmission(CJMCU_ADDRESS);
    Wire.write(CJMCU_APP_START);
    Wire.endTransmission();
}

void readCJMCUgas(float *voc, float *co2, int16_t *dataReceived)
{
    uint8_t status = getCJMCUStatus();
    if (!checkCJMCUStatus(status))
    {
        *dataReceived = 0;
    }
    else
    {
        *dataReceived = 1;
        getBothValue(voc, co2);
    }
    Serial.println(*dataReceived);
    Serial.println(*voc);
    Serial.println(*co2);
}

uint8_t getCJMCUStatus()
{
    Wire.beginTransmission(CJMCU_ADDRESS);
    Wire.write(CJMCU_STATUS);
    Wire.endTransmission();

    Wire.requestFrom(CJMCU_ADDRESS, 1);
    return Wire.read();
}

bool checkCJMCUStatus(uint8_t status)
{
    if (status == CJMCU_MEAS_IS_READY)
    {
        return true;
    }
    else if (status == CJMCU_FIRM_IS_NOT_LOADED || status == CJMCU_FIRM_IS_BOOTING)
    {
        // start the tvoc app.
        startAppCJMCU();
        // setup the sensor to measure.
        setupCJMCUMeasure();
        return false;
    }
    else
    {
        return false;
    }
}

void getBothValue(float *tvoc, float *co2)
{
    Wire.beginTransmission(CJMCU_ADDRESS);
    Wire.write(CJMCU_ALG_RESULT_DATA);
    Wire.endTransmission();

    Wire.requestFrom(CJMCU_ADDRESS, 4);

    // declare the read data value as a one byte value.
    uint8_t data[4];

    // catching the data.
    for (int i = 0; i < 4; i++)
    {
        data[i] = Wire.read();
    }

    // converting the read data as value.
    *co2 = (((uint16_t)data[0] << 8) | ((uint16_t)data[1]));
    *tvoc = (((uint16_t)data[2] << 8) | ((uint16_t)data[3]));
}
