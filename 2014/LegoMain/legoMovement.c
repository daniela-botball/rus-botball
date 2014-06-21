#include "legoMovement.h"
#include "movement.h"
void lego_drive(int speed, int direction) {
	motor(LEFT_MOTOR, speed * direction);
	motor(RIGHT_MOTOR, speed * direction);
}

void lego_spin(int speed, int direction) {
	motor(LEFT_MOTOR, speed * -direction);
	motor(RIGHT_MOTOR, speed * direction);
}

void lego_stop() {
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void lego_drive_distance(float distance, float speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_drive(speed, direction);
	int ticks = distance * TICKS_PER_CENTIMETER;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	lego_stop();
}

void lego_spin_degrees(int degrees, int speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_spin(speed, direction);
	int ticks = degrees * TICKS_PER_DEGREE;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	lego_stop();
}
