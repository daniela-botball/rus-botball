// Set the following constant per what is plugged in where.

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2

#define LEFT_LINE_SENSOR_PORT 5
#define RIGHT_LINE_SENSOR_PORT 6

// Tune the following constants as needed.
#define LINE_FOLLOWING_NORMAL_SPEED 10
#define LINE_FOLLOWING_MINIMUM_SPEED 5
#define LINE_FOLLOWING_MAXIMUM_SPEED 100

#define LEFT_LINE_SENSOR_DESIRED_VALUE 100
#define RIGHT_LINE_SENSOR_DESIRED_VALUE 100
#define kP 0.5

#define TRUE 1
#define FALSE 0

// Follow a black line.
// Assumes two sensors:
//   -- LEFT_LINE_SENSOR controlling the LEFT_MOTOR speed
//   -- RIGHT_LINE_SENSOR controlling the RIGHT_MOTOR speed
// This code assumes a LEGO robot.
void follow_black_line() {
	int left_sensor_current_value, right_sensor_current_value;
	int left_error, right_error;
	float left_speed, right_speed;
	
	// Turn on the left and right motors.
	motor(LEFT_MOTOR, LINE_FOLLOWING_NORMAL_SPEED);
	motor(RIGHT_MOTOR, LINE_FOLLOWING_NORMAL_SPEED);

	while (TRUE) {
		// The following IF determines when you want line-following to stop.
		// Put it where you want in this WHILE loop.
		// Replace FALSE by the condition that, if true, should cause line-following to stop.
		if (FALSE) {
			break;
		}
		
		// Determine the "errors" -- how far the sensors are from their desired values.
		left_sensor_current_value = analog(LEFT_LINE_SENSOR_PORT);
		right_sensor_current_value = analog(RIGHT_LINE_SENSOR_PORT);
		
		left_error = LEFT_LINE_SENSOR_DESIRED_VALUE - left_sensor_current_value;
		right_error = RIGHT_LINE_SENSOR_DESIRED_VALUE - right_sensor_current_value;
		
		// Adjust the motor speeds proportionately to the errors.
		left_speed = LINE_FOLLOWING_NORMAL_SPEED + (left_error * kP);
		if (left_speed < LINE_FOLLOWING_MINIMUM_SPEED) {
			left_speed = LINE_FOLLOWING_MINIMUM_SPEED;
		} else if (left_speed > LINE_FOLLOWING_MAXIMUM_SPEED) {
			left_speed = LINE_FOLLOWING_MAXIMUM_SPEED;
		}
		
		right_speed = LINE_FOLLOWING_NORMAL_SPEED + (right_error * kP);
		if (right_speed < LINE_FOLLOWING_MINIMUM_SPEED) {
			right_speed = LINE_FOLLOWING_MINIMUM_SPEED;
		} else if (right_speed > LINE_FOLLOWING_MAXIMUM_SPEED) {
			right_speed = LINE_FOLLOWING_MAXIMUM_SPEED;
		}
		
		motor(LEFT_MOTOR, (int) left_speed);
		motor(RIGHT_MOTOR, (int) right_speed);
	}
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

/**
// PID controller.
void PID(controller, ) {
	// Read the sensor.
	current_value = SENSOR;

	// Compute error E, change in error dE, and sum of errors sE.
	E = desired_value - current_value;
	dE = E - previous_E - E;
	sE = 0; // FIXME 
	
	// Compute the control value.  Send it to the controller.
	control = (kP * E) + (kD * dE) + (kE * sE);
	controller(control);
	
	// Prepare for next iteration of the loop.
	previous_E = E;
}

void controller(double control) {
}
**/
