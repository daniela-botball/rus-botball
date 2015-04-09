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
