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
#include "robot_gpio.h"
#include "robot_timers.h"
#include "robot_uart.h"
#include "servo_controller.h"
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
const double kI = 0.549378309652703;
const double kP = 0.156755704961953;
const double kD = 0.0904541280843227;

volatile uint32_t last_capture = 0;
volatile uint32_t pulse_width = 0;
volatile uint8_t capture_done = 0;

volatile uint16_t distance_to_obstacle = 0;
volatile uint8_t state_sent = 0;

float totalDistance = 0;
int count = 0;

int turning_direction;

DistanceType filtered_distance = 0;

volatile RobotState robot_state = INIT;

volatile DirectionType current_direction = DIR_NONE;
volatile DirectionType last_direction = DIR_NONE;

uint32_t state_change_millis = 0;
uint32_t robot_loop_millis = 0;
uint8_t reverse_count = 0;

uint32_t stop_interval = 1000;
uint32_t loop_interval = 50;
uint32_t move_backward_interval = 500;
uint32_t rotate_interval = 2500;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	configure_UART();
	configure_extern_UART();

	Timer2_Init();
	Timer3_Init();
	Timer4_Init();

	EnableGPIOA();
	EnableGPIOB();

	Ultrasonic_Trigger_Config();
	Ultrasonic_Echo_Config();

	Servo_PWM_Config();
	Infrared_Config();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */
		uint32_t currentMillis = millis;
		DistanceType distance = measure_distance();

		if (distance != DEFAULT_DISTANCE) {
			filtered_distance = distance;
			UART_send_distance_to_extern(filtered_distance);
		}

		if (currentMillis - robot_loop_millis >= loop_interval) {

			robot_loop_millis = currentMillis;

			uint16_t sensor_leftmost = (GPIOA->IDR & GPIO_IDR_0) ? 1 : 0;
			uint16_t sensor_left = (GPIOA->IDR & GPIO_IDR_1) ? 1 : 0;
			uint16_t sensor_center = (GPIOA->IDR & GPIO_IDR_4) ? 1 : 0;
			uint16_t sensor_right = (GPIOA->IDR & GPIO_IDR_6) ? 1 : 0;
			uint16_t sensor_rightmost = (GPIOA->IDR & GPIO_IDR_7) ? 1 : 0;

			switch (robot_state) {
			case INIT:
				// Initialization code here
				robot_state = MOVE;
				break;

			case MOVE:
				// Call my_pid to control the servo based on distance
				double my_pid_output = my_pid(DANGER_DISTANCE,
						filtered_distance);
				UART_send_speed_to_extern(my_pid_output);

				if (filtered_distance <= DANGER_DISTANCE) {
					state_change_millis = currentMillis;
					robot_state = STOP;
				} else if ((sensor_center == 0) && sensor_left && sensor_right
						&& sensor_leftmost && sensor_rightmost) {
					robot_state = FORWARD;
					state_change_millis = currentMillis;
				} else if ((sensor_right == 0 || sensor_rightmost == 0)
						&& sensor_center && sensor_left && sensor_leftmost) {
					robot_state = TURN_RIGHT;
					state_change_millis = currentMillis;
				} else if ((sensor_left == 0 || sensor_leftmost == 0)
						&& sensor_center && sensor_right && sensor_rightmost) {
					robot_state = TURN_LEFT;
					state_change_millis = currentMillis;
				} else if (sensor_leftmost && sensor_left && sensor_center
						&& sensor_right && sensor_rightmost) {
					state_change_millis = currentMillis;
					if (reverse_count < MAX_REVERSE_COUNT) {
						robot_state = REVERSE;
					} else {
						robot_state = ROTATE;
					}
				}
				break;

			case FORWARD:
				move_forward(my_pid_output);
				current_direction = DIR_FORWARD;
				robot_state = MOVE;
				break;

			case TURN_LEFT:
				turn_left(my_pid_output);
				current_direction = DIR_LEFT;
				robot_state = MOVE;
				break;

			case TURN_RIGHT:
				turn_right(my_pid_output);
				current_direction = DIR_RIGHT;
				robot_state = MOVE;
				break;

			case STOP:
				if (filtered_distance > DANGER_DISTANCE
						&& !(sensor_center && sensor_left && sensor_leftmost
								&& sensor_right && sensor_rightmost)) {
					state_change_millis = currentMillis;
					robot_state = MOVE;
				} else {
					stop();
					current_direction = DIR_STOP;
				}
				break;

			case REVERSE:
				if (currentMillis - state_change_millis
						>= move_backward_interval) {
					state_change_millis = currentMillis;
					reverse_count++;
					turning_direction = (rand() % RANDOM_FACTOR);
					robot_state = MOVE;
				} else {
					move_backward(); // Move backward for the duration
					current_direction = DIR_REVERSE;
				}
				break;

			case ROTATE:
				if (currentMillis - state_change_millis >= rotate_interval) {
					state_change_millis = currentMillis;
					reverse_count = 0; // Reset reverse count after rotation
					robot_state = MOVE;
				} else {
					rotating(turning_direction); // Rotate 180 degrees (implement this function to rotate)
					current_direction = DIR_ROTATE;
				}
				break;
			}
			if (current_direction != last_direction) {
				switch (current_direction) {
				case DIR_FORWARD:
					UART_send_direction_to_extern(0); // Send "forward"
					break;
				case DIR_STOP:
					UART_send_direction_to_extern(1); // Send "stop"
					break;
				case DIR_LEFT:
					UART_send_direction_to_extern(3); // Send "left"
					break;
				case DIR_RIGHT:
					UART_send_direction_to_extern(4); // Send "right"
					break;
				case DIR_REVERSE:
					UART_send_direction_to_extern(2); // Send "reverse"
					break;
				case DIR_ROTATE:
					UART_send_direction_to_extern(5); // Send "rotate"
					break;
				default:
					break;
				}
				last_direction = current_direction;
			}
		}

	}
}
/* USER CODE END 3 */

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
DistanceType measure_distance() {
if (capture_done) {
	capture_done = 0;
	DistanceType distance = pulse_width / SCALING_FACTOR;

	// make macros 200, default 11 value
	if (distance > MAX_DISTANCE) {
		// Return a default value
		return DEFAULT_DISTANCE;
	}

	if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
		totalDistance += distance;
		count++;

	}

	// implement better filtering mechanism
	if (count % 2 == 0) {
		distance = totalDistance / 2;
		totalDistance = 0;
		count = 0;
		return distance;

	}
}
// Return a default value if conditions are not met
return DEFAULT_DISTANCE;
}

double my_pid(double obstacle_distance, double measured_distance) {
static double integral_val = 0;
static double prev_error = 0;

// Calculate error as the difference between the obstacle distance and the measured distance
double error_val = measured_distance - obstacle_distance;

if (error_val == 0 || error_val > obstacle_distance) {
	integral_val = 0;
}
// Proportional term
double proportional = error_val * kP;

// Integral term
integral_val += error_val;
integral_val = integral_val * kI;

// Derivative term
double derivative = error_val - prev_error;
derivative = derivative * kD;

prev_error = error_val;

// Total PID output
double pid_output = proportional + derivative + integral_val;
//	UART_send_double(pid_output);
//UART_send_speed_to_extern(pid_output);

if (pid_output > MAX_OUTPUT_POWER) {
	pid_output = MAX_OUTPUT_POWER;
}

return pid_output;
}

void TIM4_IRQHandler(void) {
if (TIM4->SR & TIM_SR_CC1IF) {
	uint32_t captureValue = TIM4->CCR1;
	if ((TIM4->CCER & TIM_CCER_CC1P) == 0) {
		last_capture = captureValue;
		TIM4->CCER |= TIM_CCER_CC1P;
	} else {
		if (captureValue < last_capture) {
			pulse_width = (0xFFFF - last_capture) + captureValue + 1;
		} else {
			pulse_width = captureValue - last_capture;
		}
		capture_done = 1;
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
