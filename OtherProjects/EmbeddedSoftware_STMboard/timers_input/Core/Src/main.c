/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 * @author		   : Farros Ramzy (3767353)
 * @date		   : 01-12-2023
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
#include "stdio.h"
#include "string.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TIME_DIVIDER 58
#define PRINT_DELAY 500
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
void myUARTbegin(void);
void printValue(uint32_t);

void SysTick_Init();

void EnableGPIOB(void);
void Echo_Init(void);
void Trigger_Init(void);

void Timer3_Init(void);
void Timer4_Init(void);
void Channel1_Init(void);
void Channel2_Init(void);

void TIM4_IRQHandler(void);
void SysTick_Handler(void);

uint32_t millis(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t edge_val = 0;
volatile uint32_t sensor_pulse = 0;
volatile uint32_t distance_cm = 0;

volatile uint8_t read_state = 0;
volatile uint32_t start_millis = 0;
volatile uint32_t millis_counter = 0;
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
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	myUARTbegin();
	/* USER CODE BEGIN 2 */
	Timer3_Init();
	Timer4_Init();
	Channel1_Init();
	Channel2_Init();

	EnableGPIOB();
	Echo_Init();
	Trigger_Init();

	start_millis = millis();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		if (millis() - start_millis >= PRINT_DELAY) {
			if (read_state == 1) {
				distance_cm = sensor_pulse / TIME_DIVIDER;
				printValue(distance_cm);
				read_state = 0;
			}
			start_millis = millis();
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
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
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
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
 * @brief This function is the setup of the SysTick register.
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
 * @brief This function handles the SysTick interrupt to increase the custom millis value.
 * 
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
	millis_counter++;
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/**
 * @brief This function used to get the millis value.
 * 
 * @return uint32_t 
 */
uint32_t millis(void) {
	return millis_counter;
}

/**
 * @brief This function is a custom GPIO UART initialization.
 * 
 */
void myUARTbegin(void) {
	// Configure GPIO for UART
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure USART2
	__HAL_RCC_USART2_CLK_ENABLE();
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief This function returns the distance value as a printed text in UART terminal
 * 		  communication.
 * 
 * @param distance_val 
 */
void printValue(uint32_t distance_val) {
	char buffer[50];
	sprintf(buffer, "%lu cm\r\n", distance_val);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), 1000);
}

/**
 * @brief This function set-up the Timer 3 of the STM Nucleo for the trigger pin.
 * 
 */
void Timer3_Init(void) {
	//Activate Timer 3 in APB register.
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//Pre-scale the system using 16MHz frequency.
	TIM3->PSC = 16 - 1;
	//set the PWM period to 65ms.
	TIM3->ARR = 65000 - 1;
	//set up the 	
	TIM3->CCR2 = 10;
	//
	TIM3->EGR |= TIM_EGR_UG;
	//enable the timer.
	TIM3->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief 
 * 
 */
void Channel2_Init(void) {
	//
	TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
	//
	TIM3->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	//
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;
	//
	TIM3->CCER &= ~TIM_CCER_CC2P;
	//
	TIM3->CCER |= TIM_CCER_CC2E;
}

/**
 * @brief 
 * 
 */
void Timer4_Init(void) {
	//
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//
	TIM4->PSC = 16 - 1;
	//
	TIM4->ARR = 0xFFFF;
	//
	NVIC_EnableIRQ(TIM4_IRQn);
	//
	NVIC_SetPriority(TIM4_IRQn, 0);
	//
	TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief 
 * 
 */
void Channel1_Init(void) {
	//
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	//
	TIM4->CCER &= ~TIM_CCER_CC1P;
	//
	TIM4->CCER &= ~TIM_CCER_CC1NP;
	//
	TIM4->CCER |= TIM_CCER_CC1E;
	//
	TIM4->DIER |= TIM_DIER_CC1IE;
}

/**
 * @brief 
 * 
 */
void EnableGPIOB(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
}

/**
 * @brief 
 * 
 */
void Echo_Init(void) {
	//resets the sensor's pin MODE. (PB6)
	GPIOB->MODER &= ~GPIO_MODER_MODER6;
	//resets the sensor's pin SPEED.
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	//resets the sensor's PUPD register.
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
	//sets the sensor's pin MODE to 0b10 as an alternated input.
	GPIOB->MODER |= GPIO_MODER_MODER6_1;
	//sets the sensor's pin SPEED to medium.
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
	//set PUPD to pull-down.
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_0;
	//resets the high alternate function for pin PB6.
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
	//activate alternate function 2 (AF2) to use timer 4 on channel 1 PB6
	GPIOB->AFR[0] |= 0b0010 << GPIO_AFRL_AFRL6_Pos;
}

/**
 * @brief 
 * 
 */
void Trigger_Init(void) {
	//resets the sensor's pin MODE. (PB5)
	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	//resets the sensor's pin SPEED.
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	//resets the sensor's PUPD register.
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5;
	//sets the sensor's pin MODE to 0b10 as an alternated output.
	GPIOB->MODER |= GPIO_MODER_MODER5_1;
	//sets the sensor's pin SPEED to medium.
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
	//resets the PUPD register
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5;
	//resets the high alternate function for pin PB5
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL5;
	//activate alternate function 2 (AF2) to use timer 3 on channel 2 PB5
	GPIOB->AFR[0] |= 0b0010 << GPIO_AFRL_AFRL5_Pos;
}

/**
 * @brief 
 * 
 */

void TIM4_IRQHandler(void) {
	if (TIM4->SR & TIM_SR_CC1IF) {
		uint32_t pulse_val = TIM4->CCR1;

		if ((TIM4->CCER & TIM_CCER_CC1P) == 0) {
			edge_val = pulse_val;
			TIM4->CCER |= TIM_CCER_CC1P;
		}
		else {
			if (pulse_val < edge_val) {
				sensor_pulse = (0xFFFF - edge_val) + pulse_val + 1;
			} else {
				sensor_pulse = pulse_val - edge_val;
			}
			read_state = 1;
			TIM4->CCER &= ~TIM_CCER_CC1P;
		}
		TIM4->SR &= ~TIM_SR_CC1IF;
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
