/*
 * robot_gpio.c
 *
 *  Created on: Nov 15, 2023
 *      Author: farro
 */

#include "robot_gpio.h"

void EnableGPIOB() {
	//enable GPIOB in RCC register.
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
}

void Servo_PWM_Config() {
	//resets the Servos' pin MODE. (PB0 & PB1)
	GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
	//resets the Servos' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1);
	//resets the Servos' pin SPEED.
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR1);

	//sets the Servos' pin MODE to 0b10 as an alternated output.
	GPIOB->MODER |= (GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1);
	//sets the Servos' pin SPEED to medium.
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR0_0 | GPIO_OSPEEDER_OSPEEDR1_0);
	//resets the Servos' PUPD register.
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1);

	//resets the high alternate function for pin PB0 & PB1.
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL0 | GPIO_AFRL_AFRL1);
	/*activate alternate function 2 (AF2) to use timer 3 on channel 3 & 4 for PB0
	 & PB1 in AFRL0 & AFRL1.*/
	GPIOB->AFR[0] |= ((0b0010 << GPIO_AFRL_AFRL1_Pos)
			| (0b0010 << GPIO_AFRL_AFRL0_Pos));
}

void Ultrasonic_Trigger_Config() {
	//resets the Servos' pin MODE. (PB3)
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	//resets the Servos' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_3;
	//resets the Servos' pin SPEED.
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;

	//sets the Servos' pin MODE to 0b10 as an alternated output.
	GPIOB->MODER |= GPIO_MODER_MODER3_1;
	//sets the Servos' pin SPEED to medium.
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;
	//resets the Servos' PUPD register.
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR3;

	//resets the high alternate function for pin PB3.
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL3;
	//activate alternate function 1 (AF1) to use timer 2 on channel 2 PB3
	GPIOB->AFR[0] |= 0b0001 << GPIO_AFRL_AFRL3_Pos;
}

void Ultrasonic_Echo_Config() {
	//resets the Servos' pin MODE. (PB6)
	GPIOB->MODER &= ~GPIO_MODER_MODER6;
	//resets the Servos' pin SPEED.
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	//resets the Servos' PUPD register.
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;

	//sets the Servos' pin MODE to 0b10 as an alternated input.
	GPIOB->MODER |= GPIO_MODER_MODER6_1;
	//sets the Servos' pin SPEED to medium.
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
	//set PUPD to pull-down.
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_0;

	//resets the high alternate function for pin PB6.
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
	//activate alternate function 2 (AF2) to use timer 4 on channel 1 PB6
	GPIOB->AFR[0] |= 0b0010 << GPIO_AFRL_AFRL6_Pos;
}

