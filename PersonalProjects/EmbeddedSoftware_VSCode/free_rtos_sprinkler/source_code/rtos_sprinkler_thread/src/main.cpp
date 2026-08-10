/**
 * @file main.cpp
 * @author farros ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "sprinkler.h"

int nr_of_leds[NUMBER_OF_LEDS] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

String my_scenes[NUMBER_OF_SCENES][MAX_SCENE_OPERATION] = {
    {"LED1 on", "LED4 on", "wait 5", "LED1 off", "LED4 off", "wait 5"},
    {"LED2 on", "LED3 on", "wait 5", "LED2 off", "LED3 off", "wait 5"},
    {"LED1 on", "wait 5", "LED3 on", "wait 5", "LED1 off", "wait 5", "LED3 off"},
    {"LED1 on", "LED2 on", "LED3 on", "LED4 on", "wait 5", "LED1 off", "LED2 off", "LED3 off", "LED4 off", "wait 5"},
};

int operations[NUMBER_OF_SCENES] = {6, 6, 7, 10};

void setup()
{
  Serial.begin(9600);

  // Set LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);

  xTaskCreate(taskSerialRead, "SerialRead", 1000, NULL, 1, NULL);
}

void loop()
{
  ;
}

