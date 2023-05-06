#include <BME280Library.h>

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;

uint8_t dig_H1;
int16_t dig_H2;
uint8_t dig_H3;
int16_t dig_H4;
int16_t dig_H5;
int8_t dig_H6;

int32_t t_fine;

bme_ctrl_hum_osr ctrl_hum;
bme_ctrl_meas_mode ctrl_mode;
bme_ctrl_meas_p_osr ctrl_pres;
bme_ctrl_meas_t_osr ctrl_temp;

void setup()
{
  ctrl_hum = BME_H_OSR_8;
  ctrl_mode = BME_NORMAL;
  ctrl_pres = BME_P_OSR_0;
  ctrl_temp = BME_T_OSR_8;

  Serial.begin(9600);
  Wire.begin();

  // Reset
  BME280_reset();

  // Get Id
  Serial.print("ID: ");
  uint8_t id = BME280_GetID();
  Serial.println(id);

  // Calibration values
  calculateTemperatureCalibrationValues();
  calculateHumidityCalibrationValues();

  // ctrl_hum : should be run or written before the ctrl_meas.
  BME280_ctrl_hum(ctrl_hum);

  // ctrl_meas
  BME280_ctrl_meas(ctrl_mode, ctrl_temp, ctrl_pres);
  // BME280_ctrl_meas(0x83);
}

void loop()
{
  // calibration
  calculateHumidityCalibrationValues();
  calculateTemperatureCalibrationValues();

  // Temperature
  int32_t temperatureRawVal = BME280_ReadTemperature();
  double tempVal = (0.01) * tempCalculation(temperatureRawVal, dig_T1, dig_T2, dig_T3, &t_fine);
  // double tempVal = calculateTemp(temperatureRawVal, dig_T1, dig_T2, dig_T3, &t_fine);

  Serial.print("Calculated Temperature:\t");
  // Serial.println(temperature);
  Serial.println(tempVal);

  delay(1000);

  // Humidity
  int32_t rawHumidityVal = BME280_ReadHumidity();

  // uint32_t humVal = humidityCalculation(rawHumidityVal);
  // double realHumVal = humVal / 1024;
  double realHumVal = calculateHumidity(rawHumidityVal, dig_H1, dig_H2, dig_H3, dig_H4, dig_H5, dig_H6, t_fine);

  Serial.print("Real Humidity:\t");
  Serial.println(realHumVal);

  delay(1000);
}

// Helper/private functions

/**
 * Gets all calibration values from the BME's non-volotile memory and saves them in global variables
 */

/**
 * @brief Get and put the dig_Tn values from the temperature MSB & LSB
 * for calibration.
 *
 */
void calculateTemperatureCalibrationValues()
{
  Wire.beginTransmission(BME280_ADDR);
  Wire.write(BME280_CAL_FIRST_BATCH_START_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(BME280_ADDR, 6);
  uint8_t t1Lsb = Wire.read(); // 0x88
  uint8_t t1Msb = Wire.read(); // 0x89

  uint8_t t2Lsb = Wire.read(); // 0x8A
  uint8_t t2Msb = Wire.read(); // 0x8B

  uint8_t t3Lsb = Wire.read(); // 0x8C
  uint8_t t3Msb = Wire.read(); // 0x8D

  dig_T1 = t1Msb << 8;
  dig_T1 |= t1Lsb;

  dig_T2 = t2Msb << 8;
  dig_T2 |= t2Lsb;

  dig_T3 = t3Msb << 8;
  dig_T3 |= t3Lsb;
}

/**
 * @brief Get and put the dig_Hn values from the Humidity MSB & LSB
 * for calibration.
 */
void calculateHumidityCalibrationValues()
{
  Wire.beginTransmission(BME280_ADDR);
  Wire.write(BME280_CAL_H1_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(BME280_ADDR, 1);

  uint8_t h1 = Wire.read(); // A1

  Wire.beginTransmission(BME280_ADDR);
  Wire.write(BME280_CAL_SECOND_BATCH_START_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(BME280_ADDR, 7);

  uint8_t h2Lsb = Wire.read(); // E1
  uint8_t h2Msb = Wire.read(); // E2

  uint8_t h3 = Wire.read(); // E3

  uint8_t h4Msb = Wire.read(); // E4

  uint8_t h5 = Wire.read(); // E5

  uint8_t h6 = Wire.read(); // E6
  uint8_t h7 = Wire.read(); // E7

  dig_H1 = h1;

  dig_H2 = h2Msb << 8;
  dig_H2 = dig_H2 | h2Lsb;

  dig_H3 = h3;

  dig_H4 = h4Msb << 4;
  uint8_t h4Lsb = h5 & 0x0F;
  dig_H4 = dig_H4 | h4Lsb;

  uint8_t h5Lsb = h5 >> 4;
  uint8_t h5Msb = h6 << 4;

  dig_H5 = h5Lsb | h5Msb;

  dig_H6 = h7;
}