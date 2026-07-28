/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 * @author		   : Farros Ramzy (3767353)
 * @date		   : 01-11-2023
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
#define LEFT_ANGLE -90
#define MID_ANGLE 0
#define RIGHT_ANGLE 90

#define NORMAL_RANGE 90
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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Timer2_Init(void);
void Channel3_Init(void);
void Servo_PWM_Config();

void Set_Rotation_Level(int16_t);

void TIM2_IRQHandler(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile int16_t servo_angle = LEFT_ANGLE;
volatile uint8_t servo_state = 0;
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
	Timer2_Init();
	Channel3_Init();
	Servo_PWM_Config();
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */

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
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pins : PA2 PA3 */
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Timer2_Init(void) {
	//Activate Timer 2 in APB register.
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//disable the timer.
	TIM2->CR1 &= ~TIM_CR1_CEN;

	//prescale the system using 16MHz frequency.
	TIM2->PSC = 16 - 1;
	//set the PWM period in 20 ms.
	TIM2->ARR = 20000 - 1;

	//configure NVIC for TIM2 interrupt.
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 0);

	//reset counter of Timer 2 to 0.
	TIM2->CNT &= ~TIM_CNT_CNT;

	//enable the timer.
	TIM2->CR1 |= TIM_CR1_CEN;
}

void Channel3_Init(void) {
	//set enable the compare register of channel 3 in timer 2.
	TIM2->CCER |= TIM_CCER_CC3E;

	//clean bits the channel 3 in timer 2 register.
	TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;

	//set interrupt enable register in channel 3.
	TIM2->DIER |= TIM_DIER_CC3IE;

	//set the PWM in channel 3 of timer 2 as the output compare mode.
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
	//enable the preload.
	TIM2->CCMR2 |= TIM_CCMR2_OC3PE;

	//set output state to 0 in setup.
	servo_state = 0;
}

void Servo_PWM_Config() {
	//enable GPIOA in RCC register.
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//resets the Servo's pin MODE. (PA9)
	GPIOA->MODER &= ~GPIO_MODER_MODER9;
	//resets the Servo's pin OTYPE to 0 as push-pull.
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
	//resets the Servo's pin SPEED.
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;

	//sets the Servo's pin MODE to 0b10 as an alternated output.
	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	//sets the Servo's pin SPEED to medium.
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0;
	//resets the Servo's PUPD register.
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;

	//resets the high alternate function for pin PA9.
	GPIOA->AFR[1] &= ~GPIO_AFRH_AFRH1;
	//activate alternate function 10 to use timer 2 and channel 3 for PA9 in AFRH9.
	GPIOA->AFR[1] |= (0b1010 << GPIO_AFRH_AFRH1_Pos);
}

void TIM2_IRQHandler(void) {
	//read interrupt flag.
	if (TIM2->SR & TIM_SR_CC3IF) {
		//reset the flag.
		TIM2->SR &= ~TIM_SR_CC3IF;

		//using static value for timer tick.
		static uint32_t tick = 0;
		tick++;
		//20 ms * 50 = 1000 ms (change state every 1 sec).
		if (tick >= 50) {
			switch (servo_state) {
			case 0:
				servo_angle = LEFT_ANGLE;
				servo_state = 1;
				break;
			case 1:
				servo_angle = MID_ANGLE;
				servo_state = 2;
				break;
			case 2:
				servo_angle = RIGHT_ANGLE;
				servo_state = 0;
				break;
			default:
				break;
			}
			tick = 0;
			//use angle value.
			Set_Rotation_Level(servo_angle);
		}
	}
}

void Set_Rotation_Level(int16_t angle) {
	int16_t pwm_width = 1500 + (angle * 10);
	TIM2->CCR3 = pwm_width;
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
