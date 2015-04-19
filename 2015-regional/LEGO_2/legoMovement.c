#include "legoMovement.h"
#include "universal.h"
void lego_drive_distance(int direction, float distance, float speed) {
	int ticks;
	int distance_in_ticks = (int) (distance * TICKS_PER_CENTIMETER);
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	motor(LEFT_MOTOR, speed * direction);
	motor(RIGHT_MOTOR, speed * 95 * direction / 100);
	
	while (TRUE) {
		ticks = get_motor_position_counter(LEFT_MOTOR);
		if (ticks < 0) ticks = -ticks;
			
		if (ticks >= distance_in_ticks) {
			break;
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	adjust_drive(direction,distance);
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
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	
	adjust_spin(direction,distance);
}
