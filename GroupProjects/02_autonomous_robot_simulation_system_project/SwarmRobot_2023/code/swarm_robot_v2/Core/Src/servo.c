#include "servo.h"

void move_forward(double pid_power) {
    TIM3->CCR3 = ANTI_CLOCKWISE + pid_power;
    TIM3->CCR4 = CLOCKWISE - pid_power;
}

void move_backward(void) {
    uint16_t reverse_counter = 0;
    while (reverse_counter < MAX_MOVE_BACK_COUNTER) {
        TIM3->CCR3 = CLOCKWISE;
        TIM3->CCR4 = ANTI_CLOCKWISE;
        reverse_counter++;
    }
}

void turn_right(void) {
    uint16_t turning_counter = 0;
    while (turning_counter < MAX_TURNING_COUNTER) {
        TIM3->CCR3 = ANTI_CLOCKWISE;
        TIM3->CCR4 = STOP_SERVO;
        turning_counter++;
    }
}

void turn_left(void) {
    uint16_t turning_counter = 0;
    while (turning_counter < MAX_TURNING_COUNTER) {
        TIM3->CCR3 = STOP_SERVO;
        TIM3->CCR4 = CLOCKWISE;
        turning_counter++;
    }
}

void stop(void) {
    uint16_t stop_counter = 0;
    while (stop_counter < MAX_STOP_COUNTER) {
        TIM3->CCR3 = STOP_SERVO;
        TIM3->CCR4 = STOP_SERVO;
        stop_counter++;
    }
}
