#ifndef BME280_LIBRARY_H
#define BME280_LIBRARY_H

#include <Arduino.h>
#include <BitHelper.h>
#include <Wire.h>

#define BME280_ADDR 0x76
#define BME280_RESET_ADDR 0xE0
#define BME280_ID_ADDR 0xD0
#define BME280_CTRL_HUM_ADDR 0xF2
#define BME280_CTRL_MEAS_ADDR 0xF4
#define BME280_TEMP_MSB_ADDR 0xFA
#define BME280_HUM_MSB_ADDR 0xFD

// Calibration registers addresses
#define BME280_CAL_FIRST_BATCH_START_ADDR 0x88
#define BME280_CAL_FIRST_BATCH_END_ADDR 0x8D
#define BME280_CAL_H1_ADDR 0xA1
#define BME280_CAL_SECOND_BATCH_START_ADDR 0xE1
#define BME280_CAL_SECOND_BATCH_END_ADDR 0xE7

// Enums:
// Mode
typedef enum
{
    BME_SLEEP = 0b0,
    BME_FORCED = 0b1,
    BME_NORMAL = 0b11
} bme_ctrl_meas_mode;

// Temperature oversampling
typedef enum
{
    BME_T_OSR_0 = 0b0,
    BME_T_OSR_1 = 0b1,
    BME_T_OSR_2 = 0b10,
    BME_T_OSR_4 = 0b11,
    BME_T_OSR_8 = 0b100,
    BME_T_OSR_16 = 0b101

} bme_ctrl_meas_t_osr;

// Pressure oversampling
typedef enum
{
    BME_P_OSR_0 = 0b0,
    BME_P_OSR_1 = 0b1,
    BME_P_OSR_2 = 0b10,
    BME_P_OSR_4 = 0b11,
    BME_P_OSR_8 = 0b100,
    BME_P_OSR_16 = 0b101
} bme_ctrl_meas_p_osr;

// Humidity oversampling
typedef enum
{
    BME_H_OSR_0 = 0b0,
    BME_H_OSR_1 = 0b1,
    BME_H_OSR_2 = 0b10,
    BME_H_OSR_4 = 0b11,
    BME_H_OSR_8 = 0b100,
    BME_H_OSR_16 = 0b101
} bme_ctrl_hum_osr;

// Function declarations:
uint8_t BME280_GetID();
void BME280_reset();
uint8_t BME280_ctrl_hum();
void BME280_ctrl_hum(uint8_t bitPattern); // TODO: Use enums
void BME280_ctrl_hum(bme_ctrl_hum_osr humidityOsr);
uint8_t BME280_ctrl_meas();
void BME280_ctrl_meas(uint8_t bitPattern); // TODO: Use enums
void BME280_ctrl_meas(bme_ctrl_meas_mode mode, bme_ctrl_meas_t_osr temperatureOsr, bme_ctrl_meas_p_osr pressureOsr);

int32_t BME280_ReadTemperature();
int32_t BME280_ReadHumidity();

// double calculateTemp(int32_t, uint16_t, int16_t, int16_t, int32_t *);
double calculateHumidity(uint32_t, uint8_t, int16_t, uint8_t, int16_t, int16_t, int8_t, int32_t);
int32_t tempCalculation(int32_t, uint16_t, int16_t, int16_t, int32_t *);
// uint32_t humidityCalculation(int32_t, uint8_t, int16_t, uint8_t, int16_t, int16_t, int8_t, int32_t);

// Helper function prototypes
void calculateTemperatureCalibrationValues();
void calculateHumidityCalibrationValues();

// void getCalibrationParams();
// void getFirstBatchCalibrationParams();
// void getSecondBatchCalibrationParams();

#endif