// Created on Thu April 2 2015

#include "createMovement.h"

#define CLOSED_FOR_CUBES 800
#define OPEN 1500
#define CLOSED_FOR_BOTGAL 900
#define CLOSED_FULLY 830

#define HAND 0
#define ARM 0

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

void seeding();
void sample_run();
void move_arm_to_rest_position();
void press_a_to_continue();
void arm_up();
void arm_down();

int main()
{
	seeding();
	
	return 0;
}

void seeding() {
	printf("Connecting to the Create...\n");
	create_connect();
	printf("Connected!\n");
	
	set_servo_position(HAND, CLOSED_FULLY);
	enable_servos();
	press_a_to_continue();
	
	create_spin_degrees(RIGHT, 10, 10);
	press_a_to_continue();

	set_servo_position(HAND, OPEN);
	press_a_to_continue();

	arm_up();
	press_a_to_continue();

	create_spin_degrees(RIGHT, 10, 10);
	press_a_to_continue();

	arm_down();
	press_a_to_continue();
	
	set_servo_position(HAND, CLOSED_FOR_CUBES);
	press_a_to_continue();
	
	arm_up();
	press_a_to_continue();
	
	create_spin_degrees(RIGHT, 35, 20);
	press_a_to_continue();
	
	create_drive_distance(BACKWARDS, 55, 25);
	press_a_to_continue();
	
	set_servo_position(HAND, OPEN);
	press_a_to_continue();
	
	disable_servos();
	create_disconnect();
}

// Makes the Create move forward slowly,
// centering the z
void camera_move_to_x(int desired_x) {
}

void arm_up() {
	motor(ARM, 100);
	while (!a_button()) {}
	off(ARM);
}

void arm_down() {
	motor(ARM, -30);
	while (!a_button()) {}
	off(ARM);
}

void press_a_to_continue() {
	printf("Press A to continue.\n");
	while (!a_button()) {}
	while (a_button()) {}
	msleep(1000);
}

// Demonstrate the use of the Create movement library.
void sample_run() {
	set_servo_position(3,2000);
	enable_servos();
	msleep(2000);
	// Connect to the Create.
	// Set to "full mode" so that it does not stop when its wheels "drop".
	printf("Trying to connect...\n");
	create_connect();
	create_full();
	printf("Connected.\n");
	
	// Wait briefly to allow user to take finger off the Link.
	msleep(1000);
	
	// Create movement commands start here.
	// Sleeps in between are just so that
	// the user can see the effects of each command.
	
	//Drive backwards 20 centimeters at 10 centimeters a second.
	//(Mas speed is 50 centimeters a second.)
	create_drive_distance(BACKWARDS, 20, 10);
	msleep(1000);
	
	//Spin right 90 degrees at 45 degrees a second.
	//(Max speed is ?? degrees a second.)
	//DCM: Is the speed accurate??
	create_spin_degrees(RIGHT, 90, 45);
	
	// Go backwards 60 centimeters at 30 centimeters a second.
	// (Max speed is 50 centimeters a second.)
	create_drive_distance(BACKWARDS, 60, 30);
	msleep(1000);
	
	 // Spin left 90 degrees at 45 degrees a second.
	// (Max speed is about ?? degrees a second.)
	// DCM: Is the speed accurate??
	// It will knock over Podd Guy
	create_spin_degrees(LEFT, 90, 45);
	msleep(1000);
	
     // Spin left  90 degrees at 45 degrees a second.
	// (Max speed is about ?? degrees a second.)
	// DCM: Is the speed accurate??
	create_spin_degrees(LEFT, 90, 45);
	msleep(1000);
		
   
	
	// Go backwards 40 centimeters at 20 centimeters a second.
	// It will halt in front of cubes
	create_drive_distance(BACKWARDS, 40, 20);
	msleep(1000);
	
	
	// The following leaves the Create in a "clean" state
	// after the run.
	create_disconnect();
}
