#ifndef ROBOT_MAIN_HPP
#define ROBOT_MAIN_HPP

//network data
#define MY_NETWORK_SSID "R@mzy"
#define MY_NETWORK_PASSWORD "yzmar252887!"
#define MY_NETWORK_PORT 1883
#define MY_MQTT_HOST_SERVER "test.mosquitto.org"
#define MY_ID "SWARM_ROBOT"

//mqtt topic
#define SPEED_TOPIC "SWARM_FR_ISK/SPEED"
#define DIRECTION_TOPIC "SWARM_FR_ISK/DIRECTION"

//message protocol
#define START_MSG '#'
#define SPLIT_MSG ':'
#define END_MSG ';'

#define SPEED_INDICATOR "Speed"

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

#endif