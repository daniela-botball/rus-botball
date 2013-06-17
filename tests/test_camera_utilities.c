/*
 * TEST the Camera utilities.
 *
 * Written by Aaron and David Mutchler, June 2013.
 */
 
#include "../camera_utilities.h"

// FIXME: include the library file that has press_A_to_continue
void test_move_so_blob_is_at_x();
void test_move_so_blob_is_at_y();
void test_app_to_display_blob_numbers();
void press_A_to_continue();

int main() {
	test_move_so_blob_is_at_x();
	msleep(3000);
	test_app_to_display_blob_numbers();
	//test_move_so_blob_is_at_y();
	return 0;
}

void test_app_to_display_blob_numbers() {
	printf("Testing app_to_display_blob_numbers\n");
	press_A_to_continue();
	
	app_to_display_blob_numbers();
}

void test_move_so_blob_is_at_x() {
	printf("Testing move_so_blob_is_at_x\n");
	create_connect();
	press_A_to_continue();
	
	camera_open(LOW_RES);
	move_so_blob_is_at_x(0, 73, 2, 300);
}

void test_move_so_blob_is_at_y() {
	printf("Testing move_so_blob_is_at_y\n");
	create_connect();
	press_A_to_continue();
	
	camera_open(LOW_RES);
	move_so_blob_is_at_y(0, 23, 1, 50);
}

/*
void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backward_for_camera_search() {}
void move_forward_for_camera_search() {}
void stop_camera_search() {}
*/

void spin_left_for_camera_search() { create_spin_CCW(5); }
void spin_right_for_camera_search() { create_spin_CW(5); }
void move_backwards_for_camera_search() { create_drive_straight(10); }
void move_forwards_for_camera_search() { create_drive_straight(-10); }
void stop_camera_search() { create_stop(); }

// FIXME: Replace the following by the standard version.
void press_A_to_continue()
{
	printf("Press the A button to continue\n");
	
	while (! a_button()) ; // Wait for A button to be pressed
	
	printf("Hands off!\n");
	while (a_button()) ;   // Wait for hands off A button
	
	msleep(.5);	// To allow their hand to get away from the screen
}
