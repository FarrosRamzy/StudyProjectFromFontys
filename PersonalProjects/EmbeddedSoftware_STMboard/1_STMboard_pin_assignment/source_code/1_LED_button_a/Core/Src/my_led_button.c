/*
 * my_led_button.c
 *
 *  Created on: Feb 20, 2024
 *      Author: farros
 */

#include "my_led_button.h"

/**
 * @brief GPIO port clock enabler
 *
 * @note this function is needed to set enable the clock registers
 * 		 for GPIO A and B.
 *
 */
void gpio_port_en(void) {
	RCC->AHBENR |= (0x1UL << RCC_AHBENR_GPIOAEN_Pos);
	RCC->AHBENR |= (0x1UL << RCC_AHBENR_GPIOBEN_Pos);
}

/**
 * @brief GPIO A port initialization
 *
 * @note this function is needed to initialize the pin in GPIO A
 * 		 port as an input. (PA8)
 *
 */
void gpio_a_init(void) {
	//resets button's pin MODE to 00 as an input.
	GPIOA->MODER &= ~(0x3UL << GPIO_MODER_MODER8_Pos);
	//resets button's pin SPEED.
	GPIOA->OSPEEDR &= ~(0x3UL << GPIO_MODER_MODER8_Pos);
	//resets button input PUPD register.
	GPIOA->PUPDR &= ~(0x3UL << GPIO_PUPDR_PUPDR8_Pos);

	//sets button's pin SPEED to 01 (medium).
	GPIOA->OSPEEDR |= (0x1UL << GPIO_OSPEEDER_OSPEEDR8_Pos);
	//sets button input's PUPD register to 01 (pull-down).
	GPIOA->PUPDR |= (0x2UL << GPIO_PUPDR_PUPDR8_Pos);
}

/**
 * @brief GPIO B port initialization
 *
 * @note this function is needed to initialize the pin in GPIO B
 * 		 port as an output.(PB1)
 *
 */
void gpio_b_init(void) {
	//resets the LED pin's MODE.
	GPIOB->MODER &= ~(0x3UL << GPIO_MODER_MODER1_Pos);
	//resets the LED pin's OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_1);
	//resets the LED pin's SPEED.
	GPIOB->OSPEEDR &= ~(0x3UL << GPIO_OSPEEDER_OSPEEDR1_Pos);

	//sets the LED pin's MODE to 01 as an output.
	GPIOB->MODER |= (0x1UL << GPIO_MODER_MODER1_Pos);
	//sets the LED pin's SPEED to medium.
	GPIOB->OSPEEDR |= (0x1UL << GPIO_OSPEEDER_OSPEEDR1_Pos);
	//resets the LED's PUPD register.
	GPIOB->PUPDR &= ~(0x3UL << GPIO_PUPDR_PUPDR1_Pos);
}

/**
 * @brief Set LED output
 *
 * @note this function is needed to switch the LED pin to ON
 * 		 or OFF, depends on the requested state.
 *
 * @param PORT: the gpio port of the output LED.
 * @param STATE_REQ: the request state to set/reset the LED.
 * @param PIN: the gpio pin of the output LED.
 *
 */
void set_led(GPIO_TypeDef *PORT, uint8_t STATE_REQ, uint16_t PIN) {
	if (STATE_REQ != LOW) {
		PORT->BSRR = (uint32_t) PIN;
	} else {
		PORT->BRR = (uint32_t) PIN;
	}
}

/**
 * @brief LED's toggle
 *
 * @note this function reads the state of the input button and make an
 * 		 output request to the set_led function.
 *
 * @param PORT: the gpio port of the output LED.
 * @param BTN_STATE: the state of the input button.
 * @param LED_PIN: the gpio pin of the output LED.
 *
 */
void toggle_output(GPIO_TypeDef *PORT, uint8_t *BTN_STATE, uint16_t LED_PIN) {
	if (*BTN_STATE == 0) {
		set_led(PORT, HIGH, LED_PIN);
		*BTN_STATE = 1;
	} else {
		set_led(PORT, LOW, LED_PIN);
		*BTN_STATE = 0;
	}
}

/**
 * @brief Button read
 *
 * @note this function reads the button's state activity and return it to
 * 		 the caller of this function.
 *
 * @param PORT: the gpio port of the input button.
 * @param PIN: the gpio pin of the input button.
 *
 * @retval 0 (button state if released) or 1 (button state if pressed).
 *
 */
uint16_t button_press(GPIO_TypeDef *PORT, uint16_t PIN) {
	uint16_t btn_state = 0;
	if ((PORT->IDR & PIN) != (uint32_t) LOW) {
		btn_state = HIGH;
	} else {
		btn_state = LOW;
	}
	return btn_state;
}
