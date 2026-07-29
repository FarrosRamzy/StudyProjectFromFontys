/*
 * my_led_button.h
 *
 *  Created on: Feb 21, 2024
 *      Author: farros
 */

#ifndef INC_MY_LED_BUTTON_H_
#define INC_MY_LED_BUTTON_H_

#include "main.h"

#define MIN_SWEEP_COUNTER 0
#define MAX_SWEEP_COUNTER 3

#define MIN_SWEEP_ADDER 0
#define MAX_SWEEP_ADDER 8

#define MIN_HALF_SWEEP_ADDER 4
#define MAX_HALF_SWEEP_ADDER 3

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

void switch_sweep_state(uint8_t*);
void all_sweep_off(void);
void sweep_a(uint8_t *, uint8_t *);
void sweep_b(uint8_t *, uint8_t *, uint8_t *,uint8_t *);
uint16_t button_press(GPIO_TypeDef*, uint16_t);

#endif /* INC_MY_LED_BUTTON_H_ */
