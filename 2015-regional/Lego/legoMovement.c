#include "legoMovement.h"

void lego_drive_distance(int direction, float distance, float speed) {
	int ticks;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, speed * direction);
	motor(RIGHT_MOTOR, speed * direction);
	
	while (TRUE) {
		ticks = get_motor_position_counter(LEFT_MOTOR);
		if (ticks < 0) ticks = -ticks;
			
		if (ticks >= distance) {
			break;
		}
	}
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void lego_spin_degrees(int direction, int distance, int speed) {
	int ticks;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, speed * direction);
	motor(RIGHT_MOTOR, -speed * direction);
	
	while (TRUE) {
		ticks = get_motor_position_counter(LEFT_MOTOR);
		if (ticks < 0) ticks = -ticks;
			
		if (ticks >= distance) {
			break;
		}
	}
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

