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
#define SCOOP_DOWN_POSITION 135
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
	lego_spin_degrees(RIGHT, 425, 80);
	press_a_to_continue();
	
	drive_until(FORWARDS, 100, R_TOPHAT, greater_than, RIGHT_SENSOR_ON_BLACK_DIVIDER - 100);
	drive_until(FORWARDS, 100, L_TOPHAT, greater_than, LEFT_SENSOR_ON_BLACK_DIVIDER - 100);
	lego_drive_distance(FORWARDS, 6, 40);
	press_a_to_continue();
	
	lego_spin_degrees(RIGHT, 300, 80);
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
	lego_drive_distance(FORWARDS, 10, 30);
	lego_spin_degrees(LEFT, ONE_EIGHTY_DEGREES, 40);
	
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, wall_opening_stop);
						
	
	lego_drive_distance(FORWARDS, 32, 80);				
	/*follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, ET_stop);*/
	
	move_servo_slowly(PORT, SCOOP_UP_POSITION); //set_servo_position(PORT, SCOOP_UP_POSITION);
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
	lego_drive_distance(FORWARDS, 10, 30);
	lego_spin_degrees(LEFT, ONE_EIGHTY_DEGREES, 40);
	
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	
	follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, wall_opening_stop);
						
	
	lego_drive_distance(FORWARDS, 32, 80);				
	/*follow_black_line(LINE_FOLLOWING_NORMAL_SPEED, LINE_FOLLOWING_MINIMUM_SPEED, LINE_FOLLOWING_MAXIMUM_SPEED,
						LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE, RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE,
						LEFT_kP_FOR_WIDE_TAPE, RIGHT_kP_FOR_WIDE_TAPE, ET_stop);*/
	
	move_servo_slowly(PORT, SCOOP_UP_POSITION); //set_servo_position(PORT, SCOOP_UP_POSITION);
	msleep(5000);
	
						
}

/*
int main()
{
	start();
	score_gold_poms();
	
	return;
	
	move_servo_slowly(PORT, 1100);
	
	lego_drive_distance(FORWARDS, 20, 30);
	
	clear_motor_position_counter(LEFT_MOTOR);
	motor(LEFT_MOTOR, -80);
	motor(RIGHT_MOTOR, 80);
	while (get_motor_position_counter(LEFT_MOTOR) > -1550) {}
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
	
	move_servo_slowly(PORT, 248);
	line_follow(FORWARDS, 60, STOP_BY_ET);
	
	//wall_follow(BACKWARDS, 40, STOP_BY_TOPHAT);
	//follow_wide_black_tape_backwards();
	return 0;
	
	
	
	return 0;
}

ld() {
	set_servo_position(PORT, SCOOP_DOWN_POSITION);
	msleep(1000);
	line_follow(FORWARDS, 60, STOP_BY_CAMERA);
	lego_drive_distance(BACKWARDS, 8, 20);
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	line_follow(BACKWARDS, 40, STOP_BY_ET);
	set_servo_position(PORT, SCOOP_UP_POSITION);
	msleep(4000);
	move_servo_slowly(PORT, SCOOP_REST_POSITION);
	lego_drive_distance(FORWARDS, 5, 20);
	move_servo_slowly(PORT, SCOOP_UP_POSITION);
	lego_spin_degrees(RIGHT, 1600, 20);
	//Put wait for light code here
	wall_follow(FORWARDS, 40, STOP_BY_TOPHAT);
	adjust_onto_line(FORWARDS);
	press_a_to_continue();
	lego_drive_distance(BACKWARDS, 1, 40);
	lego_spin_degrees(LEFT, 1100, 40);
	lego_drive_distance(BACKWARDS, 45, 40);
	lego_spin_degrees(LEFT, 800, 40);
	
	
	printf("i was made by hannah gabriel and john leschorn \n");
	set_servo_position(PORT, SCOOP_REST_POSITION);
	enable_servos();
	
	//to center line
	lego_drive_distance(FORWARDS, TO_MIDDLE_OF_BOARD, FAST);
	//turn right 90
	lego_spin_degrees(RIGHT, NINETY_DEGREES, FAST);
	//to middle line
	lego_drive_distance(FORWARDS, TO_MIDDLE_OF_BOARD, FAST);
	//turn right 90
	move_servo_slowly(PORT, SCOOP_DOWN_POSITION);
	lego_spin_degrees(RIGHT, NINETY_DEGREES, FAST);//mabye NINETY_DEGREES 
	//drive down center
	lego_drive_distance(FORWARDS, TO_MIDDLE_OF_BOARD, FAST);
	//it close arms
	lego_drive_distance(BACKWARDS, A_LITTLE_BIT_BACKWARDS, FAST);
	move_servo_slowly(PORT,SCOOP_UP_POSITION);
	move_servo_slowly(PORT,SCOOP_DOWN_POSITION);
	lego_spin_degrees(RIGHT, ONE_EIGHTY_DEGREES, FAST);
	//move's to the ather side
	lego_drive_distance(FORWARDS, 5300, FAST);
	//it move's it arme up
	lego_drive_distance(BACKWARDS, A_LITTLE_BIT_BACKWARDS, FAST);
	move_servo_slowly(PORT,SCOOP_UP_POSITION);
	msleep(HALF_A_SEC);
	
	press_a_to_continue();
	printf("the end good bye\n");
	ao();
	
}
*/
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
