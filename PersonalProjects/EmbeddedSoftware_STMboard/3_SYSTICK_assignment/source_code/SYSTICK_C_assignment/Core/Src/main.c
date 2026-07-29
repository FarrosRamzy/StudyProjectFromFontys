/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 *
 * Written by	   : Farros Ramzy (3767353)
 * Assignment	   : 2 C Embedded System
 * Date			   : 19/09/2023
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
 * This code contains a basic bit register manipulation for the STM32 MCU & the
 * ARM4. This bit manipulation program is similar with the LED_button_assignment,
 * but with the change of using SysTick on its timer instead of HAL_Delay.
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
void SysTick_Button();
void SysTick_Handler(void);
void DelayMS(uint32_t);
void ResetLED(GPIO_TypeDef*, uint16_t);
void SwitchLED(GPIO_TypeDef*, uint16_t, uint8_t);
uint16_t ButtonPressed(GPIO_TypeDef*, uint16_t);
void ToggleOutputMode(GPIO_TypeDef*, uint8_t*, uint16_t);
void SweepA(uint8_t*, uint8_t*);
void SweepB(uint8_t*, uint8_t*, uint8_t*, uint8_t*);
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
	SysTick_Button();
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	/* USER CODE BEGIN 2 */
	ResetLED(GPIOB, GPIO_PIN_1);
	ResetLED(GPIOB, GPIO_PIN_2);
	ResetLED(GPIOB, GPIO_PIN_3);
	ResetLED(GPIOB, GPIO_PIN_4);
	ResetLED(GPIOB, GPIO_PIN_5);

	TimeDelay = 0;

	uint8_t btn_1_pressed = 0;

	uint8_t led_sweep_type = 0;
	uint8_t sweep_a_to_left = 1;
	uint8_t sweep_b_to_left = 1;

	uint8_t sweep_a_counter = 0;
	uint8_t sweep_b_counter = 0;
	uint8_t sweep_b_adder = 0;
	uint8_t sweep_b_reverse = 0;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		//Button 1 de-bouncing to toggle the single LED.
		if (ButtonPressed(GPIOA, GPIO_PIN_8) == SET) {
			DelayMS(10);
			if (ButtonPressed(GPIOA, GPIO_PIN_8) == SET) {
				ToggleOutputMode(GPIOB, &btn_1_pressed, GPIO_PIN_1);
			}
			while (ButtonPressed(GPIOA, GPIO_PIN_8) == SET) {
				//wait 'till release.
			}
		}

		//Button 2 de-bouncing to switch the sweep mode of the LEDs' row.
		if (ButtonPressed(GPIOA, GPIO_PIN_9) == SET) {
			DelayMS(10);
			if (ButtonPressed(GPIOA, GPIO_PIN_9) == SET) {
				led_sweep_type ^= 1;
			}
			while (ButtonPressed(GPIOA, GPIO_PIN_9) == SET) {
				//wait 'till release.
			}
		}

		if (led_sweep_type == 0) {
			SweepA(&sweep_a_counter, &sweep_a_to_left);
		} else {
			SweepB(&sweep_b_counter, &sweep_b_adder, &sweep_b_reverse,
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
 * @note   This function is a GPIO setup function to set the input pin of the Nucleo
 *         board. In this case, the GPIO pin in setup are PB1, PB2, PB3, PB4, PB5.
 * @param  none.
 * @retval none.
 */
void SysTick_LED() {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

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
}

/**
 * @brief  Button Setup.
 *
 * @note   This function is a GPIO setup function to set the input pin of the Nucleo
 *         board. In this case, the GPIO pin in setup is PA8 & PA9.
 * @param  none.
 * @retval none.
 */
void SysTick_Button() {
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
 * @brief  SysTick Interrupt Handler.
 *
 * @note   This function is a SysTick interrupt handler to run an interrupt process
 * 		   between the main program in the main loop.
 *
 * @param  none.
 * @retval none.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */
	if (TimeDelay > 0) {
		TimeDelay--;
	}
	/* USER CODE END SysTick_IRQn 0 */
	//  HAL_IncTick();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/**
 * @brief  Delay SysTick.
 *
 * @note   This function is a SysTick control to count down an input timer value
 * 		   in a ARM register as the timer delay.
 *
 * @param  delay_n the input delay value.
 * @retval none.
 */
void DelayMS(uint32_t delay_n) {
	TimeDelay = delay_n;
	while (TimeDelay > 0) {
		;
	}
}

/**
 * @brief  Reseting the LED output.
 *
 * @note   This function resets the output value of the LEDs digitally to LOW.
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PIN_POS specifies the pin register that would be used in the writing function.
 * @retval none.
 */
void ResetLED(GPIO_TypeDef *PORT, uint16_t PIN_POS) {
	PORT->BRR = (uint32_t) PIN_POS;
}

/**
 * @brief  Writing the LED output.
 *
 * @note   This function writes the output value of the LEDs digitally (HIGH or LOW).
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PIN_POS specifies the pin register that would be used in the writing function.
 * @param  PIN_STATE specifies the chosen state of the LED (HIGH or LOW (SET or RESET)).
 * @retval none.
 */
void SwitchLED(GPIO_TypeDef *PORT, uint16_t PIN_POS, uint8_t PIN_STATE) {
	if (PIN_STATE != RESET) {
		PORT->BSRR = (uint32_t) PIN_POS;
	} else {
		PORT->BRR = (uint32_t) PIN_POS;
	}
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
 * @brief  Toggling the LED output.
 *
 * @note   This function read the state of the input pin (in this case, a button pin)
 * 		   and trigger the output pins (LEDs) state by calling another function, based
 * 		   on the input state.
 *
 * @param  PORT is the GPIO peripheral for STM32F3 family (between A to F).
 * @param  PRESS_STATE specifies the state of the input button (switched to on or off).
 * @param  OUT_PIN_POS specifies the pin register that would be used in the writing function.
 * @retval none.
 */
void ToggleOutputMode(GPIO_TypeDef *PORT, uint8_t *PRESS_STATE,
		uint16_t OUT_PIN_POS) {
	if (*PRESS_STATE == RESET) {
		SwitchLED(PORT, OUT_PIN_POS, SET);
		*PRESS_STATE = SET;
	} else {
		SwitchLED(PORT, OUT_PIN_POS, RESET);
		*PRESS_STATE = RESET;
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
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, SET);
			DelayMS(100);
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, RESET);
			*counter += 1;
		} else if (*counter == 4) {
			*sweep_to_left = 0;
		}
	} else if (*sweep_to_left == 0) {
		if (*counter > 0) {
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, SET);
			DelayMS(100);
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, RESET);
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
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, SET);
			*counter += 1;
			*adder += 1;
		} else if (*adder > 3 && *adder < 8) {
			SwitchLED(GPIOB, GPIO_PIN_2 << *reverse, RESET);
			*adder += 1;
			*reverse += 1;
		} else if (*adder == 8) {
			*sweep_to_left = 0;
		}
		DelayMS(100);
	} else if (*sweep_to_left == 0) {
		if (*counter > 0) {
			*counter -= 1;
			*adder -= 1;
			SwitchLED(GPIOB, GPIO_PIN_2 << *counter, SET);
		} else if (*adder <= 4 && *adder > 0) {
			*adder -= 1;
			*reverse -= 1;
			SwitchLED(GPIOB, GPIO_PIN_2 << *reverse, RESET);
		} else if (*adder == 0) {
			*sweep_to_left = 1;
		}
		DelayMS(100);
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
