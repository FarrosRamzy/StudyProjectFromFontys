#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

void configure_UART(void);
void configure_extern_UART(void);
void UART_send_speed_to_extern(double data);
void UART_send_direction_to_extern(int state);
void UART_send(uint16_t data);
void UART_send_double(double data);

#endif
