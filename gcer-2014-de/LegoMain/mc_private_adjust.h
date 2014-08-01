#ifndef _MC_PRIVATE_ADJUST_H_
#define _MC_PRIVATE_ADJUST_H_

#include "mc_interface.h"

#define _MC_TRUE 1
#define _MC_FALSE 0

extern int _IS_MC_ON;
extern float _MC_BIG_LINEAR_AMOUNT;
extern float _MC_SMALL_LINEAR_AMOUNT;
extern float _MC_BIG_SPIN_AMOUNT;
extern float _MC_SMALL_SPIN_AMOUNT;

extern float _MC_SLOW_LINEAR_SPEED;
extern float _MC_VERY_SLOW_LINEAR_SPEED;
extern float _MC_SLOW_SPIN_SPEED;
extern float _MC_VERY_SLOW_SPIN_SPEED;

typedef enum {_MC_FORWARD_ACTION, _MC_BACKWARD_ACTION, _MC_LEFT_ACTION, _MC_RIGHT_ACTION, _MC_HELP_ACTION, _MC_QUIT_ACTION, _MC_UNKNOWN_ACTION} _MC_ACTION;

// _MC_FORWARD_SECONDS, _MC_BACKWARD_SECONDS, _MC_LEFT_SECONDS, _MC_RIGHT_SECONDS, _MC_SERVO, _MC_MOTOR, _MC_SERVOS, _MC_MOTORS, 

typedef struct {
	_MC_ACTION action;
	int amount;
	int number; // for servo and motor motions // FIXME -- does not handle multiple ones
} _MC_COMMAND;

float _mc_adjust(MC_DIRECTION direction_moved, float amount_moved, float speed_at_which_moved, float result_from_move);

void _mc_repeat_command();
void _mc_show_robot_state();
_MC_COMMAND _mc_ask_what_to_do(MC_DIRECTION direction);
void _mc_summarize();
void _mc_do_it(_MC_COMMAND command);

#endif
