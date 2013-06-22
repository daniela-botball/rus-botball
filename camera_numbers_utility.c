/*
 * RUN the Camera numbers utility (that shows all the numbers
 * for the biggest blobs of the selected color_model).
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

// CONSIDER: Change the following when the libraries move.
#include "in_progress_2/camera_library.h"
#include "in_progress_2/universal_library.h"
int main() {
	int status;
	
	status = initialize_camera(LOW_RES);
	if (status == FAILURE) return 1;
	
	app_to_display_blob_numbers();
	
	return 0;
}

void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backwards_for_camera_search() {}
void move_forwards_for_camera_search() {}
void stop_camera_search() {}
