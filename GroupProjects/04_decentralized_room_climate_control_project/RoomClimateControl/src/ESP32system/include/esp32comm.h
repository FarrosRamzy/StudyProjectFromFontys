#ifndef ESP32COMM_H
#define ESP32COMM_H

#include <WiFi.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <stddef.h>

#define SSID "MSI_YZMAR"
#define PASSWORD "Yzmar252887"

#define SERVER_IP "192.168.137.1"
#define SERVER_PORT 8888

#define RX_PIN 25
#define TX_PIN 26

#define INPUT_SEGMENT_LIMIT 20

#define START_CHAR '#'
#define SPLIT_CHAR '&'
#define PAYLOAD_START_CHAR '{'
#define PAYLOAD_SEPARATOR '|'
#define PAYLOAD_END_CHAR '}'
#define END_CHAR ';'

#define TYPE_TO_TRY "TMP"
#define MESSAGE_TO_TRY "18.2"

#define TEMPERATURE_TYPE "TMP"
#define HUMIDITY_TYPE "HUM"
#define CARBON_MONOXYDE_TYPE "CO"
#define CARBON_DIOXYDE_TYPE "CO2"
#define ORGANIC_TYPE "VOC"
#define FAN_TYPE "FAN"

#define MAIN_SYSTEM_SERVER_ID "VB"

#define SENSOR_DEVICE "SENSOR"
#define UI_DEVICE "UI"
#define APP_DEVICE "APP"

#define READ_DATA "READ"
#define WRITE_DATA "WRITE"

void writeMessage(String *);

bool readInputMessage(String *, String *, uint32_t *);
bool splitInputLine(String, String *, String *, uint32_t *);
bool identifyInputID(String[], String *, String *, uint32_t *);
bool identifyDevice(String[], String *, String *, uint32_t *);
bool identifyPayload(String[], String *, String *, uint32_t *);
bool identifyPayloadType(String *, String *, String, uint32_t *);

bool identifyTemperaturePayload(String *, String, uint32_t *);
bool identifyFanPayload(String *, String, uint32_t *);

#endif