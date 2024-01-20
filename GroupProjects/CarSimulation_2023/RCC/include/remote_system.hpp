#pragma once

#define MY_NETWORK_SSID "R@mzy"
#define MY_NETWORK_PASSWORD "yzmar252887!"
#define MY_NETWORK_PORT 1883
#define MY_MQTT_HOST_SERVER "test.mosquitto.org"
#define MY_ID "extruder"

#define LIGHTING_TOPIC "COM3_G4/CAR/LIGHT_SYSTEM"
#define ENGINE_TOPIC "COM3_G4/CAR/ENGINE_SYSTEM"
#define SENSOR_TOPIC "COM3_G4/CAR/SENSOR_SYSTEM"

//remote commands
#define R_BRAKE "BRAKE"
#define R_SPEED_UP "SPEED_UP"
#define R_SPEED_DOWN "SPEED_DOWN"
#define R_HEADLIGHT_ON "HEADLIGHT_ON"
#define R_HEADLIGHT_OFF "HEADLIGHT_OFF"
#define R_TURN_RIGHT "TURN_RIGHT"
#define R_TURN_LEFT "TURN_LEFT"
#define R_GO_STRAIGHT "GO_STRAIGHT"

//message format
#define EMPTY_STRING ""
#define OVERHEAT "OVERHEAT!!"
#define FLAT_TIRE "FLAT TIRE!!"
#define TEMPERATURE_FORMAT(x) ("temp: " + x + " ℃")
#define PRESSURE_FORMAT(x) ("pressure: " + x + "Pa")

#define R_ACK "ACK"

#define COM_DELAY 1000
#define WIFI_CONNECT_TIMEOUT 10000

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

void callback(char *, byte *, unsigned int);
void sortCommandToEngine(String);
void sortCommandToLighting(String);
void speedUpTheCar();
void speedDownTheCar();
void stopTheCar();
void turnOnHeadlights();
void turnOffHeadlights();
void turnLeft();
void turnRight();
void goStraight();

void handleCanMessage();
void showTemperatureVal(String);
void showTemperatureCaution();
void showPressureVal(String);
void showPressureCaution();