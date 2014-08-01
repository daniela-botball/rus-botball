#ifndef _MC_MOVEMENTS_H_
#define _MC_MOVEMENTS_H_

#include "mc_interface.h"

// FIXME: Add description.
// Authors:  Aaron, Seth and David Mutchler.
//           July 2014 (with earliest versions dating from 2006).
// FIXME: Add Creative Commons license.

// These are what the user of this framework must implement.
// The framework supplies do-nothing implementations.


// All of the following do what their name suggests, plus adjusting if move-calibration is on.
// Amount and speed are always POSITIVE.
float real_move(MC_DIRECTION direction_to_move, float amount_to_move, float speed_at_which_to_move);

// CONSIDER: Offer the trivial implementations of the following, in terms of move.

/*
float forward(float distance, float speed);
float backward(float distance, float speed);
float left(float distance, float speed);
float right(float distance, float speed);

float forward_seconds(float seconds, float speed);
float backward_seconds(float seconds, float speed);
float left_seconds(float seconds, float speed);
float right_seconds(float seconds, float speed);

float curve(float left_motor_distance, float left_motor_speed, float right_motor_distance, float right_motor_speed);
float curve_seconds(float seconds, float left_motor_speed, float right_motor_speed);
*/

#endif
