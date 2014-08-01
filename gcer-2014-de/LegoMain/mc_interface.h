#ifndef _MC_INTERFACE_H_
#define _MC_INTERFACE_H_

// FIXME: Add description.
// Authors:  Aaron, Seth and David Mutchler.
//           Created 2006, this version is July 2014.
// FIXME: Add Creative Commons license.

// If you have already used   move   as a function name,
// simply change ... FIXME

typedef enum {MC_FORWARD=0, MC_BACKWARD=1, MC_LEFT=2, MC_RIGHT=3} MC_DIRECTION;

float mc_move(MC_DIRECTION direction_to_move, float amount_to_move, float speed_at_which_to_move);

// Call these if (as is likely) the defaults are not right for you.
void set_mc_big_amount(float big_linear_amount, float big_spin_amount);
void set_mc_small_amount(float small_linear_amount, float big_linear_amount);
void set_mc_slow_speed(float slow_linear_speed, float slow_spin_speed);
void set_mc_very_slow_speed(float very_slow_linear_speed, float very_slow_spin_speed);

void turn_mc_on();
void turn_mc_off();
int is_mc_on();

/*
typedef enum (UNITS_ARE_CM, UNITS_ARE_MM, UNITS_ARE_INCHES, UNITS_ARE_TICKS, UNITS_ARE_DEGREES, UNITS_ARE_SECONDS, UNITS_ARE_MILLISECONDS, UNITS_ARE_OTHER) UNITS;
typedef enum {CREATE_ROBOT, LEGO_ROBOT} ROBOT;
void set_units(ROBOT robot, UNITS linear_units, UNITS spin_units);
*/
/*

// FIXME: Some of these will NOT make sense to the user, probably.
// FIXME: Make it prettier in this file???
// FIXME: Add a PREFIX to avoid name conflicts, perhaps MC_
// FIXME: At least add a WARNING, ala above.


// All of the following do what their name suggests, plus adjusting if move-calibration is on.
// Amount and speed are always POSITIVE.


// Turn move-calibration on or off.

// FIXME: deal with curves.
// void mc_curve(float amount, float left_motor_speed, float right_motor_speed);
void mc();	// CONSIDER: Should mc stop things?  Or leave that to the user?  Or have a mc_stop, that calls the user's stop?
			// CONSIDER: Should there be a mc_pause and mc_resume, that call the users' stop and resume?
	

// Rest are syntactic sugar.
void mc_forward(float distance, float speed);
void mc_backward(float distance, float speed);
void mc_left(float distance, float speed);
void mc_right(float distance, float speed);

void mc_forward_seconds(float seconds, float speed);
void mc_backward_seconds(float seconds, float speed);
void mc_left_seconds(float seconds, float speed);
void mc_right_seconds(float seconds, float speed);
*/
#endif
