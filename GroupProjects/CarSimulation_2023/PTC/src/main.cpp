/**
 * @file main.cpp
 * @author farros ramzy (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>
#include "..\include\PtcManager\PtcManager.hpp"

using namespace myPTC;
myPTC::PtcManager my_ptc_manager(TEMPER_DEV_ADDR); //NOTE - pressure address can only be use if the sensor i2c pin cutted manually by a knife.

const uint32_t read_delay = 1000;
uint32_t start_millis = millis();
uint32_t current_millis;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  my_ptc_manager.myPtcConfig();
}

void loop()
{
  // put your main code here, to run repeatedly:
  current_millis = millis();
  if (current_millis - start_millis >= read_delay)
  {
    my_ptc_manager.myPtcLoop();
    start_millis = current_millis;
  }
}