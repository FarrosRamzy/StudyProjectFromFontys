/*
 * my_led_button.c
 *
 *  Created on: Feb 21, 2024
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
 * @note this function is needed to initialize the pins in GPIO A
 * 		 port to be the input.
 * 		 the pins are:
 * 		 - PA8
 * 		 - PA9
 *
 */
void gpio_a_init(void) {
	//resets both button pins' MODE to 00 as an input.
	GPIOA->MODER &= ~((0x3UL << GPIO_MODER_MODER8_Pos)
			| (0x3UL << GPIO_MODER_MODER9_Pos));
	//resets both button pins' SPEED.
	GPIOA->OSPEEDR &= ~((0x3UL << GPIO_MODER_MODER8_Pos)
			| (0x3UL << GPIO_OSPEEDER_OSPEEDR9_Pos));
	//resets both button input PUPD registers.
	GPIOA->PUPDR &= ~((0x3UL << GPIO_PUPDR_PUPDR8_Pos)
			| (0x3UL << GPIO_PUPDR_PUPDR9_Pos));

	//sets both button pins' SPEED to 01 (medium).
	GPIOA->OSPEEDR |= ((0x1UL << GPIO_OSPEEDER_OSPEEDR8_Pos)
			| (0x1UL << GPIO_OSPEEDER_OSPEEDR9_Pos));
	//sets both button input PUPD registers to 01 (pull-down).
	GPIOA->PUPDR |= ((0x2UL << GPIO_PUPDR_PUPDR8_Pos)
			| (0x2UL << GPIO_PUPDR_PUPDR9_Pos));
}

/**
 * @brief GPIO B port initialization
 *
 * @note this function is needed to initialize the pins in GPIO B
 * 		 port as an output.
 * 		 the pins are:
 * 		 - PB1
 * 		 - PB2
 * 		 - PB3
 * 		 - PB4
 * 		 - PB5
 *
 */
void gpio_b_init(void) {
	//resets all the LEDs' pin MODE.
	GPIOB->MODER &= ~((0x3UL << GPIO_MODER_MODER1_Pos)
			| (0x3UL << GPIO_MODER_MODER2_Pos)
			| (0x3UL << GPIO_MODER_MODER3_Pos)
			| (0x3UL << GPIO_MODER_MODER4_Pos)
			| (0x3UL << GPIO_MODER_MODER5_Pos));
	//resets all LEDs' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2
			| GPIO_OTYPER_OT_3 | GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5);
	//resets all LEDs' pin SPEED.
	GPIOB->OSPEEDR &= ~((0x3UL << GPIO_OSPEEDER_OSPEEDR1_Pos)
			| (0x3UL << GPIO_OSPEEDER_OSPEEDR2_Pos)
			| (0x3UL << GPIO_OSPEEDER_OSPEEDR3_Pos)
			| (0x3UL << GPIO_OSPEEDER_OSPEEDR4_Pos)
			| (0x3UL << GPIO_OSPEEDER_OSPEEDR5_Pos));

	//sets the LEDs' pin MODE to 01 as an output.
	GPIOB->MODER |= ((0x1UL << GPIO_MODER_MODER1_Pos)
			| (0x1UL << GPIO_MODER_MODER2_Pos)
			| (0x1UL << GPIO_MODER_MODER3_Pos)
			| (0x1UL << GPIO_MODER_MODER4_Pos)
			| (0x1UL << GPIO_MODER_MODER5_Pos));
	//sets all LEDs' pin SPEED to medium.
	GPIOB->OSPEEDR |= ((0x1UL << GPIO_OSPEEDER_OSPEEDR1_Pos)
			| (0x1UL << GPIO_OSPEEDER_OSPEEDR2_Pos)
			| (0x1UL << GPIO_OSPEEDER_OSPEEDR3_Pos)
			| (0x1UL << GPIO_OSPEEDER_OSPEEDR4_Pos)
			| (0x1UL << GPIO_OSPEEDER_OSPEEDR5_Pos));
	//resets all LEDs' PUPD register.
	GPIOB->PUPDR &= ~((0x3UL << GPIO_PUPDR_PUPDR1_Pos)
			| (0x3UL << GPIO_PUPDR_PUPDR2_Pos)
			| (0x3UL << GPIO_PUPDR_PUPDR3_Pos)
			| (0x3UL << GPIO_PUPDR_PUPDR4_Pos)
			| (0x3UL << GPIO_PUPDR_PUPDR5_Pos));
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

/**
 * @brief Switch sweep mode
 *
 * @note this function is needed to switch the mode of the sweep LEDs,
 * 		 following to its state in each button press.
 *
 * @param SWEEP_STATE: the state input of the sweep mode.
 *
 */
void switch_sweep_state(uint8_t *SWEEP_STATE) {
	switch (*SWEEP_STATE) {
		case 0:
			*SWEEP_STATE = 1;
			break;
		case 1:
			*SWEEP_STATE = 2;
			break;
		case 2:
			*SWEEP_STATE = 0;
			break;
		default:
			break;
	};
}

/**
 * @brief Turn off all sweep LEDs.
 *
 * @note this function is needed to set all sweep LEDs to LOW.
 *
 */
void all_sweep_off(void) {
	set_led(GPIOB, LOW, GPIO_PIN_2);
	set_led(GPIOB, LOW, GPIO_PIN_3);
	set_led(GPIOB, LOW, GPIO_PIN_4);
	set_led(GPIOB, LOW, GPIO_PIN_5);
}

/**
 * @brief Sweep A
 *
 * @note this function runs the sweep LEDs to do a looping sweep per LED.
 *
 * @param COUNTER: the input count number to recognize the sweep position.
 * @param SWEEP_TO_LEFT: the input value to recognize the sweep direction.
 *
 */
void sweep_a(uint8_t *COUNTER, uint8_t *SWEEP_TO_LEFT) {
	if (*SWEEP_TO_LEFT == 1) {
		if (*COUNTER < MAX_SWEEP_COUNTER) {
			set_led(GPIOB, HIGH, GPIO_PIN_2 << *COUNTER);
			HAL_Delay(100);
			set_led(GPIOB, LOW, GPIO_PIN_2 << *COUNTER);
			*COUNTER += 1;
		} else if (*COUNTER == MAX_SWEEP_COUNTER) {
			*SWEEP_TO_LEFT = 0;
		}
	} else if (*SWEEP_TO_LEFT == 0) {
		if (*COUNTER > MIN_SWEEP_COUNTER) {
			set_led(GPIOB, HIGH, GPIO_PIN_2 << *COUNTER);
			HAL_Delay(100);
			set_led(GPIOB, LOW, GPIO_PIN_2 << *COUNTER);
			*COUNTER -= 1;
		} else if (*COUNTER == MIN_SWEEP_COUNTER) {
			*SWEEP_TO_LEFT = 1;
		}
	}
}

/**
 * @brief Sweep B
 *
 * @note This function runs the sweep LEDs to do a smooth looping sweep.
 *
 * @param COUNTER: the input count number to recognize the sweep position.
 * @param ADDER: the input value to shift increase the sweep pin to the
 * 				 correct direction.
 * @param REVERSE: the input value to shift decrease the sweep pin to the
 * 				   correct direction.
 * @param SWEEP_TO_LEFT: the input value to recognize the sweep direction.
 *
 */
void sweep_b(uint8_t *COUNTER, uint8_t *ADDER, uint8_t *REVERSE,
		uint8_t *SWEEP_TO_LEFT) {
	if (*SWEEP_TO_LEFT == 1) {
		if (*COUNTER <= MAX_SWEEP_COUNTER) {
			set_led(GPIOB, HIGH, GPIO_PIN_2 << *COUNTER);
			*COUNTER += 1;
			*ADDER += 1;
		} else if (*ADDER > MAX_HALF_SWEEP_ADDER && *ADDER < MAX_SWEEP_ADDER) {
			set_led(GPIOB, LOW, GPIO_PIN_2 << *REVERSE);
			*ADDER += 1;
			*REVERSE += 1;
		} else if (*ADDER == MAX_SWEEP_ADDER) {
			*SWEEP_TO_LEFT = 0;
		}
		HAL_Delay(100);
	} else if (*SWEEP_TO_LEFT == 0) {
		if (*COUNTER > MIN_SWEEP_COUNTER) {
			*COUNTER -= 1;
			*ADDER -= 1;
			set_led(GPIOB, HIGH, GPIO_PIN_2 << *COUNTER);
		} else if (*ADDER <= MIN_HALF_SWEEP_ADDER && *ADDER > MIN_SWEEP_ADDER) {
			*ADDER -= 1;
			*REVERSE -= 1;
			set_led(GPIOB, LOW, GPIO_PIN_2 << *REVERSE);
		} else if (*ADDER == MIN_SWEEP_ADDER) {
			*SWEEP_TO_LEFT = 1;
		}
		HAL_Delay(100);
	}
}
