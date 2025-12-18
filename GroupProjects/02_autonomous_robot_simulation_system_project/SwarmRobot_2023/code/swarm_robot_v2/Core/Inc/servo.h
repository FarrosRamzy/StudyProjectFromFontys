#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"

// Duration for turning
#define TURN_DURATION 3000
#define STOP_SERVO 1500
#define CLOCKWISE 1436
#define ANTI_CLOCKWISE 1570
#define MAX_TURNING_COUNTER 700
#define MAX_STOP_COUNTER 250
#define MAX_MOVE_BACK_COUNTER 100

typedef enum {
    INIT,
    MOVE,
	STOP,
	MOVE_BACKWARD,
    TURN
} RobotState;

extern volatile RobotState robot_state;
extern volatile RobotState last_state;

void move_forward(double);
void move_backward(void);
void turn_right(void);
void turn_left(void);
void stop(void);

#endif
