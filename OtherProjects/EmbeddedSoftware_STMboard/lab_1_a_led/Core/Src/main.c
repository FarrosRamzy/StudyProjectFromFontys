/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 *
 * Written by	   : Farros Ramzy (3767353)
 * Assignment	   : 1 Embedded System
 * Date			   : 12/09/2023
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
 * This code contains a basic bit register manipulation for the STM32 MCU.
 * This bit manipulation program starts from using the output pin register
 * to blinks a row of LEDs until using a couple of input pin register to
 * switch the output modes.
 */

//These are just a list of basic register pins that will be required to
//work on the assignment.
//pin MODE register:
/* 00: Input.
 * 01: Output.
 * 10: Alternate.
 * 11: Analog.
 * */

//pin OTYPE register (for output only):
/* 0: Output push-pull.
 * 1: Output open-drain.
 * */

//pin SPEED register:
/* 00: low.
 * 01: medium.
 * 10: low.
 * 11: high.
 * */

//pin PUPD register (important for input, unnecessary for output):
/* 00: No pull-up/pull-down.
 * 01: Pull-up.
 * 10: Pull-down.
 * 11: Reserved.
 * */

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
uint16_t ButtonPressed(GPIO_TypeDef*, uint16_t);
void ToggleOutputMode(GPIO_TypeDef*, uint8_t*, uint16_t);
void ResetLED(GPIO_TypeDef*, uint16_t, GPIO_PinState);
void SweepA(uint8_t*, uint8_t*);
void SweepB(uint8_t*, uint8_t*, uint8_t*, uint8_t*);
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
	//enables port a & b clock registers.
	/* port a: input
	 * port b: output
	 * */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	//button setup:
	/* PA8: button 1
	 * PA9: button 2
	 * */
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

	//LED setup:
	/* PB1: LED 1
	 * PB2: LED 2
	 * PB3: LED 3
	 * PB4: LED 4
	 * PB5: LED 5
	 * */
	//resets all the LEDs' pin MODE.
	GPIOB->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3
			| GPIO_MODER_MODER4 | GPIO_MODER_MODER5);
	//resets all LEDs' pin OTYPE to 0 as push-pull.
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_3
			| GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5);
	//resets all LEDs' pin SPEED.
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR2
			| GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4
			| GPIO_OSPEEDER_OSPEEDR5);
	//sets the LEDs' pin MODE to 01 as an output.
	GPIOB->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0
			| GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0);
	//sets all LEDs' pin SPEED to medium.
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR2_0
			| GPIO_OSPEEDER_OSPEEDR3_0 | GPIO_OSPEEDER_OSPEEDR4_0
			| GPIO_OSPEEDER_OSPEEDR5_0);
	//resets all LEDs' PUPD register.
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3
			| GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5);

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
	/* USER CODE BEGIN 2 */
	//sets the button 1 toggle state.
	uint8_t btn_1_pressed = 0;

	//sets the sweep LED rows' configuration.
	uint8_t led_sweep_type = 0;
	uint8_t sweep_a_to_left = 1;
	uint8_t sweep_b_to_left = 1;

	uint8_t sweep_a_counter = 0;
	uint8_t sweep_b_counter = 0;
	uint8_t sweep_b_adder = 0;
	uint8_t sweep_b_reverse = 0;

	//resets all LEDs to LOW.
	ResetLED(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	ResetLED(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	ResetLED(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	ResetLED(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	ResetLED(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		//Button 1 de-bouncing to toggle the single LED.
		if (ButtonPressed(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
			HAL_Delay(100);
			if (ButtonPressed(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
				ToggleOutputMode(GPIOB, &btn_1_pressed, GPIO_PIN_1);
			}
			while (ButtonPressed(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
				//wait 'till release.
			}
		}

		//Button 2 de-bouncing to switch the sweep mode of the LEDs' row.
		if (ButtonPressed(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {
			HAL_Delay(100);
			if (ButtonPressed(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {
				led_sweep_type ^= 1;
			}
			while (ButtonPressed(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {
				//wait 'till release.
			}
		}

		if (led_sweep_type == 0) {
			SweepA(&sweep_a_counter, &sweep_a_to_left);
		} else {
			SweepB(&sweep_b_counter, &sweep_b_adder, &sweep_b_reverse,
					&sweep_b_to_left);
		}
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
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/**
 * @brief  Read a button press status.
 *
 * @note   This function read an IDR state of an input pin (in this case, a button pin)
 * 		   and compare it to the PIN_RESET to determine the input pull-up or pull-down.
 * 		   This function is needed to trigger the output pins (LEDs) state later on.
 *
 * @param  GPIOx is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  GPIO_Pin specifies the port bit to be written.
 * @retval 0 (pressed) or 1 (released).
 */
uint16_t ButtonPressed(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	uint16_t bitState = 0;
	if ((GPIOx->IDR & GPIO_Pin) != (uint32_t) GPIO_PIN_RESET) {
		bitState = GPIO_PIN_SET;
	} else {
		bitState = GPIO_PIN_RESET;
	}
	return bitState;
}

/**
 * @brief  Toggling the LED output.
 *
 * @note   This function read the state of the input pin (in this case, a button pin)
 * 		   and trigger the output pins (LEDs) state by calling another function, based
 * 		   on the input state.
 *
 * @param  GPIOx is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  btn_state specifies the state of the input button (switched to on or off).
 * @param  led_pin_pos specifies the pin register that would be used in the writing function.
 * @retval none.
 */
void ToggleOutputMode(GPIO_TypeDef *GPIOx, uint8_t *btn_state,
		uint16_t led_pin_pos) {
	if (*btn_state == 0) {
		ResetLED(GPIOx, led_pin_pos, GPIO_PIN_SET);
		*btn_state = 1;
	} else {
		ResetLED(GPIOx, led_pin_pos, GPIO_PIN_RESET);
		*btn_state = 0;
	}
}

/**
 * @brief  Writing the LED output.
 *
 * @note   This function writes the output value of the LEDs digitally (HIGH or LOW).
 *
 * @param  GPIOx is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  led_pin_pos specifies the pin register that would be used in the writing function.
 * @param  state specifies the chosen state of the LED (HIGH or LOW (SET or RESET)).
 * @retval none.
 */
void ResetLED(GPIO_TypeDef *GPIOx, uint16_t led_pin_pos,
		GPIO_PinState state) {
	if (state != GPIO_PIN_RESET) {
		GPIOx->BSRR = (uint32_t) led_pin_pos;
	} else {
		GPIOx->BRR = (uint32_t) led_pin_pos;
	}
}

/**
 * @brief  Sweep LEDs version A.
 *
 * @note   This function read the sweep state input based on the button register pin and sweeps
 * 		   multiple LEDs in a row, both ways, one by one, by using the output writing function.
 *
 * @param  counter is the limit value that the sweep can go (about 1 to 4).
 * @param  sweep_to_left specifies the state of the sweep direction so it can sweep to right and
 * 		   to left in a correct manner.
 * @retval none.
 */
void SweepA(uint8_t *counter, uint8_t *sweep_to_left) {
	if (*sweep_to_left == 1) {
		if (*counter < 4) {
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_SET);
			HAL_Delay(100);
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_RESET);
			*counter += 1;
		} else if (*counter == 4) {
			*sweep_to_left = 0;
		}
	} else if (*sweep_to_left == 0) {
		if (*counter > 0) {
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_SET);
			HAL_Delay(100);
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_RESET);
			*counter -= 1;
		} else if (*counter == 0) {
			*sweep_to_left = 1;
		}
	}
}

/**
 * @brief  Sweep LEDs version B.
 *
 * @note   This function read the sweep state input based on the button register pin and sweeps
 * 		   multiple LEDs in a row to forward and backward by using the output writing function.
 *
 * @param  counter is the limit value that the sweep can go (about 1 to 4).
 * @param  adder is the additional limit value that the sweep can go (maximum to 8) so the row
 * 		   can have all LEDs on, or the otherwise.
 * @param  reverse is the limit value to reverse sweep the row.
 * @param  sweep_to_left specifies the state of the sweep direction so it can sweep to right and
 * 		   to left in a correct manner.
 * @retval none.
 */
void SweepB(uint8_t *counter, uint8_t *adder, uint8_t *reverse,
		uint8_t *sweep_to_left) {
	if (*sweep_to_left == 1) {
		if (*counter <= 3) {
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_SET);
			*counter += 1;
			*adder += 1;
		} else if (*adder > 3 && *adder < 8) {
			ResetLED(GPIOB,
			GPIO_PIN_2 << *reverse, GPIO_PIN_RESET);
			*adder += 1;
			*reverse += 1;
		} else if (*adder == 8) {
			*sweep_to_left = 0;
		}
		HAL_Delay(100);
	} else if (*sweep_to_left == 0) {
		if (*counter > 0) {
			*counter -= 1;
			*adder -= 1;
			ResetLED(GPIOB,
			GPIO_PIN_2 << *counter, GPIO_PIN_SET);
		} else if (*adder <= 4 && *adder > 0) {
			*adder -= 1;
			*reverse -= 1;
			ResetLED(GPIOB,
			GPIO_PIN_2 << *reverse, GPIO_PIN_RESET);
		} else if (*adder == 0) {
			*sweep_to_left = 1;
		}
		HAL_Delay(100);
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
