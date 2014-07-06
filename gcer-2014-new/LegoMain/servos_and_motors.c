#include "servos_and_motors.h"
#include <stdlib.h>

void move_servo_at_speed(int port, int desired_position, int ticks_per_second) {
	// FIXME: Change units to degrees per second
	int i;
	int initial_position;
	int distance;
	int direction;
	int sleep_per_iteration;
	
	initial_position = get_servo_position(port);
	direction = initial_position <= desired_position ? 1 : -1;
	distance = abs(initial_position - desired_position);
	
	sleep_per_iteration = (int) (1000.0 * (float) MINIMUM_SERVO_INCREMENT / ticks_per_second);
	
	for (i = 0; i < distance; i += MINIMUM_SERVO_INCREMENT) {
			set_servo_position(port, initial_position + direction * i);
			msleep(sleep_per_iteration);
	}
	
	// To get exactly to the desired_position (since the above has round-off error).
	msleep(200);
	set_servo_position(port, desired_position);
}

/*
void move_servo_slowly(int port, int position) {
	int i;
	if (get_servo_position(port) < position) {
		for (i = get_servo_position(port); i < position; i += SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(20);
		}
	} else if (get_servo_position(port) > position) {
		for (i = get_servo_position(port); i > position; i -= SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(20);
		}
	} else {return;}
	msleep(500);
	set_servo_position(port, position);
}

void move_servo_very_slowly(int port, int position) {
	int i;
	if (get_servo_position(port) < position) {
		for (i = get_servo_position(port); i < position; i += SERVO_INCREMENT / 3) {
			set_servo_position(port, i);
			msleep(20);
		}
	} else if (get_servo_position(port) > position) {
		for (i = get_servo_position(port); i > position; i -= SERVO_INCREMENT / 3) {
			set_servo_position(port, i);
			msleep(20);
		}
	} else {return;}
	msleep(500);
	set_servo_position(port, position);
}*/
