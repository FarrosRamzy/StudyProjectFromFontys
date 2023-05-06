#ifndef WIFI_ESP_H
#define WIFI_ESP_H

#include <Arduino.h>
#include <AltSoftSerial.h>
#include <string.h>

#define SET_WIFI_MODE "AT+CWMODE=3"
#define CHECK_ACC_POINT "AT+CWJAP?"
#define GET_MAC_ADDRESS "AT+CIPSTAMAC?"
#define JOIN_ACC_POINT "AT+CWJAP="
#define CHECK_STATUS "AT+CIPSTATUS"
#define START_COMMUNICATION "AT+CIPSTART="
#define SEND_MESSAGE "AT+CIPSEND="
#define STOP_ECHO "ATE0"

#define TCP "TCP"

#define SSID "MSI_YZMAR"
#define PASSWORD "Yzmar252887"

#define SERVER_IP "192.168.137.1"
#define SERVER_PORT "8888"

#define START_CHAR "#"
#define SPLIT_CHAR "&"
#define PAYLOAD_START_CHAR "{"
#define PAYLOAD_SEPARATOR "|"
#define PAYLOAD_END_CHAR "}"
#define END_CHAR ";"
#define TYPE_TO_TRY "TEMP"
#define MESSAGE_TO_TRY "18.2"

#define SENSOR "SENSOR"
#define UI "UI"
#define APP "APP"

void getDeviceID();
void runWifi();

bool setConnectionMode();
bool checkAccessPoint();
bool joinAccessPoint();
bool checkConnectionStatus();
bool startConnection();
bool sendMessage();

bool setUpWifi();

bool checkATresponse(String);

// void readInputMessage();
// void splitInputLine(String);

#endif