/*
 * Camera utilities:
 *   -- display_blob_numbers
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

#ifndef _CAMERA_UTILITIES_H_
#define _CAMERA_UTILITIES_H_

#include <string.h>

#define NUMBER_OF_BLOBS_TO_SHOW 4
#define INITIAL_MILLISECONDS_BETWEEN_PICTURES 2000
#define ERROR_MESSAGE_LINE (2 + NUMBER_OF_BLOBS_TO_SHOW + 1)
#define BLANK_LINE "                                          "
#define MAX_ERRORS_ALLOWED_WHEN_OPENING_CAMERA 4
#define MAX_ERRORS_ALLOWED_BEFORE_FIRST_PICTURE 50
#define SUCCESS 1
#define FAILURE 0
#define LARGEST_BLOB 0
#define LOOP_DELAY 50 // sleep this many milliseconds between camera updates

// Functions intended to be ** PUBLIC **:
int initialize_camera(int resolution);
int move_so_blob_is_at_x(int color_model, int x, int delta, int minimum_area);
int move_so_blob_is_at_y(int color_model, int y, int delta, int minimum_area);
void app_to_display_blob_numbers();
void display_blob_numbers(int color_model, int blob, int header_line, int data_line);

// Functions intended to be ** PRIVATE **:
void _initialize_buttons();
void _display_model_and_resolution(int color_model, int resolution);

void _take_a_picture();
void _process_buttons(int* color_model, int* milliseconds_between_pictures);

// Functions that must be defined elsewhere for the move... functions to work.
extern void spin_left_for_camera_search();
extern void spin_right_for_camera_search();
extern void move_backwards_for_camera_search();
extern void move_forwards_for_camera_search();
extern void stop_camera_search();

// Opens the camera at the given resolution.
// Takes some pictures to be sure that it is working correctly.
// Returns FAILURE if it cannot open the camera
// or if picture-taking is not working, else returns SUCCESS.
// Preconditions:  There must be at least one camera model on the LINK
//   and it must be able to see at least one blob.
int initialize_camera(int resolution) {
	// FIXME: Allow for either camera.
	// FIXME: Provide a default version that uses LOW_RES.
	// CONSIDER: What happens if we attempt to open an already-open camera?
	int status, error_count;
	
	printf("Make sure that:\n");
	printf("  1. The camera is attached, and\n");
	printf("  2. There is at least one camera model on the LINK, and\n");
	printf("  3. The camera can see at least one blob after you press A.\n");
	press_A_to_continue();
	
	for (k = 0; k < MAX_ERRORS_ALLOWED_WHEN_OPENING_CAMERA; ++k) {
		status = camera_open(resolution);
		if (status == SUCCESS) {
			break;
		}
		msleep(500);
		printf("Warning: Attempt %i to open the camera failed.\n", k + 1);
	}
	
	if (status == FAILURE) {
		printf("Could not open the camera.\n");
		printf("Check the 3 things listed above and try again.");
		return FAILURE;
	}
	
	if (get_channel_count() == 0) {
		printf("There are no channels in the configuration!\n");
		printf("Fix your camera configuration.\n");
		return FAILURE;
	}
	// FIXME: Finish this function.
	/*
	for (k = 0; k < MAX_ERRORS_ALLOWED_BEFORE_FIRST_PICTURE; ++k) {
		status = camera_open(resolution);
		if (status == SUCCESS) {
			break;
		}
		msleep(500);
		printf("Warning: Attempt %i to open the camera failed.\n", k + 1);
	}*/
	return SUCCESS;
}

// Spins the robot left or right until the largest blob of the given color model
// is within the given delta of the given x.  Considers only blobs whose area is
// at least the given minimum area.  Returns 1 if it accomplishes the task,
// or 0 if it does not (that is, if at any point there is no blob visible whose
// area is at least the given area).
// Preconditions: The given color model has been set on the Link, x is within
// the screen dimensions (0 to 120 at LOW_RES), and delta and minimum area are
// both non-negative.
int move_so_blob_is_at_x(int color_model, int desired_x, int delta, int minimum_area) {
	int blob_area, blob_center_x, how_many_times_no_blob_is_visible;
	
	how_many_times_no_blob_is_visible = 0;
	while (1) {
		// Take a picture and display the numbers for the biggest blob.
		_take_a_picture();
		display_blob_numbers(color_model, LARGEST_BLOB, 0, 1);
		
		// Is there a big enough blob?
		// If not, increment error-count and return failure if the count is too big.
		blob_area = get_object_area(color_model, LARGEST_BLOB);
		if (blob_area < minimum_area) {
			++ how_many_times_no_blob_is_visible;
			if (how_many_times_no_blob_is_visible > MAX_NUMBER_OF_CAMERA_ERRORS) {
				stop_camera_search();
				display_printf(0, 2, "FAILURE - I cannot see a big enough blob.");
				return 0;
			}
		} else {
		
			// Is the center of the blob within delta of the desired x?
			// If so, return success.  Otherwise, spin left or right as appropriate.
			blob_center_x = get_object_center(color_model, LARGEST_BLOB).x;
		
			if (blob_center_x >= desired_x - delta && blob_center_x <= desired_x + delta) {
				stop_camera_search();
				display_printf(0, 2, "SUCCESS - quit at %i, trying for %i", blob_center_x, desired_x);
				return 1;
			} else if (blob_center_x < desired_x - delta) {
				display_printf(0, 2, "Spin LEFT ");
				spin_left_for_camera_search();
			} else {
				display_printf(0, 2, "Spin RIGHT");
				spin_right_for_camera_search();
			}
		}
		
		// Wait a bit before taking the next picture
		msleep(LOOP_DELAY);
	}
}

int move_so_blob_is_at_y(int color_model, int desired_y, int delta, int minimum_area) {
	int blob_area, blob_center_y, how_many_times_no_blob_is_visible;
	
	how_many_times_no_blob_is_visible = 0;
	while (1) {
		// Take a picture and display the numbers for the biggest blob.
		_take_a_picture();
		display_blob_numbers(color_model, LARGEST_BLOB, 0, 1);
		
		// Is there a big enough blob?
		// If not, increment error-count and return failure if the count is too big.
		blob_area = get_object_area(color_model, LARGEST_BLOB);
		if (blob_area < minimum_area) {
			++ how_many_times_no_blob_is_visible;
			if (how_many_times_no_blob_is_visible > MAX_NUMBER_OF_CAMERA_ERRORS) {
				stop_camera_search();
				display_printf(0, 2, "FAILURE - I cannot see a big enough blob.");
				return 0;
			}
			continue;
		}
		
		// Is the center of the blob within delta of the desired x?
		// If so, return success.  Otherwise, spin left or right as appropriate.
		blob_center_y = get_object_center(color_model, LARGEST_BLOB).y;
		
		if (blob_center_y >= desired_y - delta && blob_center_y <= desired_y + delta) {
			stop_camera_search();
			display_printf(0, 2, "SUCCESS - quit at %i, trying for %i", blob_center_y, desired_y);
			return 1;
		} else if (blob_center_y < desired_y - delta) {
			display_printf(0, 2, "Move BACKWARDS");
			move_backwards_for_camera_search();
		} else {
			display_printf(0, 2, "Move FORWARDS ");
			move_forwards_for_camera_search();
		}
		
		// Wait a bit before taking the next picture
		msleep(LOOP_DELAY);
	}
}

// FIXME - write this spec
// Preconditions: The camera is open and ...
void app_to_display_blob_numbers() {
	int color_model, k, resolution, status, milliseconds_between_pictures;
	
	// Starting values of variables the user can change.
	color_model = 0;
	resolution = LOW_RES;
	milliseconds_between_pictures = INITIAL_MILLISECONDS_BETWEEN_PICTURES;
	
	_initialize_buttons();
	_display_model_and_resolution(color_model, resolution);

	while (1) {
		_take_a_picture();

		for (k = 0; k < NUMBER_OF_BLOBS_TO_SHOW; ++k) {
			display_blob_numbers(color_model, k, 1, k + 2);
		}
		
		_process_buttons(&color_model, &milliseconds_between_pictures);
		msleep(milliseconds_between_pictures);
	}
}

void _initialize_buttons() {
	extra_buttons_show();
	
	set_a_button_text("Next color mdl");
	set_b_button_text("+ Refresh rate");
	set_c_button_text("Pause / resume");
	set_x_button_text("Prev color mdl");
	set_y_button_text("- Refresh rate");
	set_z_button_text("Done");
}

void _display_model_and_resolution(int color_model, int resolution) {
	char resolution_string[100];
	
    if (resolution == LOW_RES) {
		strcpy(resolution_string, "160 by 120 (LOW_RES)");
	} else if (resolution == MED_RES) {
		strcpy(resolution_string, "320 by 240 (MED_RES)");
	} else {
		strcpy(resolution_string, "640 by 480 (HIGH_RES)");
	}
	
	display_printf(0, 0, "Color model %i.  %s", color_model, resolution_string);
}

// Displays all the statistics available in the KISS library about
// the given blob (largest, next-largest, ...) in the given color model.
// Displays the header and data at the given line numbers. 
void display_blob_numbers(int color_model, int blob, int header_line, int data_line) {
	display_printf(0, header_line, "B  Center Cntroid Area Cfd ulX ulY lrX lrY");
	
	if (get_object_count(color_model) < blob + 1) {
		display_printf(0, data_line, "%s", BLANK_LINE);
	} else {
		display_printf(0, data_line,
			"%1i %3i %3i %3i %3i %4i %3.1f %3i %3i %3i %3i",
			blob,
			get_object_center(color_model, blob).x,
			get_object_center(color_model, blob).y,
			get_object_centroid(color_model, blob).x,
			get_object_centroid(color_model, blob).y,
			get_object_area(color_model, blob),
			get_object_confidence(color_model, blob),
			get_object_bbox(color_model, blob).ulx,
			get_object_bbox(color_model, blob).uly,
			get_object_bbox(color_model, blob).ulx + get_object_bbox(color_model, blob).width,
			get_object_bbox(color_model, blob).uly + get_object_bbox(color_model, blob).height);
	}
}

void _take_a_picture() {
	int status;
	
	while (1) {
		status = camera_update();
		if (status != 1) {
			display_printf(0, ERROR_MESSAGE_LINE, "Could not update camera (i.e., take a picture.");
		} else {
			display_printf(0, ERROR_MESSAGE_LINE, "%s", BLANK_LINE);
			break;
		}
	}
}

void _process_buttons(int* color_model, int* milliseconds_between_pictures) {
	if (a_button()) {
		display_printf(0, ERROR_MESSAGE_LINE, "Hands off!");
		
		if (*color_model >= get_channel_count() - 1) {
			display_printf(0, ERROR_MESSAGE_LINE, "You are already at the biggest color model!");
		} else {
			*color_model = *color_model + 1;
		}
		_display_model_and_resolution(*color_model, LOW_RES);
		
		while (a_button()) ;   // Wait for user to take her hands off the button
		display_printf(0, ERROR_MESSAGE_LINE, "%s", BLANK_LINE);
	}
}

#endif
