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

// TODO:
//  Fix hand so that it is symmetric.
//  Make hand sturdier.  Reverse the axle with stop.  Etc.
//  The hand is sort of upside down.  Should the fingers be more at the half-way point of the foam board?  Or would that block the camera?
//  Make the arm_up function smooth:  enough power, but not too fast, consider varying power as it rises?
//  Make the arm_up function stop at the right points somehow.
//  The library should allow the Create to specify either side as the "front".

// Failure points to check:
//  servo extender wire coming disconnected.
//  fishing wire getting too loose or tangled or off the winch.

void score_our_cubes();

int main()
{
	printf("OK\n");
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
	create_drive_until_bump(BACKWARDS, 20);
	
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
