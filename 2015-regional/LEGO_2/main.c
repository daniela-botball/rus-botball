// Created on Thu April 2 2015

#include "legoMovement.h"
#include "universal.h"
#include "lineFollow.h"

//#define OPEN 555
//#define CLOSE 1235
#define SCOOP_UP_POSITION 2000
#define SCOOP_REST_POSITION 248
#define SCOOP_DOWN_POSITION 65
#define NINETY_DEGREES 800
#define ONE_EIGHTY_DEGREES 1600
#define HALF 1500
#define TO_MIDDLE_OF_BOARD 5300
#define TO_THE_OTHER_SIDE_OF_BOARD 11400
#define FAST 100
#define HALF_A_SEC 500
#define PORT 0
#define A_LITTLE_BIT_BACKWARDS 4000
#define ZERO 0



void sample_run();
void turn_test();
void move_servo_slowly(int servo, int position);
void start();
void score_gold_poms();
void follow_wide_black_tape_backwards();

int main()
{
	analog_et(2);
	
	start();
	
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
	
	score_gold_poms();
	
	return 0;
}

void score_gold_poms() {
	// Go forward until at least one of the two reflectance sensors
	// sees the black line that goes under the Mesa.
	motor(LEFT_MOTOR, 100);
	motor(RIGHT_MOTOR, 100);
	
	while (TRUE) {
		if (analog(L_TOPHAT) > 750 || analog(R_TOPHAT) > 750) {
			freeze(LEFT_MOTOR);
			freeze(RIGHT_MOTOR);
			break;
		}
	}
	
	press_a_to_continue();
	lego_drive_distance(FORWARDS, 3, 100);
	press_a_to_continue();
	
	lego_spin_degrees(RIGHT, 850, 80);
	press_a_to_continue();
		
	line_follow(FORWARDS, 20, STOP_BY_CAMERA);
	
	// Make the robot move so that both reflectance sensors are
	// on the black line that goes under the Mesa.
	
	// Spin clockwise until both reflectance sensors see white.
	// At this point, those sensors should straddle the black line
	// that goes under the Mesa.
	
	// Line follow to the pink/blue tape (the one that marks the
	// edge of our side).
	
	// Continue until the line sensors are both just past the pink/blue tape,
	// using a technique similar to how the robot straddled the black line
	// in a previou step.
	
	// Dead-reckon the turn enough to get onto the fat black line.
	
	// Line follow, scooping poms.  Get the poms into the scoop.
	
	// Line follow backwards (hopefully) until the right point.
	// Dump to the bin.
	
	// Turn 180.
	
	// Do the other side of poms.
}

void old() {
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

void start() {
	set_mode(PRACTICE_MODE);
	initialize_camera();
	
	set_servo_position(PORT, SCOOP_REST_POSITION);
	enable_servos();
	
	press_a_to_continue();
	
	
	//Starts in middle of board
}

void turn_test(){
	clear_motor_position_counter(RIGHT_MOTOR);
	motor(LEFT_MOTOR, 30);
	motor(RIGHT_MOTOR, -30);
	while (digital(15) == 0);
	ao();
	int ticks = get_motor_position_counter(RIGHT_MOTOR);
	printf("ticks traveled: %i\n", ticks);
}
//void up_and_down_







// Demonstrate the use of the Create movement library.
/*void sample_run() {
	// Wait briefly to allow user to take finger off the Link.
	msleep(1000);
	
	// Spin somewhat slowly right (clockwise) until the sensor
	// in analog port TOPHAT_PORT sees BLACK_TAPE.  (See #define
	// statements above for TOPHAT_PORT and BLACK_TAPE).
	// Assumes that the sensor is a little tophat (reflectance) sensor
	// placed the "right" distance (per the BLACK_TAPE number) from the surface.
	motor(LEFT_MOTOR, 10);
	motor(RIGHT_MOTOR, -10);
	
	while (TRUE) {
		if (analog(TOPHAT_PORT) >= BLACK_TAPE) {
			break;
		}
	}
	freeze(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
	
	return;
	
	// Lego movement commands start here.
	// Sleeps in between are just so that
	// the user can see the effects of each command.
	
	// Go forwards 2000 ticks at half (50) power.
	lego_drive_distance(FORWARDS, 2000, 50);
	msleep(2000);
	
	// Go backwards 1000 ticks at full (100) power.
	lego_drive_distance(BACKWARDS, 1000, 100);
	msleep(2000);
	
	// Spin left 300 ticks at slow (20) power.
	lego_spin_degrees(LEFT, 300, 20);
	msleep(2000);
	
	// Spin right 1000 ticks at full (100) power.
	lego_spin_degrees(RIGHT, 1000, 100);
	msleep(2000);
}
*/
void move_servo_slowly(int servo, int position) {
	int starting_position = get_servo_position(servo);
	int current_position = starting_position;
	if (position > starting_position) {
		for (current_position = starting_position; current_position <= position; current_position = current_position + 5) {
			set_servo_position(servo, current_position);
			msleep(20);
		}			
	} else if (position < starting_position) {
		for (current_position = starting_position; current_position >= position; current_position = current_position - 5) {
			set_servo_position(servo, current_position);
			msleep(20);
		}
	} else if (position == starting_position) {
		return;
	}
	set_servo_position(servo, position);
}
