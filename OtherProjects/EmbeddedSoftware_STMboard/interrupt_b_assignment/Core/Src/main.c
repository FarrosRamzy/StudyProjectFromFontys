/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 * 
 * Written by	   : Farros Ramzy (3767353)
 * Assignment	   : 3 B Embedded System
 * Date			   : 29/09/2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MIN_SHORT_DELAY 20
#define MAX_SHORT_DELAY 500
#define SWEEP_DELAY 50

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void LEDsetup();
void ButtonSetup();

void SysConfig_Enabler();
void EXTI_Config();

void EXTI9_5_IRQHandler(void);
void Button_1_Interrupt_Handler(void);
void Button_2_Interrupt_Handler(void);

void ResetInterrupt1();
void ResetInterrupt2();

void SysTick_Init();
void SysTick_Handler(void);

void ResetLED(GPIO_TypeDef*, uint16_t);
void SwitchLED(GPIO_TypeDef*, uint16_t, uint8_t);

void SweepA(uint8_t*, uint8_t*);
void SweepB(uint8_t*, uint8_t*, uint8_t*, uint8_t*);

uint16_t ButtonPressed(GPIO_TypeDef*, uint16_t);
uint32_t millis(void);

typedef enum {
	LED_OFF, LED_ON_SHORT_PRESS, LED_OFF_LONG_PRESS
} Single_LED_State;

typedef enum {
	ALL_LED_OFF, SWEEP_A, SWEEP_B
} Sweep_LED_State;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t millis_counter = 0;

volatile uint32_t sweep_start_millis = 0;

volatile uint32_t interrupt_1_duration = 0;
volatile uint32_t interrupt_2_duration = 0;

volatile uint32_t btn_1_rising_start = 0;
volatile uint32_t btn_1_falling_start = 0;

volatile uint32_t btn_2_rising_start = 0;
volatile uint32_t btn_2_falling_start = 0;

volatile uint32_t sweep_flag = 0;

volatile Single_LED_State single_led_state = LED_OFF;
volatile Sweep_LED_State sweep_state = ALL_LED_OFF;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	LEDsetup();
	ButtonSetup();
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	SysTick_Init();

	SysConfig_Enabler();
	EXTI_Config();
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */

	uint8_t sweep_a_to_left = 1;
	uint8_t sweep_b_to_left = 1;

	uint8_t sweep_a_pos = 0;

	uint8_t sweep_b_pos = 0;
	uint8_t sweep_b_reverse = 0;
	uint8_t sweep_b_count = 0;

	uint16_t ALL_LEDS = (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
			| GPIO_PIN_5);

	ResetLED(GPIOB, ALL_LEDS);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		if (sweep_flag == 0) {
			SweepA(&sweep_a_pos, &sweep_a_to_left);
		} else if (sweep_flag == 1) {
			SweepB(&sweep_b_pos, &sweep_b_reverse, &sweep_b_count,
					&sweep_b_to_left);
		}
		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
 * @brief LED setup function.
 * 
 * @note This is a GPIO setup function for the LEDs.
 * 
 */
void LEDsetup() {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//resets all LEDs' pin MODE.
	GPIOB->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3
			| GPIO_MODER_MODER4 | GPIO_MODER_MODER5);
	//resets all LEDs' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_3
			| GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5);
	//resets all LEDs' pin SPEED.
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2
			| GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4
			| GPIO_OSPEEDER_OSPEEDR5);
	//sets all LEDs' pin MODE to 01 as an output.
	GPIOB->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
			| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0);
	//sets all LEDs' pin SPEED to medium.
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR2_0
			| GPIO_OSPEEDER_OSPEEDR3_0 | GPIO_OSPEEDER_OSPEEDR4_0
			| GPIO_OSPEEDER_OSPEEDR5_0);
	//resets all LEDs' PUPD register.
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3
			| GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5);
}

/**
 * @brief Button setup function.
 * 
 * @note This is a GPIO setup function for the input buttons.
 * 
 */
void ButtonSetup() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//resets both button pins' MODE to 00 as an input.
	GPIOA->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
	//resets both button pins' SPEED.
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9);
	//resets both button input PUPD registers.
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
	//sets both button pins' SPEED to 01 (medium).
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR9_0);
	//sets both button input PUPD registers to 01 (pull-down).
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1);
}

/**
 * @brief SysTick Initialization function.
 * 
 * @note This is a SysTick function to initialize the timer register of the ARM4
 * 		 controller of the Nucleo board.
 * 
 */
void SysTick_Init() {
	//resets SysTick control pin to 0.
	SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk;
	//sets up the reload register.
	SysTick->LOAD = 16000 - 1;
	//sets the interrupt priority of SysTick to the least urgent.
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	//resets the SysTick counter value.
	SysTick->VAL &= SysTick_VAL_CURRENT_Msk;
	//sets the SysTick control pin to use the clock source, the interrupt, and enables both of them.
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk
			| SysTick_CTRL_ENABLE_Msk);
}

/**
 * @brief SYSCFG enabler.
 * 
 * @note This is a one line function to enable the SYSCFG register for the external
 *       interrupt.
 * 
 */
void SysConfig_Enabler() {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

/**
 * @brief EXTI configuration.
 * 
 * @note This function is created to setup the eternal interrupt line register. The
 *       line number that is being used for this system is line number 8 & 9, which
 *       are included in the third EXTICR group regirter line.
 * 
 */
void EXTI_Config() {
	//reset the External interrupt's configurator register group per line number.
	SYSCFG->EXTICR[2] &= ~(SYSCFG_EXTICR3_EXTI8 | SYSCFG_EXTICR3_EXTI9);
	//set the necessary EXTICR line using the GPIO port name as position.
	SYSCFG->EXTICR[2] |= (SYSCFG_EXTICR3_EXTI8_PA | SYSCFG_EXTICR3_EXTI9_PA);

	//reset the trigger.
	EXTI->FTSR &= ~(EXTI_FTSR_TR8 | EXTI_FTSR_TR9);
	EXTI->RTSR &= ~(EXTI_RTSR_TR8 | EXTI_RTSR_TR9);

	//set the necessary trigger.
	EXTI->RTSR |= (EXTI_RTSR_TR8 | EXTI_RTSR_TR9);

	//mask the EXTI line.
	EXTI->IMR |= (EXTI_IMR_MR8 | EXTI_IMR_MR9);

	NVIC_SetPriority(EXTI9_5_IRQn, 0);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * @brief SysTick Handler function.
 * 
 * @note This function is created to handle the interrupt tick from the SysTick.
 * 
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */
	millis_counter++;
	/* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/**
 * @brief millis function.
 * 
 * @note This one line function is created to get the volatile value of the SysTick
 *       interrupt.
 * 
 * @return uint32_t the millisecond value from the counter tick.
 */
uint32_t millis(void) {
	return millis_counter;
}

/**
 * @brief Interrupt 1 timer reset.
 * 
 * @note reset the counter timer of the duration, rising, and falling trigger to 0.
 * 
 */
void ResetInterrupt1() {
	interrupt_1_duration = 0;
	btn_1_rising_start = 0;
	btn_1_falling_start = 0;
}

/**
 * @brief Interrupt 2 timer reset.
 * 
 * @note reset the counter timer of the duration, rising, and falling trigger to 0.
 * 
 */
void ResetInterrupt2() {
	interrupt_2_duration = 0;
	btn_2_rising_start = 0;
	btn_2_falling_start = 0;
}

/**
 * @brief EXTI 5 to 9 Handler.
 * 
 * @note This function is an interrupt handler for the EXTI line pin 5 until 9.
 * 
 */
void EXTI9_5_IRQHandler(void) {

	if ((EXTI->PR & EXTI_PR_PR8)) {
		if (ButtonPressed(GPIOA, GPIO_PIN_8) == SET) {
			btn_1_rising_start = millis();
			EXTI->RTSR &= ~EXTI_RTSR_TR8;
			EXTI->FTSR |= EXTI_FTSR_TR8;
		} else {
			btn_1_falling_start = millis();
			EXTI->FTSR &= ~EXTI_FTSR_TR8;
			EXTI->RTSR |= EXTI_RTSR_TR8;

			if (btn_1_falling_start > btn_1_rising_start) {
				interrupt_1_duration = btn_1_falling_start - btn_1_rising_start;
			} else {
				ResetInterrupt1();
			}

			if ((interrupt_1_duration) >= MIN_SHORT_DELAY) {
				Button_1_Interrupt_Handler();
			}
		}

		EXTI->PR |= EXTI_PR_PR8; //reset the pending register.
	}

	if ((EXTI->PR & EXTI_PR_PR9)) {
		if (ButtonPressed(GPIOA, GPIO_PIN_9) == SET) {
			btn_2_rising_start = millis();
			EXTI->RTSR &= ~EXTI_RTSR_TR9;
			EXTI->FTSR |= EXTI_FTSR_TR9;
		} else {
			btn_2_falling_start = millis();
			EXTI->FTSR &= ~EXTI_FTSR_TR9;
			EXTI->RTSR |= EXTI_RTSR_TR9;

			if (btn_2_falling_start > btn_2_rising_start) {
				interrupt_2_duration = btn_2_falling_start - btn_2_rising_start;
			} else {
				ResetInterrupt2();
			}

			if ((interrupt_2_duration) >= MIN_SHORT_DELAY) {
				Button_2_Interrupt_Handler();
			}
		}

		EXTI->PR |= EXTI_PR_PR9; //reset the pending register.
	}
}

/**
 * @brief Interrupt Handler for the first button.
 * 
 * @note This function reads the interrupt signal from the first button and switch the
 *       first LED state that was designed with an enum, based on the time length of the
 * 		 button's time length.
 * 
 */
void Button_1_Interrupt_Handler(void) {
	switch (single_led_state) {
	case LED_OFF:
		if (interrupt_1_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, SET);
			single_led_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			single_led_state = LED_OFF;
		}
		break;
	case LED_ON_SHORT_PRESS:
		if (interrupt_1_duration > MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, RESET);
			single_led_state = LED_OFF_LONG_PRESS;
		} else {
			//do not change state.
			single_led_state = LED_ON_SHORT_PRESS;
		}
		break;
	case LED_OFF_LONG_PRESS:
		if (interrupt_1_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, SET);
			single_led_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			single_led_state = LED_OFF_LONG_PRESS;
		}
		break;
	}
	ResetInterrupt1();
}

/**
 * @brief Interrupt Handler for the second button.
 * 
 * @note This function reads the interrupt signal from the second button and switch the
 *       second LED state that was designed with an enum, based on the time length of the
 * 		 button's time length.
 * 
 */
void Button_2_Interrupt_Handler(void) {
	switch (sweep_state) {
	case LED_OFF:
		if (interrupt_2_duration > MAX_SHORT_DELAY) {
			sweep_state = SWEEP_A;
			sweep_flag = 0;
		} else {
			//do not change state.
			sweep_state = LED_OFF;
		}
		break;
	case SWEEP_A:
		if (interrupt_2_duration <= MAX_SHORT_DELAY) {
			sweep_state = SWEEP_B;
			sweep_flag = 1;
		} else {
			//do not change state.
			sweep_state = SWEEP_A;
		}
		break;
	case SWEEP_B:
		if (interrupt_2_duration > MAX_SHORT_DELAY) {
			sweep_state = SWEEP_A;
			sweep_flag = 0;
		} else {
			//do not change state.
			sweep_state = SWEEP_B;
		}
		break;
	}
	ResetInterrupt2();
}

/**
 * @brief  Read a button press status.
 *
 * @note   This function read an IDR state of an input pin (in this case, a button pin)
 * 		   and compare it to the PIN_RESET to determine the input pull-up or pull-down.
 * 		   This function is needed to trigger the output pins (LEDs) state later on.
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PIN_POS specifies the port bit to be written.
 * @retval uint16_t 0 (pressed) or 1 (released).
 */
uint16_t ButtonPressed(GPIO_TypeDef *PORT, uint16_t PIN_POS) {
	uint16_t bitState = 0;
	if ((PORT->IDR & PIN_POS) != (uint32_t) RESET) {
		bitState = SET;
	} else {
		bitState = RESET;
	}
	return bitState;
}

/**
 * @brief Reset LED function.
 * 
 * @note This function is witten to reset the chosen LED pin on a chosen port.
 * 
 * @param PORT the GPIO port address of the LED.
 * @param PIN_POS The pin number of the LED.
 */
void ResetLED(GPIO_TypeDef *PORT, uint16_t PIN_POS) {
	PORT->BRR = (uint32_t) PIN_POS;
}

/**
 * @brief Switch LED function.
 * 
 * @note This functon is written to set the chosen LED pin on a chosen port to the
 * 		 desired state of the output.
 * 
 * @param PORT The GPIO port address of the LED.
 * @param PIN_POS The pin number of the LED.
 * @param PIN_STATE The desired state for the LED.
 */
void SwitchLED(GPIO_TypeDef *PORT, uint16_t PIN_POS, uint8_t PIN_STATE) {
	if (PIN_STATE != RESET) {
		PORT->BSRR = (uint32_t) PIN_POS;
	} else {
		PORT->BRR = (uint32_t) PIN_POS;
	}
}

/**
 * @brief The sweep A function.
 * 
 * @note This function is single toggling the LEDs' row forward and backward
 * 		 using the bit register manipulation.
 * 
 * @param position The number to indicate which sweep position that the row
 * 				   has currently.
 * @param sweep_to_left A boolean unsigned integer to tell which direction
 * 						that the sweep is going.
 */
void SweepA(uint8_t *position, uint8_t *sweep_to_left) {
	uint32_t current_millis = millis();
	if (current_millis - sweep_start_millis >= SWEEP_DELAY) {
		sweep_start_millis = current_millis;
		SwitchLED(GPIOB, (GPIO_PIN_2 << *position), RESET);
		if (*sweep_to_left == 1) {
			if (*position < 3) {
				*position += 1;
			} else if (*position == 3) {
				*sweep_to_left = 0;
			}
		} else if (*sweep_to_left == 0) {
			if (*position > 0) {
				*position -= 1;
			} else if (*position == 0) {
				*sweep_to_left = 1;
			}
		}
		SwitchLED(GPIOB, (GPIO_PIN_2 << *position), SET);
	}
}

/**
 * @brief The sweep A function.
 * 
 * @note This function is smoothly toggling multiple LEDs in a row to move
 * 		 forward and backward using the bit register manipulation.
 * 
 * @param position The number to set the LED on a row position.
 * @param reverse The counter-number to reset the LED on a row position.
 * @param counter The value to count up and down the sweep process.
 * @param sweep_to_left A boolean unsigned integer to tell which direction
 * 						that the sweep is going.
 */
void SweepB(uint8_t *position, uint8_t *reverse, uint8_t *counter,
		uint8_t *sweep_to_left) {
	uint32_t current_millis = millis();
	if (current_millis - sweep_start_millis >= SWEEP_DELAY) {
		sweep_start_millis = current_millis;
		if (*sweep_to_left == 1) {
			if (*position <= 3) {
				SwitchLED(GPIOB, (GPIO_PIN_2 << *position), SET);
				*position += 1;
				*counter += 1;
			} else if ((*counter > 3) && (*counter < 8)) {
				SwitchLED(GPIOB, (GPIO_PIN_2 << *reverse), RESET);
				*counter += 1;
				*reverse += 1;
			} else if (*counter == 8) {
				*sweep_to_left = 0;
			}
		} else if (*sweep_to_left == 0) {
			if (*position > 0) {
				*position -= 1;
				*counter -= 1;
				SwitchLED(GPIOB, (GPIO_PIN_2 << *position), SET);
			} else if ((*counter <= 4) && (*counter > 0)) {
				*counter -= 1;
				*reverse -= 1;
				SwitchLED(GPIOB, (GPIO_PIN_2 << *reverse), RESET);
			} else if (*counter == 0) {
				*sweep_to_left = 1;
			}
		}
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
