#include <BME280Library.h>

/**
 * Get the Id of the BME280
 * @returns The Id of the BME280
 */
uint8_t BME280_GetID()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_ID_ADDR);
    Wire.endTransmission(true);

    Wire.requestFrom(BME280_ADDR, 1);
    uint8_t id = Wire.read();

    return id;
}

/**
 * Resets the BME's registers to their default values
 */
void BME280_reset()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_RESET_ADDR);
    Wire.write(0xB6); // Constant to reset the BME defined in the datasheets
    Wire.endTransmission(true);
}

/**
 * Gets the ctrl_hum value in the BME's register
 * @returns The current ctrl_hum value of the register
 */
uint8_t BME280_ctrl_hum()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_CTRL_HUM_ADDR);
    Wire.endTransmission(true); // perform a STOP on the bus

    Wire.requestFrom(BME280_ADDR, 1);
    uint8_t ctrl_hum = Wire.read();

    return ctrl_hum;
}

/**
 * Sets the humidity oversampling to the provided oversampling rate
 * @param humidityOsr The oversampling rate for the humidity.
 */
void BME280_ctrl_hum(bme_ctrl_hum_osr humidityOsr)
{
    uint8_t bitPattern = humidityOsr;
    BME280_ctrl_hum(bitPattern);
}

/**
 * Sets the ctrl_hum register value to the provided bit pattern
 * @param bitPattern The bit pattern with which to overwrite the ctrl_hum register
 */
void BME280_ctrl_hum(uint8_t bitPattern)
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_CTRL_HUM_ADDR);
    Wire.write(bitPattern);
    Wire.endTransmission(true);

    uint8_t ctrl_meas = BME280_ctrl_meas();
    BME280_ctrl_meas(ctrl_meas);
}

/**
 * Get the ctrl_meas value of the register
 * @returns The ctrl_meas value in the BME's register
 */
uint8_t BME280_ctrl_meas()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_CTRL_MEAS_ADDR);
    Wire.endTransmission(true);

    Wire.requestFrom(BME280_ADDR, 1);
    uint8_t ctrl_meas = Wire.read();

    return ctrl_meas;
}

/**
 * Sets the ctrl_meas value of the register according to the provided params
 * @param mode The working mode of the sensor: Sleep, Forced or Normal
 * @param temperatureOsr The oversampling rate for the temperature
 * @param pressureOsr The oversampling rate for the pressure
 */
void BME280_ctrl_meas(bme_ctrl_meas_mode mode, bme_ctrl_meas_t_osr temperatureOsr, bme_ctrl_meas_p_osr pressureOsr)
{
    uint8_t bitPattern = temperatureOsr;
    bitPattern <<= 3;
    bitPattern |= pressureOsr;
    bitPattern <<= 2;
    bitPattern |= mode;

    BME280_ctrl_meas(bitPattern);
}

/**
 * Sets the ctrl_meas values of the register according to the provided bit pattern
 * @param bitPattern The bit pattern which to write to the register
 */
void BME280_ctrl_meas(uint8_t bitPattern)
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_CTRL_MEAS_ADDR);
    Wire.write(bitPattern);
    Wire.endTransmission(true);
}

int32_t BME280_ReadTemperature()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_TEMP_MSB_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(BME280_ADDR, 3, true);
    uint8_t temperatureMsb = Wire.read();
    uint8_t temperatureLsb = Wire.read();
    uint8_t temperatureXLsb = Wire.read();

    int32_t temperatureRaw = temperatureMsb;
    temperatureRaw <<= 8;
    temperatureRaw |= temperatureLsb;
    temperatureRaw <<= 4;
    temperatureRaw |= (temperatureXLsb >> 4);

    Serial.println(temperatureRaw, HEX);

    return temperatureRaw;
}

int32_t BME280_ReadHumidity()
{
    Wire.beginTransmission(BME280_ADDR);
    Wire.write(BME280_HUM_MSB_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(BME280_ADDR, 2, true);
    uint8_t humidityMsb = Wire.read();
    uint8_t humidityLsb = Wire.read();

    int32_t rawHumidityVal = humidityMsb;
    rawHumidityVal = rawHumidityVal << 8;
    rawHumidityVal = rawHumidityVal | humidityLsb;

    return rawHumidityVal;
}

// // Helper/private functions

// /**
//  * Gets all calibration values from the BME's non-volotile memory and saves them in global variables
//  */
// void getCalibrationParams()
// {
//     // Temperature calibration data
//     getFirstBatchCalibrationParams();

//     // Get the un-grouped H1 value
//     Wire.beginTransmission(BME280_ADDR);
//     Wire.write(BME280_CAL_H1_ADDR);
//     Wire.endTransmission(true);

//     Wire.requestFrom(BME280_ADDR, 1);
//     // dig_H1 = Wire.read();

//     // Humidity calibration data
//     getSecondBatchCalibrationParams();
// }

// void getFirstBatchCalibrationParams()
// {
//     Wire.beginTransmission(BME280_ADDR);
//     Wire.write(BME280_CAL_FIRST_BATCH_START_ADDR);
//     Wire.endTransmission(true);

//     // Burst read?
//     int bytesToRequest = BME280_CAL_FIRST_BATCH_END_ADDR - BME280_CAL_FIRST_BATCH_START_ADDR + 1;
//     Wire.requestFrom(BME280_ADDR, bytesToRequest);
// }

// void getSecondBatchCalibrationParams()
// {
//     // TODO:
// }

// double calculateTemp(int32_t rawTemp, uint16_t dig_T1, int16_t dig_T2, int16_t dig_T3, int32_t *t_fine)
// {
//     double var1 = (((double)rawTemp) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);

//     double var2 = ((((double)rawTemp) / 131072.0 - ((double)dig_T1) / 8192.0) *
//                   (((double)rawTemp) / 131072.0 - ((double)dig_T1) / 8192.0)) *
//                   ((double)dig_T3);

//     *t_fine = (int32_t)(var1 + var2);

//     double temperartureC = (var1 + var2) / 5120.0;
//     return temperartureC;
// }

int32_t tempCalculation(int32_t rawVal, uint16_t dig_T1, int16_t dig_T2, int16_t dig_T3, int32_t *t_fine)
{
    int32_t var1, var2;
    var1 = ((((rawVal >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((rawVal >> 4) - ((int32_t)dig_T1)) * ((rawVal >> 4) - ((int32_t)dig_T1))) >> 12) *
            ((int32_t)dig_T3)) >>
           14;
    *t_fine = var1 + var2;
    return (((*t_fine) * 5) + 128) >> 8;
}

// uint32_t humidityCalculation(int32_t rawVal, uint8_t dig_H1, int16_t dig_H2, uint8_t dig_H3, int16_t dig_H4, int16_t dig_H5, int8_t dig_H6, int32_t t_fine)
// {
//     int32_t humVar;
//     humVar = (t_fine - ((int32_t)76800));
//     humVar = (((((rawVal << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * humVar)) +
//              ((int32_t)16384)) >> 15) *
//              (((((((humVar * ((int32_t)dig_H6)) >> 10) * (((humVar * ((int32_t)dig_H3)) >> 11) +
//              ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14));
//     humVar = (humVar - (((((humVar >> 15) * (humVar >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
//     humVar = (humVar < 0 ? 0 : humVar);
//     humVar = (humVar > 419430400 ? 419430400 : humVar);
//     return (uint32_t)(humVar >> 12);
// }

double calculateHumidity(uint32_t rawHumid, uint8_t dig_H1, int16_t dig_H2, uint8_t dig_H3, int16_t dig_H4, int16_t dig_H5, int8_t dig_H6, int32_t t_fine)
{
    double humid;

    humid = (((double)t_fine) - 76800.0);
    humid = (rawHumid - (((double)dig_H4) * 64.0 + ((double)dig_H5) / 16384.0 * humid)) *
            (((double)dig_H2) / 65536.0 * (1.0 + ((double)dig_H6) / 67108864.0 * humid * (1.0 + ((double)dig_H3) / 67108864.0 * humid)));
    humid = humid * (1.0 - ((double)dig_H1) * humid / 524288.0);

    if (humid > 100.0)
        humid = 100.0;
    else if (humid < 0.0)
        humid = 0.0;
    return humid;
}
