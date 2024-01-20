#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stdio.h"
#include "servo.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "robot_gpio.h"
#include "robot_timers.h"
#include "uart.h"

#define DANGER_DISTANCE 10

#define MAX_DISTANCE 200
#define MIN_DISTANCE 0
#define DEFAULT_DISTANCE 11
#define SCALING_FACTOR 58
#define RANDOM_FACTOR 2

#define MAX_OUTPUT_POWER 200

// Define the data type for distance
typedef uint16_t DistanceType;

extern volatile uint32_t last_capture;
extern volatile uint32_t pulse_width;
extern volatile uint8_t capture_done;
extern volatile uint16_t distance_to_obstacle;
extern volatile uint32_t millis;

extern float totalDistance;
extern int count;

DistanceType measure_distance();
double my_pid(double, double);

void Error_Handler(void);



#ifdef __cplusplus
}
#endif

#endif
