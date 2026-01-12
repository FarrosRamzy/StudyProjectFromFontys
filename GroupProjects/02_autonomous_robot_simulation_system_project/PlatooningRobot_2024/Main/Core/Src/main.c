/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define FILTER_SIZE 25
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float KP = 1.0f;
float KI = 0.1f;
float KD = 0.0f;
volatile float feedback_value = 0.0f;
float prev_error = 0.0f;
float integral = 0.0f;
float error = 0.0f;
volatile uint32_t last_capture = 0;
volatile uint32_t tCycle = 0;
volatile uint32_t tHigh = 0;
volatile uint32_t tFilter[FILTER_SIZE] = {0};
volatile uint32_t filter_index = 0;
volatile uint32_t filter_sum = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Timer3_Config(void);
void ServoGPIO_Config(void);
void Timer4_Config(void);
void FeedbackGPIO_Config(void);
void myPID(float);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Timer3_Config(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;      // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     // Enable TIM3 clock

    TIM3->CR1 &= ~TIM_CR1_CEN;              // Disable TIM3
    TIM3->PSC = 16 - 1;                     // Prescaler value
    TIM3->ARR = 20000 - 1;                  // Auto-reload value (50 Hz)
    TIM3->CNT = 0;                          // Reset counter

    TIM3->CCMR1 &= ~(TIM_CCMR1_CC2S);       // Clear CC2S bits
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC2M);       // Clear OC2M bits
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC2PE);      // Clear OC2PE bit

    TIM3->CCER |= TIM_CCER_CC2E;            // Enable capture/compare 2 output

    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;  // PWM mode 1
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;         // Enable preload register on TIM3_CCR2

    TIM3->CR1 |= TIM_CR1_CEN;               // Enable TIM3
}

void ServoGPIO_Config(void)
{
    GPIOB->MODER &= ~(GPIO_MODER_MODER5);
    GPIOB->MODER |= GPIO_MODER_MODER5_1;    // Alternate function mode

    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_5);   // Output push-pull

    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR5);
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;  // Low speed

    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR5);   // No pull-up, pull-down

    GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL5;
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL5_Pos);  // AF2 (TIM3_CH2)
}

void Timer4_Config(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;      // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;     // Enable TIM4 clock

    TIM4->CR1 &= ~TIM_CR1_CEN;              // Disable TIM4
    TIM4->PSC = 43;                         // Prescaler value
    TIM4->ARR = 0xFFFF - 1;                 // Auto-reload value
    TIM4->CNT = 0;                          // Reset counter

    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;        // Configure input capture for channel 1
    TIM4->CCER |= TIM_CCER_CC1E;            // Enable capture from input
    TIM4->CCER |= TIM_CCER_CC1P;            // Capture on falling edge
    TIM4->CCER |= TIM_CCER_CC1NP;           // Capture on both edges
    TIM4->CCMR1 &= ~(0xF << TIM_CCMR1_IC1F_Pos); // No filter
    TIM4->DIER |= TIM_DIER_CC1IE;           // Enable interrupt for capture
    NVIC_EnableIRQ(TIM4_IRQn);              // Enable interrupt in NVIC
    TIM4->CR1 |= TIM_CR1_CEN;               // Enable TIM4
}

void FeedbackGPIO_Config(void)
{
    GPIOB->MODER &= ~(GPIO_MODER_MODER6);
    GPIOB->MODER |= GPIO_MODER_MODER6_1;    // Alternate function mode

    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR6);   // No pull-up, pull-down

    GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL6_Pos);  // AF2 (TIM4_CH1)
}

void TIM4_IRQHandler(void)
{
    if (TIM4->SR & TIM_SR_CC1IF)
    {
        uint32_t current_capture = TIM4->CCR1;
        tCycle = current_capture - last_capture;
        last_capture = current_capture;

        if (GPIOB->IDR & GPIO_IDR_6) {
            // Update the filter array with the new high time
            filter_sum -= tFilter[filter_index];  // Subtract the old value from the sum
            tFilter[filter_index] = tCycle;       // Store the new value in the array
            filter_sum += tCycle;                 // Add the new value to the sum

            // Move to the next index in the array
            filter_index = (filter_index + 1) % FILTER_SIZE;
            tHigh = filter_sum / FILTER_SIZE;
        }

        TIM4->SR &= ~TIM_SR_CC1IF;
    }
}

void myPID(float setpoint)
{
    error = setpoint - feedback_value;
    integral += error;
    float dutyCycle = (100.0f * tHigh) / tCycle;

    if (error == 0 || dutyCycle >= setpoint || error > 1000)
    {
        integral = 0;
    }

    float derivative = error - prev_error;
    prev_error = error;
    int power = (int)(error * KP + integral * KI + derivative * KD);

    if (power < 1280)
    {
        power = 1280;
    }
    else if (power > 1720)
    {
        power = 1720;
    }

    TIM3->CCR2 = power;
    HAL_Delay(15);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  Timer3_Config();
  ServoGPIO_Config();
  Timer4_Config();
  FeedbackGPIO_Config();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  UART_receive_setpoint_from_exetern();
    /* USER CODE BEGIN 3 */
    // Setpoint can be adjusted to desired speed control pulse width (e.g., 1500 for stop) (max1280-1480min for clockwise speed) (min1520-1720max for counterclockwise speed)
    myPID(1500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
