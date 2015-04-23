#include "legoMovement.h"
#include "universal.h"
#include "lineFollow2.h"
#include "timing.h"
// Follow a black line.
// Assumes two sensors:
//   -- LEFT_LINE_SENSOR controlling the LEFT_MOTOR speed
//   -- RIGHT_LINE_SENSOR controlling the RIGHT_MOTOR speed
// This code assumes a LEGO robot.
void follow_black_line(int normal_speed, int minimum_speed, int maximum_speed, int left_desired_value, int right_desired_value, float left_kP, float right_kP, int (*stopping_function)()) {
	int left_sensor_current_value, right_sensor_current_value;
	int left_error, right_error;
	float left_speed, right_speed, raw_left_speed, raw_right_speed;
	int count = 0;
	
	int LEFT_LINE_SENSOR, RIGHT_LINE_SENSOR;
	LEFT_LINE_SENSOR = L_TOPHAT;
	RIGHT_LINE_SENSOR = R_TOPHAT;
	
	display_clear();
	
	// Turn on the left and right motors.  NEGATIVE since backwards.
	motor(LEFT_MOTOR, normal_speed);
	motor(RIGHT_MOTOR, normal_speed);
	
	while (TRUE) {
		if (stopping_function()) {
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
		
		if (count % 100 == 0) {
			display_printf(0, 0, "Raw speeds (l, r): %4i, %4i", raw_left_speed, raw_right_speed);
			display_printf(0, 1, "    Speeds (l, r): %4i, %4i", left_speed, right_speed);
			display_printf(0, 2, "    Values (l, r): %4i, %4i", left_sensor_current_value, right_sensor_current_value);
			display_printf(0, 3, "    Errors (l, r): %4i, %4i", left_error, right_error);
		}
		count++;
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

// direction must be FORWARDS, BACKWARDS, LEFT or RIGHT
// speed must be between 1 and 100.
// comparison must be LESS_THAN or GREATER_THAN
// goes in specified direction at specified speed
// until given sensor is <comparison> given threshold.

void drive_until(int direction, int speed, int sensor, int (*comparator)(int, int), int threshold) {
	int left_speed, right_speed;
	
	if (direction == FORWARDS || direction == BACKWARDS) {
		left_speed = speed * direction;
		right_speed = speed * direction;
	} else {
		right_speed = speed * direction;
		left_speed = -(speed * direction);	
	}
	
	motor(LEFT_MOTOR, left_speed);
	motor(RIGHT_MOTOR, right_speed);
	
	while (TRUE) {
		if (comparator(analog(sensor), threshold)) {
			break;
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

void spin_until(int direction, int speed, int sensor, int (*comparator)(int, int), int threshold) {
	int left_speed, right_speed;
	
	if (direction == LEFT || direction == RIGHT) {
		left_speed = speed * direction;
		right_speed = -speed * direction;
	}
	
	motor(LEFT_MOTOR, left_speed);
	motor(RIGHT_MOTOR, right_speed);
	
	while (TRUE) {
		if (comparator(analog(sensor), threshold)) {
			break;
		}
	}
	
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

void turn_around_on_black_line(int direction, int speed) {
	msleep(500);
	spin_until(direction, speed, L_TOPHAT, less_than, LEFT_SENSOR_ON_WHITE);
	msleep(200);
	spin_until(direction, speed, L_TOPHAT, greater_than, LEFT_SENSOR_ON_BLACK_DIVIDER);
	msleep(200);
	spin_until(direction, speed, L_TOPHAT, less_than, LEFT_SENSOR_ON_WHITE);
}

int _count = 0;
int ET_stop() {
	if (analog_et(ET_SENSOR) > 350) {
		++_count;
	} else {
		_count = 0;
	}
		
	if (_count > 5) {
		_count = 0;
		return TRUE;
	} else {
		return FALSE;
	}
}

int wall_opening_stop() {
	if (analog_et(ET_SENSOR) < 350) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int camera_stop() {
	camera_update();
	display_printf(0, 0, "Object size: %4i", get_object_area(ORANGE, 0));
	return (get_object_count(ORANGE) > 0 && get_object_area(ORANGE, 0) > PINGPONG_THRESHOLD);
}

int camera_with_time_stop() {
	
	if (a_button()) {
		return 1;
	} else {
		return 0;
	}
	
	if (check_timer(0) < 0) {
		start_timer(0);
		display_clear();
	} else if (check_timer(0) > 5) {
		camera_update();
		display_printf(0, 0, "Object size: %4i", get_object_area(ORANGE, 0));
		return (get_object_count(ORANGE) > 0 && get_object_area(ORANGE, 0) > PINGPONG_THRESHOLD);
	} else {
		return FALSE;
	}
	
}
