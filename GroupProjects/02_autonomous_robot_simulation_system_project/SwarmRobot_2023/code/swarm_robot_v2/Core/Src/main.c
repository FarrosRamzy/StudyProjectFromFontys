#include "main.h"

// make everything snake case
const double kI = 0.549378309652703;
const double kP = 0.156755704961953;
const double kD = 0.0904541280843227;

volatile uint32_t last_capture = 0;
volatile uint32_t pulse_width = 0;
volatile uint8_t capture_done = 0;

volatile RobotState last_state = INIT;
volatile uint16_t distance_to_obstacle = 0;
volatile uint8_t state_sent = 0;

float totalDistance = 0;
int count = 0;

int turning_direction;

DistanceType filtered_distance = 0;

volatile RobotState state = INIT;

// Millis
uint32_t state_change_millis = 0;
uint32_t robot_loop_millis = 0;
// The desired delay duration in milliseconds
uint32_t stop_interval = 1000;
uint32_t loop_interval = 50;
uint32_t move_backward_interval = 2000;

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}

int main(void) {
	HAL_Init();

	// fix timers config, fist the channel

	Timer2_Init();
	Timer3_Init();
	Timer4_Init();

	EnableGPIOB();
	Ultrasonic_Trigger_Config();
	Ultrasonic_Echo_Config();
	Servo_PWM_Config();

	SystemClock_Config();
	configure_UART();
	configure_extern_UART();
	while (1) {

		uint32_t currentMillis = millis;
		DistanceType distance = measure_distance();
//		UART_send(distance);

// Measure distance regardless of the robot's state
		if (distance != DEFAULT_DISTANCE) {
			filtered_distance = distance;
		}

		if (currentMillis - robot_loop_millis >= loop_interval) {
			robot_loop_millis = currentMillis;
			switch (state) {
			case INIT:
				// Initialization code here
				state = MOVE;
				break;

			case MOVE:
				// Call my_pid to control the servo based on distance
				double my_pid_output = my_pid(DANGER_DISTANCE,
						filtered_distance);

				if (filtered_distance <= DANGER_DISTANCE) {
					state_change_millis = currentMillis;
					state_sent = 0;
					state = STOP;
				} else {
					move_forward(my_pid_output);
					if (state_sent == 0) {
						UART_send_direction_to_extern(0);
						state_sent = 1;
					}
				}
				break;
			case STOP:
				stop();
				if (state_sent == 0) {
					UART_send_direction_to_extern(1);
					state_sent = 1;
				}
				if (currentMillis - state_change_millis >= stop_interval) {
					// Reset the timing variable
					state_change_millis = currentMillis;
					state_sent = 0;
					state = MOVE_BACKWARD;
				}
				break;
			case MOVE_BACKWARD:
				move_backward();
				if (state_sent == 0) {
					UART_send_direction_to_extern(2);
					state_sent = 1;
				}
				if (currentMillis - state_change_millis
						>= move_backward_interval) {
					state_change_millis = currentMillis;
					turning_direction = (rand() % RANDOM_FACTOR);
					state_sent = 0;
					state = TURN;
				}
				break;
			case TURN:
				// Check distance during TURN
				if (filtered_distance <= DANGER_DISTANCE) {
					state = STOP;
					// Break to exit the TURN case immediately
					break;
				}
				// Continue TURN logic if distance is safe
				if (turning_direction == 0) {
					turn_left();
					if (state_sent == 0) {
						UART_send_direction_to_extern(3);
						state_sent = 1;
					}
				} else {
					turn_right();
					if (state_sent == 0) {
						UART_send_direction_to_extern(4);
						state_sent = 1;
					}
				}
				if (currentMillis - state_change_millis >= TURN_DURATION) {
					state_change_millis = currentMillis;
					state_sent = 0;
					state = INIT;
				}
				break;
			}
		}

	}
}

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

// PID control function
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
	UART_send_speed_to_extern(pid_output);

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
