#include "legoMovement.h"
#include "universal.h"
#include "lineFollow2.h"

// Follow a black line.
// Assumes two sensors:
//   -- LEFT_LINE_SENSOR controlling the LEFT_MOTOR speed
//   -- RIGHT_LINE_SENSOR controlling the RIGHT_MOTOR speed
// This code assumes a LEGO robot.
void follow_black_line(int normal_speed, int minimum_speed, int maximum_speed, int left_desired_value, int right_desired_value, float left_kP, float right_kP) {
	int left_sensor_current_value, right_sensor_current_value;
	int left_error, right_error;
	float left_speed, right_speed, raw_left_speed, raw_right_speed;
	int count;
	
	int LEFT_LINE_SENSOR, RIGHT_LINE_SENSOR;
	LEFT_LINE_SENSOR = L_TOPHAT;
	RIGHT_LINE_SENSOR = R_TOPHAT;
	
	count = 0;
	
	// Turn on the left and right motors.  NEGATIVE since backwards.
	motor(LEFT_MOTOR, normal_speed);
	motor(RIGHT_MOTOR, normal_speed);
	
	while (TRUE) {
		// The following IF determines when you want line-following to stop.
		// Put it where you want in this WHILE loop.
		// Replace FALSE by the condition that, if true, should cause line-following to stop.
		if (analog_et(2) > 350) {
			printf("count, ET: %2i %4i\n", count, analog_et(ET_SENSOR));
			++count;
		} else {
			count = 0;
		}
		
		if (count > 5) {
			break;
		}
		
		// Determine the "errors" -- how far the sensors are from their desired values.
		left_sensor_current_value = analog(LEFT_LINE_SENSOR);
		right_sensor_current_value = analog(RIGHT_LINE_SENSOR);
		
		left_error = left_desired_value - left_sensor_current_value;
		right_error = right_desired_value - right_sensor_current_value;
		
		// Adjust the motor speeds proportionately to the errors.
		raw_left_speed = normal_speed + (left_error * left_kP);
		left_speed = raw_left_speed;
		if (left_speed < minimum_speed) {
			left_speed = minimum_speed;
		} else if (left_speed > maximum_speed) {
			left_speed = maximum_speed;
		}
		
		raw_right_speed = normal_speed + (right_error * right_kP);
		right_speed = raw_right_speed;
		if (right_speed < minimum_speed) {
			right_speed = minimum_speed;
		} else if (right_speed > maximum_speed) {
			right_speed = maximum_speed;
		}
		
		motor(LEFT_MOTOR, (int) left_speed);
		motor(RIGHT_MOTOR, (int) right_speed);
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

// direction must be FORWARDS, BACKWARDS, LEFT or RIGHT
// speed must be between 1 and 100.
// comparison must be LESS_THAN or GREATER_THAN
// goes in specified direction at specified speed
// until given sensor is <comparison> given threshold.
void go_until(int direction, int speed, int sensor, int comparison, int threshold) {
	int left_speed, right_speed;
	
	if (direction == FORWARDS || direction == BACKWARDS) {
		left_speed = speed * direction;
		right_speed = speed * direction;
	} else {
		left_speed = speed * direction;
		right_speed = -(speed * direction);	
	}
	
	motor(LEFT_MOTOR, left_speed);
	motor(RIGHT_MOTOR, right_speed);
	
	while (TRUE) {
		if (comparison == LESS_THAN) {
			if (analog(sensor) < threshold) {
				break;
			}
		} else {
			if (analog(sensor) >= threshold) {
				break;
			}
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}


