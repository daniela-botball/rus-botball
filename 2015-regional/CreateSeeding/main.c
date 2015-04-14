// Created on Thu April 2 2015

#include "createMovement.h"
#include "universal.h"
#include "tournamentFunctions.h"

// TODO: (talk to your coach about EACH of these before doing them)
//  DONE Try all, see if works, decide what needs to be fixed asap.
//  Learn and practice the new   adjust   function.
//  Put comments in   score_our_cubes   for each major action (which will be a chunk of code).
//  Have robot set itself up for the run.
//  Have robot pull Botgal down early (so other robot can use Bot-thing)
//  Have robot score the cube and poms on the Mesa (just after doing Botguy, or ...?)

void score_our_cubes();

int main()
{
	set_mode(PRACTICE_MODE);
	score_our_cubes();
	
	return 0;
}

void score_our_cubes() {
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	open_claw();
	enable_servos();
	operate_winch(WINCH_MIDDLE_POSITION);
	press_a_to_continue();
	//lights on
	
	//grab the cubes
	create_spin_degrees(LEFT, 18, 20); 
	operate_winch(WINCH_GROUND_POSITION);

	create_drive_distance(FORWARDS, 6, 10);
	close_claw();
		
	//score our cubes
	create_spin_degrees(LEFT, 28, 20);
	operate_winch(WINCH_DROP_POSITION);
	
	create_drive_distance(FORWARDS, 66, 20);
	open_claw();
	
	//set_mode(PRACTICE_MODE);
	
	create_drive_until_bump(BACKWARDS, 20);
	
	operate_winch(WINCH_MIDDLE_POSITION);
	press_a_to_continue();
	
	create_spin_degrees(RIGHT, 136, 20);
	create_drive_distance(FORWARDS, 5, 5);
	create_drive_until_bump(BACKWARDS, 10);
	operate_winch(WINCH_DROP_POSITION);
	create_spin_degrees(LEFT, 90, 20);
	create_drive_until_bump(BACKWARDS, 20);
	create_spin_degrees(LEFT, 90, 20);
	create_drive_distance(FORWARDS, 5, 5);
	create_drive_distance(BACKWARDS, 10, 20);
	create_spin_degrees(RIGHT, 90, 20);
	create_drive_distance(FORWARDS, 55, 20);
	create_spin_degrees(RIGHT, 10, 20);
	operate_winch(WINCH_GROUND_POSITION);
	close_claw();
	operate_winch(WINCH_DROP_POSITION);
	create_spin_degrees(LEFT, 10, 20);
	create_drive_distance(BACKWARDS, 45, 20);
	create_spin_degrees(RIGHT, 45, 20);
	create_drive_distance(FORWARDS, 54, 20);
	open_claw();
	
	return;
}
/*
	create_drive_distance(BACKWARDS,61,10);
	msleep(5000);
	create_spin_degrees(RIGHT,10,10);
	set_servo_position(HAND,OPEN);
	msleep(15000);
	//set_servo_position(ARM,FLOOR);
	set_servo_position(HAND,CLOSE);
	msleep(1000);
	create_spin_degrees(LEFT,10,10);
	msleep(15000);
	create_drive_distance(FORWARDS,30,10);
	create_spin_degrees(RIGHT,50,10);
	create_drive_distance(BACKWARDS,50,10);
	//set_servo_position(ARM,HIGH);
	return;
}

// Demonstrate the use of the Create movement library.
void sample_run() {
	// Connect to the Create.
	// Set to "full mode" so that it does not stop when its wheels "drop".
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	set_servo_position(HAND,CLOSE);
	enable_servos();
	create_drive_distance(BACKWARDS,61,10);
	msleep(5000);
	create_spin_degrees(RIGHT,10,10);
	set_servo_position(HAND,OPEN);
	msleep(15000);
	//set_servo_position(ARM,FLOOR);
	set_servo_position(HAND,CLOSE);
	msleep(1000);
	create_spin_degrees(LEFT,10,10);
	msleep(15000);
	create_drive_distance(FORWARDS,30,10);
	create_spin_degrees(RIGHT,50,10);
	create_drive_distance(BACKWARDS,50,10);
	//set_servo_position(ARM,HIGH);
	return;
	create_drive_distance(FORWARDS,10,10);
	create_spin_degrees(RIGHT,10,10);
	create_drive_distance(BACKWARDS,10,10);
	create_spin_degrees(LEFT,10,10);
	//set_servo_position(HAND,OPEN);
	msleep(1000);
	return ;
	// Wait briefly to allow user to take finger off the Link.
	
	// Create movement commands start here.
	// Sleeps in between are just so that
	// the user can see the effects of each command.
	
	// Go forwards 40 centimeters at 20 centimeters a second.
	// (Max speed is 50 centimeters a second.)
	create_drive_distance(FORWARDS, 40, 20);
	msleep(2000);
	
	// Go backwards 30 centimeters at 50 centimeters a second.
	create_drive_distance(BACKWARDS, 30, 50);
	msleep(2000);
	
	// Spin left 90 degrees at 45 degrees a second.
	// (Max speed is about ?? degrees a second.)
	// DCM: Is the speed accurate??
	create_spin_degrees(LEFT, 90, 45);
	msleep(2000);
	
	// Spin right 720 degrees (2 full turns) at 180 degrees a second.
	// (Max speed is about ?? degrees a second.)
	// DCM: Is the speed accurate??
	create_spin_degrees(LEFT, 720, 180);
	msleep(2000);
	
	// The following leaves the Create in a "clean" state
	// after the run.
	create_disconnect();
}
*/
