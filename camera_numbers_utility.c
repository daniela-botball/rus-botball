/*
 * RUN the Camera numbers utility (that shows all the numbers
 * for the biggest blobs of the selected color_model).
 *
 * Written by Aaron and David Mutchler, June 2013.
 */
 
#include "in_progess_2/camera_utilities.h"

// FIXME: include the library file that has press_A_to_continue
void press_A_to_continue();

int main() {
	app_to_display_blob_numbers();
	
	return 0;
}

void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backwards_for_camera_search() {}
void move_forwards_for_camera_search() {}
void stop_camera_search() {}

// FIXME: Replace the following by the standard version.
void press_A_to_continue()
{
	printf("Press the A button to continue\n");
	
	while (! a_button()) ; // Wait for A button to be pressed
	
	printf("Hands off!\n");
	while (a_button()) ;   // Wait for hands off A button
	
	msleep(.5);	// To allow their hand to get away from the screen
}
