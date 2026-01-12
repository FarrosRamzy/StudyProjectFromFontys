/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 * @author			: farros ramzy
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "servo.h"
//#include "robot_gpio.h"
//#include "robot_timers.h"
//#include "uart.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef uint16_t DistanceType;
typedef enum {
	INIT, MOVE, STOP, FORWARD, TURN_LEFT, TURN_RIGHT, REVERSE, ROTATE
} RobotState;

typedef enum {
	DIR_NONE,
	DIR_FORWARD,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_STOP,
	DIR_REVERSE,
	DIR_ROTATE
} DirectionType;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern const double kI;
extern const double kP;
extern const double kD;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

extern volatile uint32_t last_capture;
extern volatile uint32_t pulse_width;
extern volatile uint8_t capture_done;
extern volatile uint16_t distance_to_obstacle;
extern volatile uint32_t millis;

extern volatile RobotState robot_state;
extern volatile RobotState last_state;

extern volatile DirectionType current_direction;
extern volatile DirectionType last_direction;

extern float totalDistance;
extern int count;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
DistanceType measure_distance();
double my_pid(double, double);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define DANGER_DISTANCE 10

#define MAX_DISTANCE 200
#define MIN_DISTANCE 0
#define DEFAULT_DISTANCE 11
#define SCALING_FACTOR 58
#define MAX_REVERSE_COUNT 1
#define RANDOM_FACTOR 2

#define MAX_OUTPUT_POWER 200

#define TURN_DURATION 3000
#define STOP_SERVO 1500
#define CLOCKWISE 1436
#define ANTI_CLOCKWISE 1565
#define MAX_TURNING_COUNTER 700
#define MAX_STOP_COUNTER 250
#define MAX_MOVE_BACK_COUNTER 50

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
