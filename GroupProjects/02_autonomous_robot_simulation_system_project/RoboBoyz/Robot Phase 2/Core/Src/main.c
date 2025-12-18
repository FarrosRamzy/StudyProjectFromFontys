/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define CLOCKWISE 1280
#define STOP 1500
#define COUNTER 1720
#define DEADZONE 12

#define AF10 0b1010
#define AF2 0b0010
#define AF 0b10

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile int32_t distance = 0;
unsigned int seed = 2;

float kP = 4.5;
float kI = 0;
float kD = 1;

char inputChar1[15] = "";
char inputChar2[15] = "";

char output[15] = "";
char testResult[15] = "";
char testOutput[15] = "";
char testReceive[15] = "Hello World\n";

int setObstacleDistance = 10;	//desiredDistance

double robotSpeed;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void Clocks_Init(void);
void Servos_Init(void);
void Echo_Init(void);
void Trigger_Init(void);

void TIM2_Init(void);
void TIM3_Init(void);
void TIM4_Init(void);

void turnRight(void);
void turnLeft(void);

void resetRobot(void);
void stopRobot(void);
void goRobotGo(void);
void reverseRobot(void);

double myPID(double setpoint, double err);
int getDistance(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t start_timer = 0;
uint32_t current_tick = 0;
uint32_t receive_delay = 500;
HAL_StatusTypeDef status1;
HAL_StatusTypeDef status2;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	Clocks_Init();
	Servos_Init();
	Echo_Init();
	Trigger_Init();
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	robotSpeed = 0;
	HAL_UART_Transmit(&huart2, (uint8_t*) testReceive, strlen(testReceive),
			100);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE BEGIN 3 */
		//setting USART1 register to read an input data.
		USART1->ICR |= USART_ICR_ORECF;
		status1 = (HAL_UART_Receive(&huart1, (uint8_t*) inputChar1, 1, 100));
		if (status1 == HAL_OK) {
			status2 = (HAL_UART_Receive(&huart1, (uint8_t*) inputChar2, 1, 100));
		}

		if (status1 == HAL_OK && status2 == HAL_OK) {
			int char1 = atoi(inputChar1);
			int char2 = atoi(inputChar2);
			int result = (char1 * 10) + char2;				//store input char data as the distance result.
			setObstacleDistance = result;
		}

		double measuredDistance = getDistance();

		current_tick = HAL_GetTick(); 						//timer tick for millis with HAL_ functions.
		if (current_tick - start_timer > receive_delay) {
			memset(testOutput, 0, 15);
			sprintf(testOutput, "%d", (int) measuredDistance);
			HAL_UART_Transmit(&huart1, (uint8_t*) testOutput, strlen(testOutput), 0); // send dashboard the current distance to obstacle.
			start_timer = current_tick;
		}
		double error = measuredDistance - setObstacleDistance;
		robotSpeed = myPID((double) setObstacleDistance, error); //read PID value

		/* USER CODE END 3 */
	}
	/* USER CODE END WHILE */
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
			| RCC_PERIPHCLK_USART2;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
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
	huart1.Init.BaudRate = 115200;
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
	huart2.Init.BaudRate = 115200;
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

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

double myPID(double setpoint, double err) {
	static double integral = 0;
	static double prevErr = 0;

	if (err == 0 || err > setpoint) {
		integral = 0;
	} else {
		integral = integral + err;
	}

	double derivative = err - prevErr;
	prevErr = err;

	//PID Controller
	double percentPower = err * kP + integral * kI + derivative * kD;

	//P controller
	//double percentPower = err*kP;

	if (percentPower > 200)	//overloading power
			{
		percentPower = 200;
	}

	if (percentPower > DEADZONE) {
		TIM2->CCR3 = 1480 - percentPower;
		TIM2->CCR4 = 1520 + percentPower;
	} else {
		resetRobot();
	}
	//TODO: remove systick
	return (percentPower / 2);
}

int getDistance() {
	return (TIM4->CCR2) / 58;
}

void Clocks_Init() {
	// enable port A, B & C clocks
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;
}

void Servos_Init() {
	//PA9
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER9)
			| (AF << GPIO_MODER_MODER9_Pos);	//AF10 - TIM2_CH3 D8 PA9
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~GPIO_AFRH_AFRH1)
			| (AF10 << GPIO_AFRH_AFRH1_Pos);

	//PA10
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER10)
			| (AF << GPIO_MODER_MODER10_Pos);	//AF10 - TIM2_CH4 D2 PA10
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~GPIO_AFRH_AFRH2)
			| (AF10 << GPIO_AFRH_AFRH2_Pos);

	TIM2_Init();
}

void TIM2_Init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = 16 - 1;
	TIM2->ARR = 20000;

	TIM2->CCER |= TIM_CCER_CC4E; //enable ch4 cc mode
	TIM2->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE; //set output to toggle on match, Enable pre-load & set PWM mode 1; 110

	TIM2->CCER |= TIM_CCER_CC3E; //enable ch3 cc mode
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;

	TIM2->CR1 |= TIM_CR1_ARPE;	//enable buffer for auto reload pre-load
	TIM2->EGR |= TIM_EGR_UG; //Re-initializes the timer counter and generates an update of the registers
	TIM2->CNT = 0;	//reset counter
	TIM2->CR1 |= TIM_CR1_CEN;	//enable up counter
}

void Echo_Init() {
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER11)
			| (0b10 << GPIO_MODER_MODER11_Pos);	// Set GPIO PA11 to alternate function.
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~GPIO_AFRH_AFRH3)
			| (0b1010 << GPIO_AFRH_AFRH3_Pos);// Select alternate function AF10 (TIM4_CH1)
	TIM4_Init();
}

void TIM4_Init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	TIM4->PSC = 16 - 1;	//16Mhz timer scaled down to 1MHz

	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_CC1S)
			| (0b01 << TIM_CCMR1_CC1S_Pos);	//01: CC1 channel is configured as input, IC1 is mapped on TI1.
	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_IC1PSC);//no prescaler, capture is done each time an edge is detected on the capture input
	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_IC1F);//no filter, sampling is done at fDTS

	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC1NP);
	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC1P);	//00: noninverted/rising edge
	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC1E) | TIM_CCER_CC1E;	//Enable capture/compare 1

	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_CC2S)
			| (0b10 << TIM_CCMR1_CC2S_Pos);	//10: CC2 channel is configured as input, IC2 is mapped on TI1.
	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_IC2PSC);
	TIM4->CCMR1 = (TIM4->CCMR1 & ~TIM_CCMR1_IC2F);

	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC2NP);
	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC2P) | (0b1 << TIM_CCER_CC2P_Pos);//01: inverted/falling edge
	TIM4->CCER = (TIM4->CCER & ~TIM_CCER_CC2E) | TIM_CCER_CC2E;	//Enable capture/compare 2

	TIM4->SMCR = (TIM4->SMCR & ~TIM_SMCR_TS) | (0b101 << TIM_SMCR_TS_Pos);//Filtered Timer Input 1 (TI1FP1)
	TIM4->SMCR = (TIM4->SMCR & ~TIM_SMCR_SMS) | (0b0100 << TIM_SMCR_SMS_Pos);//Reset Mode - Rising edge of the selected trigger input

	TIM4->CR1 = (TIM4->CR1 & ~TIM_CR1_CEN) | TIM_CR1_CEN;//start TIM4 up counter
}

void Trigger_Init() {
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER5)
			| (0b10 << GPIO_MODER_MODER5_Pos);// Set GPIO PB5 to alternate function.
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFRL5)
			| (0b0010 << GPIO_AFRL_AFRL5_Pos);// Select alternate function AF2 (TIM3_CH2)
	TIM3_Init();
}

void TIM3_Init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;		//enable TIM3

	TIM3->PSC = 16 - 1; //Set pre-scaler value to 16
	TIM3->ARR = 0xFFFF; //Set auto reload value to max
	TIM3->CNT = 0;
	TIM3->CCR2 = 10;

	TIM3->CCER = (TIM3->CCER & ~TIM_CCER_CC2E) | TIM_CCER_CC2E;

	TIM3->CCMR1 = (TIM3->CCMR1 & ~TIM_CCMR1_CC2S);
	TIM3->CCMR1 = (TIM3->CCMR1 & ~TIM_CCMR1_OC2M)
			| (0b0110 << TIM_CCMR1_OC2M_Pos); //PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
	TIM3->CCMR1 = (TIM3->CCMR1 & ~TIM_CCMR1_OC2PE) | TIM_CCMR1_OC2PE;

	TIM3->CR1 = (TIM3->CR1 & ~TIM_CR1_CEN) | TIM_CR1_CEN; //Enable timer 3
}

void resetRobot(void) {
	reverseRobot();
	stopRobot();

	if (rand() % 2) {
		turnRight();
	} else {
		turnLeft();
	}

}

void turnRight(void) {
	TIM2->CCR4 = COUNTER;
	TIM2->CCR3 = STOP;
	HAL_Delay(750);
	TIM2->CCR3 = STOP;
}

void turnLeft(void) {
	TIM2->CCR4 = CLOCKWISE;
	TIM2->CCR3 = STOP;
	HAL_Delay(750);
	TIM2->CCR4 = STOP;
}

void stopRobot() {
	TIM2->CCR4 = STOP;
	TIM2->CCR3 = STOP;
}

void goRobotGo() {
	TIM2->CCR4 = COUNTER;		//left wheel
	TIM2->CCR3 = CLOCKWISE;		//right wheel
}

void reverseRobot() {
	TIM2->CCR4 = CLOCKWISE;
	TIM2->CCR3 = COUNTER;
	HAL_Delay(1000);
}

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM17 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM17) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
