/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 *
 * Written by	   : Farros Ramzy (3767353)
 * Assignment	   : 2 B Embedded System
 * Date			   : 18/09/2023
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
//NOTES:
/**
 * This code contains a basic bit register manipulation for the STM32 MCU
 * with the ARM4 micro-controller, same as the Part A of this project. However,
 * this bit manipulation program meant to blink an LED with a support from the
 * interrupt timer register and a bit handler function from SysTick.
 */
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void SysTick_Init();
void SysTick_LED();
void SysTick_Handler(void);
//void DelayMS(uint32_t);
void ResetLED(GPIO_TypeDef*, uint16_t);
void BlinkLED(GPIO_TypeDef*, uint16_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile int32_t TimeDelay;
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

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	SysTick_Init();
	SysTick_LED();
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	/* USER CODE BEGIN 2 */
	ResetLED(GPIOB, GPIO_PIN_1);
	TimeDelay = 0;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

//		DelayMS(1000);
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
}

/* USER CODE BEGIN 4 */
/**
 * @brief  SysTick Initialization.
 *
 * @note   This function is a SysTick initialization to setup the timer register of the
 * 		   ARM4 controller of the Nucleo board.
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
 * @brief  LED Setup.
 *
 * @note   This function is a GPIO setup function to set the output pin of the Nucleo
 *         board. In this case, the GPIO pin in setup is PB1
 *
 */
void SysTick_LED() {
	//enables the GPIOB clock register.
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//resets the LED's pin MODE to 0.
	GPIOB->MODER &= ~GPIO_MODER_MODER1;
	//resets the LED's pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;
	//resets the LED's pin SPEED.
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR1;
	//sets the LED's pin MODE to 01 as an output.
	GPIOB->MODER |= GPIO_MODER_MODER1_0;
	//sets the LED's pin SPEED to medium.
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0;
	//resets the LED's PUPD register.(since internal pull-up & pull-down is not used)
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR1;
}


/**
 * @brief  SysTick Interrupt Handler.
 *
 * @note   This function is a SysTick interrupt handler to run an interrupt process
 * 		   between the main program in the main loop.
 *
 * @param  none.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */
	TimeDelay++;
	if (TimeDelay == 100) {
		BlinkLED(GPIOB, GPIO_PIN_1);
		TimeDelay = 0;
	}
	/* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/**
 * @brief  Reset LED.
 *
 * @note   This function use the BRR pin of the GPIO Port to set the pin on position
 * 		   PIN_POS to be 0 or LOW.
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PIN_POS specifies the output port bit to be written.
 */
void ResetLED(GPIO_TypeDef *PORT, uint16_t PIN_POS) {
	PORT->BRR = (uint32_t) PIN_POS;
}

/**
 * @brief  Switch LED state.
 *
 * @note   This function use the XOR math with the ODR pin of the GPIO Port on the
 * 		   LED Pin.
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PIN_POS specifies the output port bit to be written.
 */
void BlinkLED(GPIO_TypeDef *PORT, uint16_t PIN_POS) {
	PORT->ODR ^= PIN_POS;
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
