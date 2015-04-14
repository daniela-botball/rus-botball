#include "movement.h"
#include "legoMovement.h"

void robot_drive_distance(float distance, float speed, int direction) {
	if (_ROBOT == CREATE) {
	//create_drive_distance(distance, speed, direction);
	} else if (_ROBOT == LEGO) {
		lego_drive_distance(distance, speed, direction);
	}
}

void robot_drive(float speed, int direction) {
	if (_ROBOT == CREATE) {
		//create_drive(speed, direction);
	} else if (_ROBOT == LEGO) {
		lego_drive(speed, direction);
	}
}

void robot_stop() {
	#if _ROBOT == CREATE
	//create_stop();
	#elif _ROBOT == LEGO
	lego_stop();
	#endif
}

void robot_spin_degrees(int degrees, int speed, int direction) {
	if (_ROBOT == CREATE) {
		//create_spin_degrees(degrees, speed, direction);
	} else if (_ROBOT == LEGO) {
		lego_spin_degrees(degrees, speed, direction);
	}
}

void drive_until_analog_sensor(float speed, int direction, int port, int threshold, int direction_of_comparison) {
	lego_drive(speed, direction);
	while (analog_comparator(port, threshold, direction_of_comparison) == 0);
	lego_stop();
}

int analog_comparator(int port, int threshold, int direction_of_comparison) {
	if (analog10(port) * direction_of_comparison > threshold * direction_of_comparison) {
		return 1;
	} else {return 0;}
}
