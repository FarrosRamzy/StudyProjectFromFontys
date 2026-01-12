/*
 * robot_uart.c
 *
 *  Created on: Jun 14, 2024
 *      Author: farros ramzy
 */

#include "robot_uart.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

void configure_UART(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	__HAL_RCC_USART2_CLK_ENABLE();
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);
}

void configure_extern_UART(void) {
	// Enable GPIOA clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure USART1 Tx (PA9) and Rx (PA10) pins
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1; // Use AF7 for USART1
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Enable USART1 clock
	__HAL_RCC_USART1_CLK_ENABLE();

	// Configure USART1 settings
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;

	// Initialize USART1
	HAL_UART_Init(&huart1);
}

void UART_send(uint16_t data) {
	char buffer[10];
	sprintf(buffer, "%u\r\n", data);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 1000);
}

void UART_send_double(double data) {
	// Increased buffer size for double
	char buffer[20];
	// Format double with 2 decimal places
	sprintf(buffer, "%.2lf\r\n", data);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 1000);
}

void UART_send_distance_to_extern(DistanceType distance_val) {
	// Increased buffer size for double
	char buffer[20];
	// Format double with 2 decimal places
	sprintf(buffer, "#Distance:%d;\r\n", distance_val);
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 1000);
}

void UART_send_speed_to_extern(double speed_val) {
	// Increased buffer size for double
	char buffer[20];
	// Format double with 2 decimal places
	sprintf(buffer, "#Speed:%.2lf;\r\n", speed_val);
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 1000);
}

void UART_send_direction_to_extern(int state) {
	char buffer[20];
	// Format double with 2 decimal places
	switch (state) {
		case 0:
			sprintf(buffer, "#Forward;\r\n");
			break;
		case 1:
			sprintf(buffer, "#Stop;\r\n");
			break;
		case 2:
			sprintf(buffer, "#Reverse;\r\n");
			break;
		case 3:
			sprintf(buffer, "#Left;\r\n");
			break;
		case 4:
			sprintf(buffer, "#Right;\r\n");
			break;
		case 5:
			sprintf(buffer, "#Rotating;\r\n");
			break;

		default:
			break;
	}
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 1000);
}

