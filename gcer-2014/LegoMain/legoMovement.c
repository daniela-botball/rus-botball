#include "legoMovement.h"
#include "movement.h"
void lego_drive(int speed, int direction) { // use mav instead - mav's parameter is ticks/sec
	motor(LEFT_MOTOR, speed * direction); 
	motor(RIGHT_MOTOR, speed * direction);
}

void lego_spin(int speed, int direction) { // use mav instead - mav's parameter is ticks/sec
	motor(LEFT_MOTOR, speed * -direction);
	motor(RIGHT_MOTOR, speed * direction);
}

void lego_stop() {
	freeze(LEFT_MOTOR);   // active stop - block wheel
	freeze(RIGHT_MOTOR);
	msleep(100);          // wait for bot to stop
	off(LEFT_MOTOR);      // passive stop - cut off wheels power
	off(RIGHT_MOTOR);
}

void lego_drive_distance(float distance, float speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_drive(speed, direction);
	int ticks = distance * TICKS_PER_CENTIMETER;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks) msleep(10); //without sleep in loops botui doesn't work
	lego_stop();
}

void lego_spin_degrees(int degrees, int speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	lego_spin(speed, direction);
	int ticks = degrees * TICKS_PER_DEGREE;  
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks) msleep(10); //without sleep in loops botui doesn't work; todo: check if code works with both directions
	lego_stop();
}
