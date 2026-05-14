/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 * 
 * Written by	   : Farros Ramzy (3767353)
 * Assignment	   : 3 A Embedded System
 * Date			   : 24/09/2023
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
#include <stdio.h>
#include <string.h>

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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void LEDsetup();
void ButtonSetup();

void SysConfig_Enabler();
void EXTI_Config();

//void EXTI8_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void Btn_A_Intrpt_Handler(void);
void Btn_B_Intrpt_Handler(void);

void ResetAInterrupt();
void ResetBInterrupt();

void SysTick_Init();
void SysTick_Handler(void);

void ResetLED(GPIO_TypeDef*, uint16_t);
void SwitchLED(GPIO_TypeDef*, uint16_t, uint8_t);

uint16_t ButtonPressed(GPIO_TypeDef*, uint16_t);
uint32_t millis(void);

typedef enum {
	LED_OFF, LED_ON_SHORT_PRESS, LED_OFF_LONG_PRESS
} LED_State;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t millis_counter = 0;

volatile uint32_t interrupt_a_duration = 0;
volatile uint32_t interrupt_b_duration = 0;

volatile uint32_t btn_a_rising_start = 0;
volatile uint32_t btn_a_falling_start = 0;

volatile uint32_t btn_b_rising_start = 0;
volatile uint32_t btn_b_falling_start = 0;

volatile LED_State led_a_state = LED_OFF;
volatile LED_State led_b_state = LED_OFF;

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
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */
	ResetLED(GPIOB, GPIO_PIN_1);
	ResetLED(GPIOB, GPIO_PIN_2);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
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
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1
			| RCC_PERIPHCLK_USART3;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 38400;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

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

	//resets both the LEDs' pin MODE.
	GPIOB->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2);
	//resets both LEDs' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2);
	//resets both LEDs' pin SPEED.
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2);
	//sets both LEDs' pin MODE to 01 as an output.
	GPIOB->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0);
	//sets both LEDs' pin SPEED to medium.
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR2_0);
	//resets both LEDs' PUPD register.
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2);
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

	//set the rising trigger.
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
 * @brief Interrupt A timer reset.
 * 
 * @note reset the counter timer of the duration, rising, and falling trigger to 0.
 * 
 */
void ResetAInterrupt() {
	interrupt_a_duration = 0;
	btn_a_rising_start = 0;
	btn_a_falling_start = 0;
}

/**
 * @brief Interrupt B timer reset.
 * 
 * @note reset the counter timer of the duration, rising, and falling trigger to 0.
 * 
 */
void ResetBInterrupt() {
	interrupt_b_duration = 0;
	btn_b_rising_start = 0;
	btn_b_falling_start = 0;
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
			btn_a_rising_start = millis();
			EXTI->RTSR &= ~EXTI_RTSR_TR8;
			EXTI->FTSR |= EXTI_FTSR_TR8;
		} else {
			btn_a_falling_start = millis();
			EXTI->FTSR &= ~EXTI_FTSR_TR8;
			EXTI->RTSR |= EXTI_RTSR_TR8;

			if (btn_a_falling_start > btn_a_rising_start) {
				interrupt_a_duration = btn_a_falling_start - btn_a_rising_start;
			} else {
				ResetAInterrupt();
			}

			if ((interrupt_a_duration) >= MIN_SHORT_DELAY) {
				Btn_A_Intrpt_Handler();
			}
		}

		EXTI->PR |= EXTI_PR_PR8; //reset the pending register.
	}

	if ((EXTI->PR & EXTI_PR_PR9)) {
		if (ButtonPressed(GPIOA, GPIO_PIN_9) == SET) {
			btn_b_rising_start = millis();
			EXTI->RTSR &= ~EXTI_RTSR_TR9;
			EXTI->FTSR |= EXTI_FTSR_TR9;
		} else {
			btn_b_falling_start = millis();
			EXTI->FTSR &= ~EXTI_FTSR_TR9;
			EXTI->RTSR |= EXTI_RTSR_TR9;

			if (btn_b_falling_start > btn_b_rising_start) {
				interrupt_b_duration = btn_b_falling_start - btn_b_rising_start;
			} else {
				ResetBInterrupt();
			}

			if ((interrupt_b_duration) >= MIN_SHORT_DELAY) {
				Btn_B_Intrpt_Handler();
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
void Btn_A_Intrpt_Handler(void) {
	switch (led_a_state) {
	case LED_OFF:
		if (interrupt_a_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, SET);
			led_a_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			led_a_state = LED_OFF;
		}
		break;
	case LED_ON_SHORT_PRESS:
		if (interrupt_a_duration > MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, RESET);
			led_a_state = LED_OFF_LONG_PRESS;
		} else {
			//do not change state.
			led_a_state = LED_ON_SHORT_PRESS;
		}
		break;
	case LED_OFF_LONG_PRESS:
		if (interrupt_a_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_1, SET);
			led_a_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			led_a_state = LED_OFF_LONG_PRESS;
		}
		break;
	}
	ResetAInterrupt();
}

/**
 * @brief Interrupt Handler for the second button.
 * 
 * @note This function reads the interrupt signal from the second button and switch the
 *       second LED state that was designed with an enum, based on the time length of the
 * 		 button's time length.
 * 
 */
void Btn_B_Intrpt_Handler(void) {
	switch (led_b_state) {
	case LED_OFF:
		if (interrupt_b_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_2, SET);
			led_b_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			led_b_state = LED_OFF;
		}
		break;
	case LED_ON_SHORT_PRESS:
		if (interrupt_b_duration > MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_2, RESET);
			led_b_state = LED_OFF_LONG_PRESS;
		} else {
			//do not change state.
			led_b_state = LED_ON_SHORT_PRESS;
		}
		break;
	case LED_OFF_LONG_PRESS:
		if (interrupt_b_duration <= MAX_SHORT_DELAY) {
			SwitchLED(GPIOB, GPIO_PIN_2, SET);
			led_b_state = LED_ON_SHORT_PRESS;
		} else {
			//do not change state.
			led_b_state = LED_OFF_LONG_PRESS;
		}
		break;
	}
	ResetBInterrupt();
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
 * @param PORT The GPIO port address of the LED.
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
