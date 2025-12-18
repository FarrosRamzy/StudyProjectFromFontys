/*
 * robot_timers.c
 *
 *  Created on: Nov 15, 2023
 *      Author: farro
 */

#include "robot_timers.h"

void Timer2_Init(void) {
	// Enable clock for TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Prescaler to divide the clock to 1MHz (assuming a 16MHz clock)
	TIM2->PSC = 15;
	// Max auto-reload value to allow for maximum timer count
	TIM2->ARR = 0xFFFF;

	// Set the compare value for 10μs pulse
	TIM2->CCR2 = 10;

	// Clear output compare mode bits for channel 2
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
	// PWM mode 1
	TIM2->CCMR1 |= (0x6 << TIM_CCMR1_OC2M_Pos);

	// Enable preload for CCR2 to allow CCR2 to be loaded with a new value
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

	// Clear polarity bit to make output active high
	TIM2->CCER &= ~(TIM_CCER_CC2P);
	// Enable output for CH2
	TIM2->CCER |= TIM_CCER_CC2E;

	// Generate an update event to load the prescaler and ARR values
	TIM2->EGR |= TIM_EGR_UG;

	// Start the timer
	TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief setting up Timer 3 for both left & right Servos.
 *
 */
void Timer3_Init(void) {
	//Activate Timer 3 in APB register.
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	//disable the timer.
	TIM3->CR1 &= ~TIM_CR1_CEN;

	//prescale the system using 16MHz frequency.
	TIM3->PSC = 16 - 1;
	//set the PWM period in 20 ms.
	TIM3->ARR = 20000 - 1;

	//reset counter of Timer 2 to 0.
	TIM3->CNT &= ~TIM_CNT_CNT;

	//clean bits the channel 3 in timer 3 register.
	TIM3->CCMR2 &= ~TIM_CCMR2_CC3S;
	TIM3->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM3->CCMR2 &= ~TIM_CCMR2_OC3PE;

	//set enable the compare register of channel 3 in timer 3.
	TIM3->CCER |= TIM_CCER_CC3E;
	//set the PWM in channel 3 of timer 3 as the output compare mode.
	TIM3->CCMR2 |= (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
	//enable the preload.
	TIM3->CCMR2 |= TIM_CCMR2_OC3PE;

	//clean bits the channel 4 in timer 3 register.
	TIM3->CCMR2 &= ~TIM_CCMR2_CC4S;
	TIM3->CCMR2 &= ~TIM_CCMR2_OC4M;
	TIM3->CCMR2 &= ~TIM_CCMR2_OC4PE;

	//set enable the compare register of channel 3 in timer 3.
	TIM3->CCER |= TIM_CCER_CC4E;
	//set the PWM in channel 4 of timer 3 as the output compare mode.
	TIM3->CCMR2 |= (TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2);
	//enable the preload.
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
	//enable the timer.
	TIM3->CR1 |= TIM_CR1_CEN;
}

void Timer4_Init(void) {
	// Enable clock for TIM4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	// Prescaler
	TIM4->PSC = 15;
	// Max auto-reload value
	TIM4->ARR = 0xFFFF;

	// Set channel as input, IC1 is mapped on TI1
	TIM4->CCMR1 |= (1 << TIM_CCMR1_CC1S_Pos);
	TIM4->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	// Enable the capture
	TIM4->CCER |= TIM_CCER_CC1E;

	// Enable the TIM4 interrupt for capture on CH1
	TIM4->DIER |= TIM_DIER_CC1IE;
	NVIC_EnableIRQ(TIM4_IRQn);

	// Start TIM4
	TIM4->CR1 |= TIM_CR1_CEN;
}

