#pragma once

#define MAX_TEMPERATURE 25
#define MAX_PRESSURE 1031 //for simulation to press the sensor.

//#define MIN_PRESSURE 1029 //in real life situation if a flattire happens.

#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include "../include/myBME280/Headers/customBME280lib.hpp"