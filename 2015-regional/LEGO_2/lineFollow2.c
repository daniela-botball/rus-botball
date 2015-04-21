#include "legoMovement.h"
#include "lineFollow.h"
#include "universal.h"

// MEASURE these.
#define LEFT_LINE_SENSOR_DESIRED_VALUE 610 // on thick line: 955
#define RIGHT_LINE_SENSOR_DESIRED_VALUE 660 // on thick line: 980

// MEASURE these.  They are not used in the code
// but are helpful to know in figuring out the TUNINGs below.
#define LEFT_LINE_SENSOR_ON_MOST_BLACK_PLACE 840 // 970
#define RIGHT_LINE_SENSOR_ON_MOST_BLACK_PLACE 820 // 940
#define LEFT_LINE_SENSOR_ON_MOST_WHITE_PLACE 540 // 460
#define RIGHT_LINE_SENSOR_ON_MOST_WHITE_PLACE 580 // 570

// TUNE (choose) these by experimenting to see what works best.
#define LINE_FOLLOWING_MAXIMUM_SPEED 80
#define LINE_FOLLOWING_MINIMUM_SPEED 5
#define LINE_FOLLOWING_NORMAL_SPEED 30
#define LEFT_kP 0.5
#define RIGHT_kP 0.5

// Follow a black line.
// Assumes two sensors:
//   -- LEFT_LINE_SENSOR controlling the LEFT_MOTOR speed
//   -- RIGHT_LINE_SENSOR controlling the RIGHT_MOTOR speed
// This code assumes a LEGO robot.
void follow_black_line() {
	int left_sensor_current_value, right_sensor_current_value;
	int left_error, right_error;
	float left_speed, right_speed, raw_left_speed, raw_right_speed;
	int count;
	
	int LEFT_LINE_SENSOR, RIGHT_LINE_SENSOR;
	LEFT_LINE_SENSOR = L_TOPHAT;
	RIGHT_LINE_SENSOR = R_TOPHAT;
	
	count = 0;
	
	// Turn on the left and right motors.  NEGATIVE since backwards.
	motor(LEFT_MOTOR, LINE_FOLLOWING_NORMAL_SPEED);
	motor(RIGHT_MOTOR, LINE_FOLLOWING_NORMAL_SPEED);
	
	while (TRUE) {
		// The following IF determines when you want line-following to stop.
		// Put it where you want in this WHILE loop.
		// Replace FALSE by the condition that, if true, should cause line-following to stop.
		if (analog_et(2) > 350) {
			printf("count, ET: %2i %4i\n", count, analog_et(2));
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
		
		left_error = LEFT_LINE_SENSOR_DESIRED_VALUE - left_sensor_current_value;
		right_error = RIGHT_LINE_SENSOR_DESIRED_VALUE - right_sensor_current_value;
		
		// Adjust the motor speeds proportionately to the errors.
		raw_left_speed = LINE_FOLLOWING_NORMAL_SPEED + (left_error * LEFT_kP);
		left_speed = raw_left_speed;
		if (left_speed < LINE_FOLLOWING_MINIMUM_SPEED) {
			left_speed = LINE_FOLLOWING_MINIMUM_SPEED;
		} else if (left_speed > LINE_FOLLOWING_MAXIMUM_SPEED) {
			left_speed = LINE_FOLLOWING_MAXIMUM_SPEED;
		}
		
		raw_right_speed = LINE_FOLLOWING_NORMAL_SPEED + (right_error * RIGHT_kP);
		right_speed = raw_right_speed;
		if (right_speed < LINE_FOLLOWING_MINIMUM_SPEED) {
			right_speed = LINE_FOLLOWING_MINIMUM_SPEED;
		} else if (right_speed > LINE_FOLLOWING_MAXIMUM_SPEED) {
			right_speed = LINE_FOLLOWING_MAXIMUM_SPEED;
		}
		
		motor(LEFT_MOTOR, (int) left_speed);
		motor(RIGHT_MOTOR, (int) right_speed);
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

