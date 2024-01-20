#pragma once

//device address
#define TEMPER_DEV_ADDR 0X76
#define PRESSURE_DEV_ADDR 0X77 //NOTE - Pressure pin only work if the bme280 connector cutted off manually by a knife.

#define DEV_RESET_ADDR 0XE0
#define DEV_ID_ADDR 0XD0
#define DEV_CTRL_MEAS_ADDR 0XF4
#define DEV_TEMP_MSB_ADDR 0XFA
#define DEV_PRES_MSB_ADDR 0XF7

//device reset value
#define DEV_RESET_VAL 0XB6

//device callibration address
#define TEMP_START_BATCH 0X88
#define PRESS_START_BATCH 0X8E

//device callibration slots
#define TEMP_BATCH_SLOTS 6
#define PRESS_BATCH_SLOTS 18

//device read slots
#define TEMP_READ_SLOTS 3
#define PRESS_READ_SLOTS 3
#define CTRL_READ_SLOTS 1
#define ID_READ_SLOTS 1

//value resolution
#define TEMP_RESOLUTION 0.01
#define PRESS_RESOLUTION 0.01

#include "../include/myBME280/Enums/ctrlMeasureMode.hpp"
#include "../include/myBME280/Enums/ctrlPressSampler.hpp"
#include "../include/myBME280/Enums/ctrlTempSampler.hpp"