#include "legoMovement.h"

void lego_drive_distance(int direction, float distance, int left_speed, int right_speed) {
	int ticks;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, left_speed * direction);
	motor(RIGHT_MOTOR, right_speed * direction);
	
	while (TRUE) {
		ticks = get_motor_position_counter(LEFT_MOTOR);
		if (ticks < 0) ticks = -ticks;
			
		if (ticks >= distance) {
			break;
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

void lego_spin_degrees(int direction, int distance, int left_speed, int right_speed) {
	int ticks;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, left_speed * direction);
	motor(RIGHT_MOTOR, -right_speed * direction);
	
	while (TRUE) {
		ticks = get_motor_position_counter(LEFT_MOTOR);
		if (ticks < 0) ticks = -ticks;
			
		if (ticks >= distance) {
			break;
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

