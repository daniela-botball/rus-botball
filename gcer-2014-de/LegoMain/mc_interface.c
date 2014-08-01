// FIXME: Add description.
// Authors:  Aaron, Seth and David Mutchler.
//           July 2014 (with earliest versions dating from 2006).
// FIXME: Add Creative Commons license.

#include "mc_interface.h"
#include "mc_movements.h"
#include "mc_private_adjust.h"

int _MC_IS_ON = 1;

float mc_move(MC_DIRECTION direction_to_move, float amount_to_move, float speed_at_which_to_move) {
	float result;
	
	result = real_move(direction_to_move, amount_to_move, speed_at_which_to_move);
	
	if (is_mc_on()) {
		result = _mc_adjust(direction_to_move, amount_to_move, speed_at_which_to_move, result);
	} else {
		msleep(1000);
	}
	return result;
}

void set_mc_big_amount(float big_linear_amount, float big_spin_amount) {
	_MC_BIG_LINEAR_AMOUNT = big_linear_amount;
	_MC_BIG_SPIN_AMOUNT = big_spin_amount;
}

void set_mc_small_amount(float small_linear_amount, float small_spin_amount) {
	_MC_SMALL_LINEAR_AMOUNT = small_linear_amount;
	_MC_SMALL_SPIN_AMOUNT = small_spin_amount;
}
	
void set_mc_slow_speed(float slow_linear_speed, float slow_spin_speed) {
	_MC_SLOW_LINEAR_SPEED = slow_linear_speed;
	_MC_SLOW_SPIN_SPEED = slow_spin_speed;
}

void set_mc_very_slow_speed(float very_slow_linear_speed, float very_slow_spin_speed) {
	_MC_VERY_SLOW_LINEAR_SPEED = very_slow_linear_speed;
	_MC_VERY_SLOW_SPIN_SPEED = very_slow_spin_speed;
}

void turn_mc_on() {
	_IS_MC_ON = _MC_TRUE;
}

void turn_mc_off() {
	_IS_MC_ON = _MC_FALSE;
}

int is_mc_on() {
	return _IS_MC_ON;
}

/*

void set_units(int create_linear_units, int create_spin_units, int lego_linear_units, int lego_spin_units);

void set_big_linear(float big_amount_for_create, int big_amount_for_lego);
void set_big_spin(float big_amount_for_create, int big_amount_for_lego);
void set_small_linear(float big_amount_for_create, int big_amount_for_lego);
void set_small_spin(float big_amount_for_create, int big_amount_for_lego);
*/
