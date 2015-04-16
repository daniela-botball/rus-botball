// Created on Thu April 2 2015

#include "createMovement.h"
#include "universal.h"
#include "tournamentFunctions.h"

// TODO: (talk to your coach about EACH of these before doing them)
//  Learn and practice the new   adjust   function.
//  Put comments in   score_our_cubes   for each major action (which will be a chunk of code).
//  Continue pushing actions forward:
//    -- Score 2 cubes on our starting zone line
//    -- Score 2 cubes on opponent's starting zone line
//    -- Score cube and two poms on Mesa.
//    -- Then ??
//  The library should allow the Create to specify either side as the "front".
// Failure points to check:
//  servo extender wire coming disconnected.
//  fishing wire getting too loose or tangled or off the winch.

/*
Create score the last 3 cubes.
Aaron will make mechanical changes Saturday.
Lego robot -- push it forward.
*/
void score_our_cubes();
void demo_adjust_functions();

int main()
{
	// demo_adjust_functions();

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
	
	//lights on
	
	//grab the cubes
	create_spin_degrees(LEFT, 18, 20); 
	operate_winch(WINCH_GROUND_POSITION);

	create_drive_distance(FORWARDS, 8, 10);
	close_claw();
		
	//score our cubes
	create_spin_degrees(LEFT, 28, 20);
	operate_winch(WINCH_DROP_POSITION);
	
	create_drive_distance(FORWARDS, 64, 20);
	open_claw();
	
	//set_mode(PRACTICE_MODE);
	
	//back from bin
	create_drive_until_event(BACKWARDS, 20, BUMP); // TODO:  DOES THIS WORK???????????????????????????????
	
	//create_drive_until_bump(BACKWARDS, 20);
	
	//other side of board
	create_spin_degrees(RIGHT, 136, 20);
	create_drive_distance(FORWARDS, 5, 5);
	operate_winch(WINCH_MIDDLE_POSITION);
	create_drive_until_bump(BACKWARDS, 20);
	
	operate_winch(WINCH_DROP_POSITION);
	create_spin_degrees(LEFT, 90, 20);
	press_a_to_continue();
	create_drive_until_bump(BACKWARDS, 20);
	press_a_to_continue();
	create_spin_degrees(RIGHT, 90, 20);
	create_drive_distance(FORWARDS, 6, 20);
	create_spin_degrees(LEFT, 90, 20);
	create_drive_distance(FORWARDS, 65, 20);
	create_drive_distance(BACKWARDS, 8, 20);
	operate_winch(WINCH_GROUND_POSITION);
	create_spin_degrees(RIGHT, 5, 20);
	msleep(500);
	close_claw();
	// The next lines have NOT been tested yet
	
	create_spin_degrees(LEFT, 5, 20);
	create_drive_until_bump(BACKWARDS, 20);
	return;
}

void demo_adjust_functions() {
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	set_mode(PRACTICE_MODE);
	_ADJUST = TRUE;
	
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION); // TODO: Make claw open slower
	enable_servos();
	
	// Demo adjusting forwards / backwards:
	create_drive_distance(FORWARDS, 10, 50);
	create_drive_distance(BACKWARDS, 15, 30);
	
	// Demo adjusting left / right:
	create_spin_degrees(LEFT, 90, 20);
	create_spin_degrees(RIGHT, 30, 50);
	
	// Demo adjusting claw servo:
	close_claw();
	
	// Demo adjusting winch motor:
	operate_winch(WINCH_MIDDLE_POSITION);
	
	disable_servos();
	create_disconnect();
}
