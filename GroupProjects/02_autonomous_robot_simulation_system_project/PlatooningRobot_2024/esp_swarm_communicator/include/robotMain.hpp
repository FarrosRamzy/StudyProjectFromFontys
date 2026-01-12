#pragma once

//network data
#define MY_NETWORK_SSID "POWERFLEX"
#define MY_NETWORK_PASSWORD "OURPASSWORD"
#define MY_NETWORK_PORT 1883
#define MY_MQTT_HOST_SERVER "test.mosquitto.org"
#define MY_ID "PLATOON_ROBOT"

//mqtt topic
#define SPEED_TOPIC "PLATOON/SPEED"
#define DIRECTION_TOPIC "PLATOON/DIRECTION"
#define DISTANCE_TOPIC "PLATOON/DISTANCE"
#define DISTANCE_SEND_TOPIC "PLATOON/DISTANCESEND"

//message protocol
#define START_MSG '#'
#define SPLIT_MSG ':'
#define END_MSG ';'

#define SPEED_INDICATOR "Speed"
#define DISTANCE_INDICATOR "Distance"

//millis read delay
#define COM_DELAY 1000
#define WIFI_CONNECT_TIMEOUT 10000

//libraries
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HardwareSerial.h>

//global functions
void readMySerialInput(String);
void processSpeedMessage(String);
void processDirectionMessage(String);
void processDistanceMessage(String);
