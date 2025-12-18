#include "..\include\myBME280\Headers\MyCustomBME280.hpp"

namespace bmeSensor
{
    MyCustomBME280::MyCustomBME280(uint8_t my_bme_address)
        : my_address(my_bme_address)
    {
        ;
    }

    MyCustomBME280::~MyCustomBME280(){}

    void MyCustomBME280::sensorSetup()
    {
        ctrl_mode = myBMEctrlMeasureMode::BME_NORMAL;
        ctrl_temp = myBMEctrlTempOversample::BME_T_OSR_8;
        ctrl_pres = myBMEctrlPressOversample::BME_P_OSR_8;

        Wire.begin();

        MyCustomBME280::BME280config();
        calculateTemperatureCalibrationValues();
        calculatePressureCalibrationValues();

        MyCustomBME280::BME280ctrlMeasure(ctrl_mode, ctrl_temp, ctrl_pres);
    }

    void MyCustomBME280::sensorLoop()
    {
        calculateTemperatureCalibrationValues();
        calculatePressureCalibrationValues();
    }

    uint8_t MyCustomBME280::BME280getID()
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_ID_ADDR);
        Wire.endTransmission();

        Wire.requestFrom(my_address, ID_READ_SLOTS);

        uint8_t my_id = Wire.read();
        return my_id;
    }

    void MyCustomBME280::BME280config()
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_RESET_ADDR);
        Wire.write(DEV_RESET_VAL);
        Wire.endTransmission(true);
    }

    uint8_t MyCustomBME280::BME280ctrlMeasure()
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_CTRL_MEAS_ADDR);
        Wire.endTransmission(true);

        Wire.requestFrom(my_address, CTRL_READ_SLOTS);
        uint8_t my_ctrl_meas = Wire.read();

        return my_ctrl_meas;
    }

    void MyCustomBME280::BME280ctrlMeasure(uint8_t bit_pattern)
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_CTRL_MEAS_ADDR);
        Wire.write(bit_pattern);
        Wire.endTransmission(true);
    }

    void MyCustomBME280::BME280ctrlMeasure(myBMEctrlMeasureMode mode_osr,
                                           myBMEctrlTempOversample temp_osr,
                                           myBMEctrlPressOversample press_osr)
    {
        uint8_t bit_pattern = static_cast<uint8_t>(temp_osr);
        bit_pattern <<= 3;
        bit_pattern |= static_cast<uint8_t>(press_osr);
        bit_pattern <<= 2;
        bit_pattern |= static_cast<uint8_t>(mode_osr);

        MyCustomBME280::BME280ctrlMeasure(bit_pattern);
    }

    int32_t MyCustomBME280::readTemperature()
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_TEMP_MSB_ADDR);
        Wire.endTransmission(true);

        Wire.requestFrom(my_address, DEV_TEMP_MSB_ADDR);

        uint8_t temperature_msb = Wire.read();
        uint8_t temperature_lsb = Wire.read();
        uint8_t temperature_xlsb = Wire.read();

        int32_t raw_temperature = temperature_msb;
        raw_temperature <<= 8;
        raw_temperature |= temperature_lsb;
        raw_temperature <<= 4;
        raw_temperature |= (temperature_xlsb >> 4);

        return raw_temperature;
    }

    int32_t MyCustomBME280::readPressure()
    {
        Wire.beginTransmission(my_address);
        Wire.write(DEV_PRES_MSB_ADDR);
        Wire.endTransmission(true);

        Wire.requestFrom(my_address, PRESS_READ_SLOTS);

        uint8_t pressure_msb = Wire.read();
        uint8_t pressure_lsb = Wire.read();
        uint8_t pressure_xlsb = Wire.read();

        int32_t raw_pressure = pressure_msb;
        raw_pressure <<= 8;
        raw_pressure |= pressure_lsb;
        raw_pressure <<= 4;
        raw_pressure |= (pressure_xlsb >> 4);

        return raw_pressure;
    }

    int32_t MyCustomBME280::temperatureCalculation(int32_t raw_val, uint16_t dig_1,
                                                   int16_t dig_2, int16_t dig_3,
                                                   int32_t *fine_val)
    {
        int32_t var1, var2;
        var1 = ((((raw_val >> 3) - ((int32_t)dig_1 << 1))) * ((int32_t)dig_2)) >> 11;
        var2 = (((((raw_val >> 4) - ((int32_t)dig_1)) * ((raw_val >> 4) -
                                                         ((int32_t)dig_1))) >>
                 12) *
                ((int32_t)dig_3)) >>
               14;
        *fine_val = var1 + var2;
        return (((*fine_val) * 5) + 128) >> 8;
    }

    uint32_t MyCustomBME280::pressureCalculation(int32_t raw_val, uint16_t dig_1,
                                                 int16_t dig_2, int16_t dig_3, int16_t dig_4,
                                                 int16_t dig_5, int16_t dig_6, int16_t dig_7,
                                                 int16_t dig_8, int16_t dig_9,
                                                 int32_t *fine_val)
    {
        int32_t var1, var2;
        uint32_t press_val;

        var1 = ((*fine_val) >> 1) - (int32_t)64000;
        var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)dig_6);
        var2 = var2 + ((var1 * ((int32_t)dig_5)) << 1);
        var2 = (var2 >> 2) + (((int32_t)dig_4) << 16);
        var1 = (((dig_3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
                ((((int32_t)dig_2) * var1) >> 1)) >>
               18;
        var1 = ((((32768 + var1)) * ((int32_t)dig_1)) >> 15);
        if (var1 == 0)
        {
            return 0; // avoid error of division 0.
        }

        press_val = (((uint32_t)(((int32_t)1048576) - raw_val) - (var2 >> 12))) * 3125;

        if (press_val < 0X80000000)
        {
            press_val = (press_val << 1) / ((uint32_t)var1);
        }
        else
        {
            press_val = (press_val / (uint32_t)var1) * 2;
        }

        var1 = (((int32_t)dig_9) * ((int32_t)(((press_val >> 3) *
                                               (press_val >> 3)) >>
                                              13))) >>
               12;
        var2 = (((int32_t)(press_val >> 2)) * ((int32_t)dig_8)) >> 13;
        press_val = (uint32_t)((int32_t)press_val + ((var1 + var2 + dig_7) >> 4));
        return press_val;
    }

    void MyCustomBME280::calculateTemperatureCalibrationValues()
    {
        Wire.beginTransmission(my_address);
        Wire.write(TEMP_START_BATCH);
        Wire.endTransmission();

        Wire.requestFrom(my_address, TEMP_BATCH_SLOTS);

        uint8_t t1_lsb = Wire.read();
        uint8_t t1_msb = Wire.read();

        uint8_t t2_lsb = Wire.read();
        uint8_t t2_msb = Wire.read();

        uint8_t t3_lsb = Wire.read();
        uint8_t t3_msb = Wire.read();

        dig_t1 = t1_msb << 8;
        dig_t1 |= t1_lsb;

        dig_t2 = t2_msb << 8;
        dig_t2 |= t2_lsb;

        dig_t3 = t3_msb << 8;
        dig_t3 |= t3_lsb;
    }

    void MyCustomBME280::calculatePressureCalibrationValues()
    {
        Wire.beginTransmission(my_address);
        Wire.write(PRESS_START_BATCH);
        Wire.endTransmission();

        Wire.requestFrom(my_address, PRESS_BATCH_SLOTS);

        uint8_t p1_lsb = Wire.read();
        uint8_t p1_msb = Wire.read();

        uint8_t p2_lsb = Wire.read();
        uint8_t p2_msb = Wire.read();

        uint8_t p3_lsb = Wire.read();
        uint8_t p3_msb = Wire.read();

        uint8_t p4_lsb = Wire.read();
        uint8_t p4_msb = Wire.read();

        uint8_t p5_lsb = Wire.read();
        uint8_t p5_msb = Wire.read();

        uint8_t p6_lsb = Wire.read();
        uint8_t p6_msb = Wire.read();

        uint8_t p7_lsb = Wire.read();
        uint8_t p7_msb = Wire.read();

        uint8_t p8_lsb = Wire.read();
        uint8_t p8_msb = Wire.read();

        uint8_t p9_lsb = Wire.read();
        uint8_t p9_msb = Wire.read();

        dig_p1 = p1_msb << 8;
        dig_p1 |= p1_lsb;

        dig_p2 = p2_msb << 8;
        dig_p2 |= p2_lsb;

        dig_p3 = p3_msb << 8;
        dig_p3 |= p3_lsb;

        dig_p4 = p4_msb << 8;
        dig_p4 |= p4_lsb;

        dig_p5 = p5_msb << 8;
        dig_p5 |= p5_lsb;

        dig_p6 = p6_msb << 8;
        dig_p6 |= p6_lsb;

        dig_p7 = p7_msb << 8;
        dig_p7 |= p7_lsb;

        dig_p8 = p8_msb << 8;
        dig_p8 |= p8_lsb;

        dig_p9 = p9_msb << 8;
        dig_p9 |= p9_lsb;
    }

    double MyCustomBME280::getTemperature()
    {
        int32_t raw_temp = MyCustomBME280::readTemperature();
        double value = (TEMP_RESOLUTION)*temperatureCalculation(raw_temp, dig_t1, dig_t2,
                                                                dig_t3, &t_fine);
        return value;
    }

    double MyCustomBME280::getPressure()
    {
        int32_t raw_press = MyCustomBME280::readPressure();
        double value = (PRESS_RESOLUTION)*pressureCalculation(raw_press, dig_p1, dig_p2,
                                                              dig_p3, dig_p4, dig_p5, dig_p6,
                                                              dig_p7, dig_p8, dig_p9, &t_fine);
        return value;
    }
}