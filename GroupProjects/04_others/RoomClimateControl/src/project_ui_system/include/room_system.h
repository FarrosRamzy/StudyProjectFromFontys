#ifndef ROOM_SYSTEM_H
#define ROOM_SYSTEM_H

#include <DHT.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <Nextion.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define DHT_PIN 2

#define CO_PIN A0

#define CO2_TX_PIN 5
#define CO2_RX_PIN 4

#define CJMCU_ADDRESS 0x5A

#define CJMCU_STATUS 0x00
#define CJMCU_MEAS_MODE 0x01
#define CJMCU_MEAS_THRESHOLD 0x10
#define CJMCU_ALG_RESULT_DATA 0x02
#define CJMCU_APP_START 0xF4

#define CJMCU_MEAS_IS_READY 0x98
#define CJMCU_FIRM_IS_NOT_LOADED 0x11
#define CJMCU_FIRM_IS_BOOTING 0x10

#define DHT_TYPE DHT11

#define FAN_PIN_A 12
#define FAN_PIN_B 13
#define FAN_PWM_PIN 11

#define MAX_PROCESS_TIMER 500

#define MAX_CHAR_ARRAY 255

#define CO_GAS_RATIO 0.99
#define CO_V 5

#define NORMAL_TEMPERTAURE 26

#define HIGHEST_HUMIDITY 68
#define NORMAL_HUMIDITY 50

#define TEN_BIT_ANALOG_VAL 1024

#define INPUT_SEGMENT_LIMIT 20

#define WIFI_ID "MSI_YZMAR"
#define WIFI_PASSWORD "Yzmar252887"

#define SERVER_IP "192.168.137.1"
#define SERVER_PORT "8888"

#define SET_WIFI_MODE "AT+CWMODE=3"
#define CHECK_ACC_POINT "AT+CWJAP?"
#define GET_MAC_ADDRESS "AT+CIPSTAMAC?"
#define JOIN_ACC_POINT "AT+CWJAP="
#define CHECK_STATUS "AT+CIPSTATUS"
#define START_COMMUNICATION "AT+CIPSTART="
#define SEND_MESSAGE "AT+CIPSEND="
#define STOP_ECHO "ATE0"

#define TCP "TCP"

#define START_CHAR '#'
#define SPLIT_CHAR '&'
#define PAYLOAD_START_CHAR '{'
#define PAYLOAD_SEPARATOR '|'
#define PAYLOAD_END_CHAR '}'
#define END_CHAR ';'

#define MAIN_SYSTEM_SERVER_ID "VB"

#define SENSOR_DEVICE "SENSOR"
#define UI_DEVICE "UI"
#define APP_DEVICE "APP"

#define TEMPERATURE_TYPE "TMP"
#define HUMIDITY_TYPE "HUM"
#define CARBON_MONOXYDE_TYPE "CO"
#define CARBON_DIOXYDE_TYPE "CO2"
#define ORGANIC_TYPE "VOC"
#define FAN_TYPE "FAN"

#define READ_DATA "READ"
#define WRITE_DATA "WRITE"

enum STATE
{
    IDLE,
    READ_AIR_Q,
    READ_TMP,
    PROCESS,
    SEND
};

void setupTouchsreen();

void setupCJMCUMeasure();
void startAppCJMCU();
uint8_t getCJMCUStatus();
void setupCO2Sensor();
void setupHumidTempSensor();

void setupFanSystem();

void setupEspWifi();

void runWifi(String,String,String,char[]);

void sendMessage(String);

bool readInputMessage(String *, String *, uint32_t *);
bool splitInputLine(String, String *, String *, uint32_t *);
bool identifyInputID(String[], String *, String *, uint32_t *);
bool identifyDevice(String[], String *, String *, uint32_t *);
bool identifyPayload(String[], String *, String *, uint32_t *);
bool identifyPayloadType(String *, String *, String, uint32_t *);

bool identifyTemperaturePayload(String *, String, uint32_t *);
bool identifyFanPayload(String *, String, uint32_t *);

void readTempAndHumid(float *, float *);
void readCarbonMonoxide(float *, int16_t *);
void readCarbonDioxide(float *, int16_t *);
bool checkCJMCUStatus(uint8_t);
void getBothValue(float *, float *);
void readCJMCUgas(float *, float *, int16_t *);

void readTouchInput();
void processGasSensors(float, float, float, int16_t, char[]);
void setManualSpeed(uint32_t *, uint32_t *, char[], bool *);
void adjustFanSpeed(uint32_t, uint32_t *, float, float, char[]);

void readAutoManualState(bool *, uint32_t *, uint32_t *, uint32_t *, String, String, uint32_t);
void setTempBtnChange(void *);

void setFanDirection();
void setFanBtnChange(void *);
void setTempSlide(void *);
void setFanSlide(void *);

void sendTemperatureData(float);
void sendHumidityData(float);
void sendCOData(float, int16_t);
void sendCO2Data(float, int16_t);
void sendVOCData(float, int16_t);
void sendGasStatus(char[]);
void sendFanSpeedValue(uint32_t);

// void sendTempAndHumidData(float, float);
// void sendGasSensorData(int16_t, int16_t, int16_t, float, float, float, char[]);
#endif