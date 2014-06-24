#include "tournamentFunctions.h"

void track_on() {
	motor(TRACK_MOTOR, 100);
}

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
