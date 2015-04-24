// Created on Thu April 2 2015

#include "legoMovement.h"
#include "universal.h"
#include "lineFollow2.h"

#define STARTING_LIGHT_PORT 3

//#define OPEN 555
//#define CLOSE 1235
#define SCOOP_UP_POSITION 1600 //2047
#define SCOOP_REST_POSITION 220
#define SCOOP_START_POSITION SCOOP_DOWN_POSITION
#define SCOOP_TURN_POSITION 975 //1120
#define SCOOP_DOWN_POSITION 120
#define NINETY_DEGREES 800
#define ONE_EIGHTY_DEGREES 1400
#define HALF 1500
#define TO_MIDDLE_OF_BOARD 5300
#define TO_THE_OTHER_SIDE_OF_BOARD 11400
#define FAST 100
#define HALF_A_SEC 500
#define PORT 0
#define A_LITTLE_BIT_BACKWARDS 4000
#define ZERO 0

void start();
void score_gold_poms();
void move_servo_slowly(int servo, int position);

int main() {
	// Things to happen BEFORE lights-off:
	start();
	
	// Lights turn on at this point:
	score_gold_poms();
	
	return 0;
}

// Things to happen BEFORE lights-off.
void start() {
	
	initialize_camera();
	
	// Human operator selects TOURNAMENT or PRACTICE mode.
	set_mode(ask_for_mode());
	pause_for_sure();
	
	// Set the robot into its starting position.
	// The human operator should:
	//   -- Put the robot under the Create arm so that it:
	//        -- Fits comfortably with the Create (no interference).
	//        -- Is in the starting box when the First put the robot in the corner, turned so that its claw is grabbing on the starting line.
	set_servo_position(PORT, SCOOP_START_POSITION);
	enable_servos();
	
	pause_for_sure();
	
	// Now the starting-light protocol:
	// wait_for_light(STARTING_LIGHT_PORT);
	
	if (_MODE == TOURNAMENT_MODE) {
		_ADJUST = FALSE;
		wait_for_light(3);
		shut_down_in(119);
	} else {
		_ADJUST = TRUE;
	}
}



void score_gold_poms() {
	
	// Raise the scoop to its moving position.
	// Go forward until the left sensor sees the black line that goes under the Mesa.
	set_servo_position(PORT, SCOOP_REST_POSITION);
	drive_until(FORWARDS, 100, L_TOPHAT, greater_than, LEFT_SENSOR_ON_BLACK_DIVIDER - 100);
	press_a_to_continue();
	
	// Move into the cave
	lego_drive_distance(FORWARDS, 6, 100);
	press_a_to_continue();
	
	lego_spin_degrees(RIGHT, 800, 80);
	press_a_to_continue();
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_FRP, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_FRP,
						LEFT_kP_FOR_FRP, RIGHT_kP_FOR_FRP, ET_stop);
						
	press_a_to_continue();
	
	lego_drive_distance(FORWARDS, 13, 30);
	press_a_to_continue();
	
	//Adjust onto black line
	lego_spin_degrees(LEFT, 425, 80); // Was RIGHT (instead of left)
	press_a_to_continue();
	
	drive_until(FORWARDS, 100, L_TOPHAT, greater_than, LEFT_SENSOR_ON_BLACK_DIVIDER - 100); // This line and the next line are reversed to switch the direction
	drive_until(FORWARDS, 100, R_TOPHAT, greater_than, RIGHT_SENSOR_ON_BLACK_DIVIDER - 100);
	
	lego_drive_distance(FORWARDS, 6, 40);
	press_a_to_continue();
	
	lego_spin_degrees(LEFT, 300, 80); // Was RIGHT
	press_a_to_continue();
	set_servo_position(PORT, SCOOP_DOWN_POSITION);
	msleep(200);
	
	// Pick up first four poms
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, camera_stop);
	lego_drive_distance(FORWARDS, 3, 40);
						
	// Drop of first four poms
	lego_drive_distance(BACKWARDS, 7, 20);
	move_servo_slowly(PORT, SCOOP_TURN_POSITION); 
	lego_drive_distance(FORWARDS, 13, 30);
	lego_spin_degrees(LEFT, ONE_EIGHTY_DEGREES, 40);
	
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, wall_opening_stop);
						
	
	lego_drive_distance(FORWARDS, 32, 80);				
	/*follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, ET_stop);*/
	
	move_servo_slowly(PORT, SCOOP_UP_POSITION);
	msleep(2000);
	
	// On to the second set of four poms
	
	move_servo_slowly(PORT, SCOOP_DOWN_POSITION);
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, time_stop);
						
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, camera_stop);
	lego_drive_distance(FORWARDS, 3, 40);
						
	// Drop of second four poms
	lego_drive_distance(BACKWARDS, 7, 20);
	move_servo_slowly(PORT, SCOOP_TURN_POSITION); 
	lego_drive_distance(FORWARDS, 13, 30);
	lego_spin_degrees(LEFT, ONE_EIGHTY_DEGREES, 40);
	
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, wall_opening_stop);
						
	
	lego_drive_distance(FORWARDS, 32, 80);				

	
	move_servo_slowly(PORT, SCOOP_UP_POSITION);
	msleep(5000);
	
						
}


void move_servo_slowly(int servo, int position) {
	int starting_position = get_servo_position(servo);
	int current_position = starting_position;
	if (position > starting_position) {
		for (current_position = starting_position; current_position <= position; current_position = current_position + 5) {
			set_servo_position(servo, current_position);
			msleep(15);
		}			
	} else if (position < starting_position) {
		for (current_position = starting_position; current_position >= position; current_position = current_position - 5) {
			set_servo_position(servo, current_position);
			msleep(15);
		}
	} else if (position == starting_position) {
		return;
	}
	set_servo_position(servo, position);
}
