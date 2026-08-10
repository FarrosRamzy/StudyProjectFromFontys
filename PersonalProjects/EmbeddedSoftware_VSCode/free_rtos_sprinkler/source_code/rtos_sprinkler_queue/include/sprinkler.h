#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

// Define the LED pins
#define LED1_PIN 13
#define LED2_PIN 12
#define LED3_PIN 14
#define LED4_PIN 27

#define NR_OF_BLINKS 4
#define NUMBER_OF_LEDS 4

#define INPUT_1 "1"
#define INPUT_2 "2"
#define INPUT_3 "3"
#define INPUT_4 "4"

typedef struct
{
  int pin;
  bool turnOn;
} LedCommand;

extern QueueHandle_t scenarioQueue;

extern int nr_of_leds[NUMBER_OF_LEDS];

// Scenes
#define NUMBER_OF_SCENES 4
#define MAX_SCENE_OPERATION 20

extern String my_scenes[NUMBER_OF_SCENES][MAX_SCENE_OPERATION];
extern int operations[NUMBER_OF_SCENES];

void taskSerialRead(void *parameter);
void taskLEDcontrol(void *parameter);

void taskScenario1(void *parameter);
void taskScenario2(void *parameter);
void taskScenario3(void *parameter);
void taskScenario4(void *parameter);

void executeScenes(String *, int);
void ledOn(int pin);
void ledOff(int pin);