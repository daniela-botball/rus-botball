#include "movement.h"
#include "universal.h"
#include "createMovement.h"
#include "legoMovement.h"


// Direction should be either FORWARDS or BACKWARDS. Distance is in centimeters. Speed is in cm/s
float drive_distance(int direction, float distance, float speed, float acceleration) {
	float speeds [10000];
	int i = 0;
	float accel_distance = (speed * speed) / acceleration;
	printf("Got this far!\n");
	if (accel_distance > distance) {
		printf("Acceleration is too slow!\n");
		return 0.0;
	}
	
	float current_speed = 0.0;
	float seconds = 0.0; 
	while (current_speed <= speed) {
		drive(direction, current_speed);
		msleep(seconds * 1000.0);
		seconds = seconds + 0.01;
		current_speed = acceleration * seconds;
		if (i < 10000) {
			speeds [i] = current_speed;
			i++;
		}
	}
	printf("Got this far!\n");
	for (i = 0; i < 10000; i++) {
		printf("%i, ", speeds [i]);
	}
	
	
	if (_ROBOT == CREATE_ROBOT) {
		create_drive_distance(direction, distance - accel_distance, speed);
	} else if (_ROBOT == LEGO_ROBOT) {
		lego_drive_distance(direction, distance - accel_distance, speed);
	} else {
		printf("_ROBOT is undefined!\n");
	}
	printf("\n");
	printf("accel_distance = %i\n", accel_distance);
	
	return 0.0;
	
	
	
	
	
}

float drive(int direction, float speed) {
	if (_ROBOT == CREATE_ROBOT) {
		create_drive(direction, speed);
	} else if (_ROBOT == LEGO_ROBOT) {
		lego_drive(direction, speed);
	} else {
		printf("_ROBOT is undefined!\n");
	}
	return 0.0;
}

// Direction should be either LEFT or RIGHT. Degrees is in degrees. Speed is in cm/s
int spin_degrees(int direction, int degrees, int speed) {
	if (_ROBOT == CREATE_ROBOT) {
		create_spin_degrees(direction, degrees, speed);
	} else if (_ROBOT == LEGO_ROBOT) {
		lego_spin_degrees(direction, degrees, speed);
	} else {
		printf("_ROBOT is undefined!\n");
	}
	return 0;
}

int spin(int direction, int speed) {
	if (_ROBOT == CREATE_ROBOT) {
		create_spin(direction, speed);
	} else if (_ROBOT == LEGO_ROBOT) {
		lego_spin(direction, speed);
	} else {
		printf("_ROBOT is undefined!\n");
	}
	return 0;
}


