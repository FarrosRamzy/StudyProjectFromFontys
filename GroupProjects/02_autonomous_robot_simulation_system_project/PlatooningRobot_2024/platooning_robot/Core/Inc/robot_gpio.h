/*
 * robot_gpio.h
 *
 *  Created on: Jun 14, 2024
 *      Author: farros ramzy
 */

#ifndef INC_ROBOT_GPIO_H_
#define INC_ROBOT_GPIO_H_

#include "main.h"

void EnableGPIOA(void);
void EnableGPIOB(void);

void Servo_PWM_Config(void);

void Ultrasonic_Trigger_Config(void);
void Ultrasonic_Echo_Config(void);

void Infrared_Config(void);

#endif /* INC_ROBOT_GPIO_H_ */
