/*
 * servo_controller.h
 *
 *  Created on: Jun 14, 2024
 *      Author: farros ramzy
 */

#ifndef INC_SERVO_CONTROLLER_H_
#define INC_SERVO_CONTROLLER_H_

#include "main.h"

void move_forward(double);
void move_backward(void);
void turn_right(double);
void turn_left(double);
void rotating(int);
void stop(void);

#endif /* INC_SERVO_CONTROLLER_H_ */
