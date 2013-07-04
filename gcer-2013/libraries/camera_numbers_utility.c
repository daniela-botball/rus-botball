/*
 * RUN the Camera numbers utility (that shows all the numbers
 * for the biggest blobs of the selected color_model).
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

// CONSIDER: Change the following when the libraries move.
#include "universal_library.h"
#include "gui_library.h"
#include "camera_show_numbers_library.h"

int main() {
	int status;
	
	status = camera_open(LOW_RES);
	if (status == FAILURE) {
		printf("Could not open the camera.\n");
		return ABNORMAL_EXIT;
	}
	
	app_to_display_blob_numbers(DEFAULT_FIRST_LINE, DEFAULT_NUMBER_OF_BLOBS_TO_SHOW);
	return NORMAL_EXIT;
}
