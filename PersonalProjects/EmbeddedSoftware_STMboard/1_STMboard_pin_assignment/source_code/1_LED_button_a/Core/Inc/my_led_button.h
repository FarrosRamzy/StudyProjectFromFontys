/*
 * my_led_button.h
 *
 *  Created on: Feb 20, 2024
 *      Author: farros
 */

#ifndef INC_MY_LED_BUTTON_H_
#define INC_MY_LED_BUTTON_H_

#include "main.h"

typedef enum
{
  LOW,
  HIGH
}MyPinState;

void gpio_port_en(void);
void gpio_a_init(void);
void gpio_b_init(void);

void set_led(GPIO_TypeDef*, uint8_t, uint16_t);
void toggle_output(GPIO_TypeDef*, uint8_t*, uint16_t);
uint16_t button_press(GPIO_TypeDef*, uint16_t);

#endif /* INC_MY_LED_BUTTON_H_ */
