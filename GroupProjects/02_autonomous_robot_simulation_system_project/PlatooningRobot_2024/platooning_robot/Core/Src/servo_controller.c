/*
 * robot_servo.c
 *
 *  Created on: Jun 14, 2024
 *      Author: farros ramzy
 */

#include "servo_controller.h"

void move_forward(double pid_power) {
	TIM3->CCR3 = ANTI_CLOCKWISE + pid_power; //left wheel
	TIM3->CCR4 = CLOCKWISE - pid_power; //right wheel
}

void stop(void) {
	uint16_t stop_counter = 0;
	while (stop_counter < MAX_STOP_COUNTER) {
		TIM3->CCR3 = STOP_SERVO;
		TIM3->CCR4 = STOP_SERVO;
		stop_counter++;
	}
}

void turn_right(double pid_power) {
//	uint16_t turning_counter = 0;
//	while (turning_counter < MAX_TURNING_COUNTER) {
		TIM3->CCR3 = ANTI_CLOCKWISE + pid_power;
		TIM3->CCR4 = ANTI_CLOCKWISE + pid_power;
//		turning_counter++;
//	}
}

void turn_left(double pid_power) {
//	uint16_t turning_counter = 0;
//	while (turning_counter < MAX_TURNING_COUNTER) {
		TIM3->CCR3 = CLOCKWISE - pid_power;
		TIM3->CCR4 = CLOCKWISE - pid_power;
//		turning_counter++;
//	}
}

void move_backward(void) {
	uint16_t reverse_counter = 0;
	while (reverse_counter < MAX_MOVE_BACK_COUNTER) {
		TIM3->CCR3 = CLOCKWISE; //left wheel
		TIM3->CCR4 = ANTI_CLOCKWISE; //right wheel
		reverse_counter++;
	}
}

void rotating(int direction){
	if (direction == 0) {
		TIM3->CCR3 = ANTI_CLOCKWISE; //left wheel
		TIM3->CCR4 = ANTI_CLOCKWISE; //right wheel
	} else {
		TIM3->CCR3 = CLOCKWISE; //left wheel
		TIM3->CCR4 = CLOCKWISE; //right wheel
	}
}
