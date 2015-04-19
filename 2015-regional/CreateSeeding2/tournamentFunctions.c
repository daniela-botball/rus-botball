// Created on Sat April 11 2015

#include "universal.h"
#include "createMovement.h"
#include "tournamentFunctions.h"

void operate_winch(int position) {
	raise_winch();
	clear_motor_position_counter(WINCH_MOTOR);
	if (position == WINCH_GROUND_POSITION) {
		motor(WINCH_MOTOR, 100);
		while (get_motor_position_counter(WINCH_MOTOR) < WINCH_GROUND_POSITION);
		freeze(WINCH_MOTOR);
	} else if (position == WINCH_MIDDLE_POSITION) {
		motor(WINCH_MOTOR, 100);
		while (get_motor_position_counter(WINCH_MOTOR) < WINCH_MIDDLE_POSITION);
		freeze(WINCH_MOTOR);
	}
	adjust_motor(WINCH_MOTOR, position);
}

void raise_winch() {
	motor(WINCH_MOTOR, -100);
	while (!digital(WINCH_LEVER)) {}
	freeze(WINCH_MOTOR);
	press_a_to_continue();
}

void lower_winch() {
	motor(WINCH_MOTOR, 100);
	while (TRUE) {
		if (digital(BUTTON_ONE)  || digital(BUTTON_TWO)) {
			break;
		}
	}
	//freeze(WINCH_MOTOR);
	//clear_motor_position_counter(WINCH_MOTOR);
	//motor(WINCH_MOTOR, 25);
	//while (get_motor_position_counter(WINCH_MOTOR) < WINCH_SECOND_GROUND_POSITION);
	freeze(WINCH_MOTOR);
	press_a_to_continue();
}


void open_claw() {
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION); // TODO: Make claw open slower
	adjust_servo(CLAW_SERVO, CLAW_OPEN_POSITION);
}

void close_claw() {
	set_servo_position(CLAW_SERVO, CLAW_CLOSE_POSITION); // TODO: Make claw close slower
	adjust_servo(CLAW_SERVO, CLAW_CLOSE_POSITION);
}
