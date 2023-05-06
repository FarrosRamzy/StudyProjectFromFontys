#ifndef TRIAL_SYSTEM_H
#define TRIAL_SYSTEM_H

#include <Arduino.h>
#include <DHT.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <string.h>

#define DHT_PIN 2

#define FAN_PIN_A 12
#define FAN_PIN_B 13
#define FAN_PWM_PIN 11

#define DHT_TYPE DHT11

#define MAX_PROCESS_TIMER 2000

#define NORMAL_TEMPERTAURE 25

#define HIGHEST_HUMIDITY 60
#define NORMAL_HUMIDITY 45

enum STATE
{
    IDLE,
    READ,
    PROCESS,
    SEND,
};

void setupTouchScreen();
void setupDHTSensor();
void setupFanSystem();

void readTemperatureAndHumidity(float *, float *);

void readAutoManualState(bool *, bool *, uint32_t *, uint32_t *);
void setFanDirection();

void setFanCtrlButtonChange(void *);
void setTempCtrlButtonChange(void *);
void setTempManualSlider(void *);
void setFanManualSlider(void *);

void readTouchInput();
void processFanSpeed(float, float);
void setFanSpeedManually(uint32_t);

void sendTemperatureAndHumidityData(float, float);

#endif