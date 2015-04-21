// Created on Sat April 18 2015

float L_kP = 0.6;
float R_Kp = 0.6;

int L_DESIRED_VALUE = 650;
int R_DESIRED_VALUE = 640;

#include "legoMovement.h"
#include "universal.h"
#include "lineFollow.h"
void line_follow(int direction, int desired_speed, int stopping_event) {
	int l_speed, r_speed, l_reading, r_reading, r_error, l_error;
	
	while (1) {
		
		l_reading = analog(L_TOPHAT);
		r_reading = analog(R_TOPHAT);
		
		l_error = L_DESIRED_VALUE - l_reading;
		r_error = R_DESIRED_VALUE - r_reading;
		
		l_speed = desired_speed + (l_error * kP);
		if (l_speed > 100) { //desired_speed + MAXIMUM_SPEED_DEVIATION) {
			l_speed = 100; // desired_speed + MAXIMUM_SPEED_DEVIATION;
		} else if (l_speed < 10) { // desired_speed - MAXIMUM_SPEED_DEVIATION) {
			l_speed = 10; //desired_speed - MAXIMUM_SPEED_DEVIATION;
		}
		
		r_speed = desired_speed + (r_error * kP);
		if (r_speed > 100) { //desired_speed + MAXIMUM_SPEED_DEVIATION) {
			r_speed = 100; // desired_speed + MAXIMUM_SPEED_DEVIATION;
		} else if (r_speed < 10) { // desired_speed - MAXIMUM_SPEED_DEVIATION) {
			r_speed = 10; //desired_speed - MAXIMUM_SPEED_DEVIATION;
		}
		
		motor(LEFT_MOTOR, ((int) l_speed) * direction);
		motor(RIGHT_MOTOR, ((int) r_speed) * direction);
		if (check_stopping_event(stopping_event)) {
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			break;
		}
	}
}


void wall_follow(int direction, int desired_speed, int stopping_event) {
	int l_speed, r_speed, sensor_reading, error;
	
	while (1) {
		
		sensor_reading = analog_et(ET_SENSOR);
		
		error = sensor_reading - ET_DESIRED_VALUE;
		
		l_speed = desired_speed - (error * ET_kP);
		if (l_speed > desired_speed + ET_MAXIMUM_SPEED_DEVIATION) {
			l_speed = desired_speed + ET_MAXIMUM_SPEED_DEVIATION;
		} else if (l_speed < desired_speed - ET_MAXIMUM_SPEED_DEVIATION) {
			l_speed = desired_speed - ET_MAXIMUM_SPEED_DEVIATION;
		}
		
		r_speed = desired_speed + (error * ET_kP);
		if (r_speed > desired_speed + ET_MAXIMUM_SPEED_DEVIATION) {
			r_speed = desired_speed + ET_MAXIMUM_SPEED_DEVIATION;
		} else if (r_speed < desired_speed - ET_MAXIMUM_SPEED_DEVIATION) {
			r_speed = desired_speed - ET_MAXIMUM_SPEED_DEVIATION;
		}
		
		motor(LEFT_MOTOR, ((int) l_speed) * direction);
		motor(RIGHT_MOTOR, ((int) r_speed) * direction);
		if (check_stopping_event(stopping_event) == 1) {
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			break;
		}
	}
}

int check_stopping_event(int stopping_event) {
	if (stopping_event == STOP_BY_ET) {
		if (analog_et(ET_SENSOR) < 300) {
			return 1;
		}
	} else if (stopping_event == STOP_BY_TOPHAT) {
		display_printf(0, 0, "%4i", analog(L_TOPHAT));
		if (analog(L_TOPHAT) > 750 || analog(R_TOPHAT) > 750) {
			return 1;
		}
	} else if (stopping_event == STOP_BY_CAMERA) {
		camera_update();
		if (get_object_count(0) < 1) {
			display_printf(0, 0, "No Object Found");
			return 0;
		}
		if (get_object_area(0, 0) > PINGPONG_THRESHOLD) {
			display_clear();
			display_printf(0, 0, "Object Seen!");
			if (get_object_center(0, 0).x > 90 && get_object_center(0, 0).x < 110) {
				display_printf(0, 1, "Object centered");
				return 1;
			}
		}
	} else {
		printf("Stopping type is not defined!\n");
		return -1;
	}
	return 0;
}

void adjust_onto_line(int direction) {
	if (analog(L_TOPHAT) > 750 && analog(R_TOPHAT) > 750) {
		return;
	} else if (analog(L_TOPHAT) > 750 && analog(R_TOPHAT) < 750) {
		motor(RIGHT_MOTOR, 30 * direction);
		while (analog(R_TOPHAT) < 750) {}
		off(RIGHT_MOTOR);
	} else if (analog(L_TOPHAT) < 750 && analog(R_TOPHAT) > 750) {
		motor(LEFT_MOTOR, 30 * direction);
		while (analog(L_TOPHAT) < 750) {}
		off(LEFT_MOTOR);
	} else if (analog(L_TOPHAT) < 750 && analog(R_TOPHAT) < 750) {
		printf("ROBOT IS NOT ON BLACK LINE!\n");
	}
}
