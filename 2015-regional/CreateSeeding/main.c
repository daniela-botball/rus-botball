// Created on Thu April 2 2015

#include "createMovement.h"

void sample_run();

int main()
{
	sample_run();
	
	return 0;
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
