/*
 * robot_uart.h
 *
 *  Created on: Jun 14, 2024
 *      Author: farro
 */

#ifndef INC_ROBOT_UART_H_
#define INC_ROBOT_UART_H_

#include "main.h"

void configure_UART(void);
void configure_extern_UART(void);
void UART_send_distance_to_extern(DistanceType data);
void UART_send_speed_to_extern(double data);
void UART_send_direction_to_extern(int state);
void UART_send(uint16_t data);
void UART_send_double(double data);

#endif /* INC_ROBOT_UART_H_ */
