#include "legoMovement.h"
#include "movement.h"
#include <stdlib.h>

void lego_drive(float speed, int direction) {
	WHEELS_MOTOR_POWER power;
	
	power = lego_drive_powers(speed, direction);
	
	motor(LEFT_MOTOR, power.left_power * direction);
	motor(RIGHT_MOTOR, power.right_power * direction);
}


void lego_spin(int speed, int direction) {
	WHEELS_MOTOR_POWER power;
	
	power = lego_spin_powers(speed, direction);
	
	motor(LEFT_MOTOR, power.left_power * -direction);
	motor(RIGHT_MOTOR, power.right_power * direction);
}

void lego_stop() {
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void lego_freeze() {
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

WHEELS_MOTOR_POWER lego_drive_powers(float speed, int direction) {
	// Set the powers to use to achieve the given motion.
	// Adjust for the motor/port/robot differences that cause the robot to veer, etc.
	//
	// FIXME: Not tuned at all!
	WHEELS_MOTOR_POWER power;
	
	power.left_power = (int) (ADJUST_LEFT * speed);
	power.right_power = (int) (ADJUST_RIGHT * speed);
	
	return power;
}

WHEELS_MOTOR_POWER lego_spin_powers(float speed, int direction) {
	// Set the powers to use to achieve the given motion.
	// Adjust for the motor/port/robot differences that cause the robot to veer, etc.
	//
	// FIXME: Not tuned at all!
	WHEELS_MOTOR_POWER power;
	
	power.left_power = speed;
	power.right_power = speed;
	
	return power;
}

void lego_drive_distance(float distance, float speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_drive(speed, direction);
	int ticks = distance * TICKS_PER_CENTIMETER;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	lego_freeze();
}

void lego_spin_degrees(int degrees, int speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_spin(speed, direction);
	int ticks = degrees * TICKS_PER_DEGREE;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	lego_freeze();
}
