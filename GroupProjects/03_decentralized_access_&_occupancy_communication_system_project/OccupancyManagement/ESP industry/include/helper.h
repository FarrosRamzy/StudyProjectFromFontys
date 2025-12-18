#ifndef _HELPER_H
#define _HELPER_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "EspMQTTClient.h"

//SIOUX: No need to make a main.h, it's extra work for the pre-processor and you're not providing anything to other files
// and potentially exposing a lot of global variables and free functions to other files that include main.h

const char *mqtt_topic_global_counter = "group4Industry/counter"; 
const char *mqtt_topic_emergency ="group4Industry/emergency";
const char *password = "aquamagic22";
const char *name = "Kiwy";


//Variables needed to be changed based on the gate you use
//--------------------------------------------
const char *mqtt_topic_counter = "group4Industry/counter1";
const char *mqtt_gate = "CommGroup4-Gate1";
const char *mqtt_topic = "group4Industry/esp1";
const char *mqtt_topic_receiver = "group4Industry/esp2"; //If uploding to gate 2, write 1
const char *broker_ip = "192.168.117.23";
//--------------------------------------------

//client structure for connection
EspMQTTClient client
(
  name,
  password,
  broker_ip,
  "",
  "",
  mqtt_gate,
  1883
);

// constants
#define LED_RED_PIN 12
#define LED_WHITE_PIN 14
#define SERVOPIN 25
#define EMERGENCYBUTTON 27
#define ENTERBUTTON 26
#define EXITBUTTON 33
#define CONNECTION_LED 2

Servo servo;

// Variables
int pos = 90; // variable to store the servo position
int emergency = HIGH;
const long buttonDebounceDelay = 100; // the debounce time; increase if the output flickers

// declare your functions
void setupGate();
void EntranceButton();
void EmergencyButton();
void ExitButton();
void HandleButtons();
void HandleGate();
void onConnectionEstablished();
void setupConnection();
void HandleConnection();
void HandleResetGate();
void sendQueueLenght();
void HandleQueueManagment();
void sendFastestQueue();
void HandleWorkingGates();

#endif