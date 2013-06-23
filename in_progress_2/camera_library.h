/*
 * Camera utilities:
 *   -- display_blob_numbers
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

#ifndef _RUS_CAMERA_LIBRARY_H_
#define _RUS_CAMERA_LIBRARY_H_

#include <string.h>
#include "universal_library.h"

#define MILLISECONDS_BETWEEN_PICTURES 0
#define LARGEST_BLOB 0

#define GREEN 0
#define ORANGE 1
#define ROBOT_MARKER 2

#define MAX_ERRORS_ALLOWED_WHEN_OPENING_CAMERA 4
#define MAX_ERRORS_ALLOWED_BEFORE_FIRST_PICTURE 50
#define MAX_ERRORS_ALLOWED_WHEN_TAKING_A_PICTURE 50

#define NUMBER_OF_BLOBS_TO_SHOW 4
#define CAMERA_ERROR_MESSAGE_LINE (2 + NUMBER_OF_BLOBS_TO_SHOW)
#define APP_MILLISECONDS_BETWEEN_PICTURES 2000

#define MINIMUM_POM_SIZE 100
#define MINIMUM_ROBOT_MARKER_SIZE 50

typedef enum {CENTER_X, CENTER_Y, CENTROID_X, CENTROID_Y, AREA, BBOX_ULX, BBOX_ULY, BBOX_LRX, BBOX_LRY} CameraStatistic;
typedef enum {BACKWARDS_FORWARDS, LEFT_RIGHT} X_OR_Y;
typedef struct
{
	int left;
	int right;
	int front;
	int back;
	point2 center;
} bbox;

point2 SCREEN_SIZE = {159, 119};
point2 NONE = {-1, -1};
bbox BBOX_NONE = {-1, -1, -1, -1, -1};

// Functions intended to be ** PUBLIC **:
int initialize_camera(int resolution);
int move_so_blob_is_at_x(int color_model, int x, int delta, int minimum_area);
int move_so_blob_is_at_y(int color_model, int y, int delta, int minimum_area, int target);
int move_so_blob_is_at(int color_model, int desired_number, int delta, int minimum_area, CameraStatistic statistic, X_OR_Y direction);

void app_to_display_blob_numbers();
void display_blob_numbers(int color_model, int blob, int header_line, int data_line);
void turn_to_pile(int direction);
bbox get_pile_bbox(int color);
point2 find_center(int color, int object, int minimum_size);

// Functions intended to be ** PRIVATE **:
void _initialize_buttons();
void _display_model_and_resolution(int color_model, int resolution);
int _take_a_picture();
void _process_buttons(int* color_model, int* milliseconds_between_pictures, int* is_paused, int* done);
void _next_color_model(int* color_model);
void _previous_color_model(int* color_model);
void _increase_refresh_rate(int* milliseconds_between_pictures);
void _decrease_refresh_rate(int* milliseconds_between_pictures);
int _get_camera_statistic(CameraStatistic statistic, int color_model);

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
	int status, error_count, k;
	
	printf("Make sure that:\n");
	printf("  1. The camera is attached, and\n");
	printf("  2. There is at least one camera model\n");
	printf("     on the LINK, and\n");
	printf("  3. The camera can see at least one blob\n");
	printf("     after you press A.\n");
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
			if (how_many_times_no_blob_is_visible > MAX_ERRORS_ALLOWED_WHEN_TAKING_A_PICTURE) {
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
		msleep(MILLISECONDS_BETWEEN_PICTURES);
	}
}

int move_so_blob_is_at_y(int color_model, int desired_y, int delta, int minimum_area, int target) {
	int blob_area, blob_target_y, how_many_times_no_blob_is_visible;
	
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
			if (how_many_times_no_blob_is_visible > MAX_ERRORS_ALLOWED_WHEN_TAKING_A_PICTURE) {
				stop_camera_search();
				display_printf(0, 2, "FAILURE - I cannot see a big enough blob.");
				return 0;
			}
			continue;
		}
		
		// Is the center of the blob within delta of the desired x?
		// If so, return success.  Otherwise, spin left or right as appropriate.
		if (target == 0) {
		blob_target_y = get_object_center(color_model, LARGEST_BLOB).y;
		} if (target == 1) {
		blob_target_y = get_object_bbox(color_model, LARGEST_BLOB).uly;
		}
		
		if (blob_target_y >= desired_y - delta && blob_target_y <= desired_y + delta) {
			stop_camera_search();
			display_printf(0, 2, "SUCCESS - quit at %i, trying for %i", blob_target_y, desired_y);
			return 1;
		} else if (blob_target_y < desired_y - delta) {
			display_printf(0, 2, "Move BACKWARDS");
			move_backwards_for_camera_search();
		} else {
			display_printf(0, 2, "Move FORWARDS ");
			move_forwards_for_camera_search();
		}
		
		// Wait a bit before taking the next picture
		msleep(MILLISECONDS_BETWEEN_PICTURES);
	}
}

int move_so_blob_is_at(int color_model, int desired_number, int delta, int minimum_area, CameraStatistic statistic, X_OR_Y direction) {
	int blob_area, blob_target, how_many_times_no_blob_is_visible;
	int current_number;
	
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
			if (how_many_times_no_blob_is_visible > MAX_ERRORS_ALLOWED_WHEN_TAKING_A_PICTURE) {
				stop_camera_search();
				display_printf(0, 2, "FAILURE - I cannot see a big enough blob.");
				return 0;
			}
		} else {
		// If there is a big enough blob:
		
			// Get the current number for the specified camera statistic.
			current_number = _get_camera_statistic(statistic, color_model);
			
			// Is the current number within the specified delta of the desired number?
			// If so, return success.  Otherwise, move the appropriapte direction.
			if (current_number >= desired_number - delta && current_number <= desired_number + delta) {
				stop_camera_search();
				display_printf(0, 2, "SUCCESS - quit at %5i, trying for %5i", current_number, desired_number);
				return 1;
			} else if (current_number < desired_number - delta) {
				if (direction == BACKWARDS_FORWARDS) {
					display_printf(0, 2, "Move FORWARDS");
					move_forwards_for_camera_search();
				} else {
					display_printf(0, 2, "Move LEFT");
					spin_left_for_camera_search();
				}
			} else {
				if (direction == BACKWARDS_FORWARDS) {
					display_printf(0, 2, "Move BACKWARDS");
					move_backwards_for_camera_search();
				} else {
					display_printf(0, 2, "Move RIGHT");
					spin_right_for_camera_search();
				}
			}
		}
		
		// Wait a bit before taking the next picture
		if (MILLISECONDS_BETWEEN_PICTURES > 0) {
			msleep(MILLISECONDS_BETWEEN_PICTURES);
		}
	}
}

// Returns the number for the given CameraStatistic, e.g. CAMERA_X or AREA or ...
int _get_camera_statistic(CameraStatistic statistic, int color_model) {
	switch (statistic) {
		case CENTER_X:	return get_object_center(color_model, LARGEST_BLOB).x;
		case CENTER_Y:	return get_object_center(color_model, LARGEST_BLOB).y;
		case CENTROID_X:	return get_object_centroid(color_model, LARGEST_BLOB).x;
		case CENTROID_Y:	return get_object_centroid(color_model, LARGEST_BLOB).y;
		case AREA:		return get_object_area(color_model, LARGEST_BLOB);
		case BBOX_ULX:	return get_object_bbox(color_model, LARGEST_BLOB).ulx;
		case BBOX_ULY:	return get_object_bbox(color_model, LARGEST_BLOB).uly;
		case BBOX_LRX:	return get_object_bbox(color_model, LARGEST_BLOB).ulx + get_object_bbox(color_model, LARGEST_BLOB).width;
		case BBOX_LRY:	return get_object_bbox(color_model, LARGEST_BLOB).uly + get_object_bbox(color_model, LARGEST_BLOB).height;
		default:		show_message("ERROR: Request for an unknown camera statistic!  Using CENTER_X\n");
						return get_object_center(color_model, LARGEST_BLOB).x;
	}
}

// FIXME - write this spec
// Preconditions: The camera is open and ...
void app_to_display_blob_numbers() {
	int color_model, resolution, milliseconds_between_pictures;
	int is_done, is_paused;
	int old_printf_mode, old_error_message_line;
	int k, status, header_line;
	
	// Starting values of variables the user can change.
	color_model = 0;
	resolution = LOW_RES;
	milliseconds_between_pictures = APP_MILLISECONDS_BETWEEN_PICTURES;
	is_paused = FALSE;
	is_done = FALSE;
	
	// Initialize.
	old_printf_mode = _DISPLAY_PRINTF_MODE;
	old_error_message_line = _ERROR_MESSAGE_LINE;
	_DISPLAY_PRINTF_MODE = TRUE;
	_ERROR_MESSAGE_LINE = CAMERA_ERROR_MESSAGE_LINE;
	header_line = 1;
	
	_initialize_buttons();
	_display_model_and_resolution(color_model, resolution);
	
	// Repeatedly take a picture, show the blobs and process any button-presses.
	while (1) {
		if (! is_paused) {
			_take_a_picture();
			
			for (k = 0; k < NUMBER_OF_BLOBS_TO_SHOW; ++k) {
				display_blob_numbers(color_model, k, header_line, k + 2);
			}
		}
		
		// Repeatedly process and sleep a small amount, until time to sleep between pictures is reached.
		for (k = 0; k < milliseconds_between_pictures / 50; ++k) {
			_process_buttons(&color_model, &milliseconds_between_pictures, &is_paused, &is_done);
			if (is_done) {
				_DISPLAY_PRINTF_MODE = old_printf_mode;
				_ERROR_MESSAGE_LINE = old_error_message_line;
				return;
			}
			if (! is_paused) {
				msleep(50);
			}
		}
	}
}

void _initialize_buttons() {
	extra_buttons_show();
	
	set_a_button_text("Next color mdl");
	set_b_button_text("RefreshFaster");
	set_c_button_text("Pause / resume");
	set_x_button_text("Prev color mdl");
	set_y_button_text("RefreshSlower");
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

bbox get_pile_bbox(int color)
{
	bbox pile;
	rectangle r;
	int number_of_blobs, i;
	
	camera_update();
	number_of_blobs = get_object_count(color);
	
	if (number_of_blobs == 0)
	{
		return BBOX_NONE;
	}
	
	r = get_object_bbox(color, 0);
	pile.left = r.ulx;
	pile.right = r.ulx + r.width;
	pile.back = r.uly;
	pile.front = r.uly + r.height;
	
	for (i = 1; i < number_of_blobs; i++)
	{
		r = get_object_bbox(color, i);
		if (r.width * r.height < MINIMUM_POM_SIZE)
		{
			break;
		}
		
		if (r.ulx < pile.left)
		{
			pile.left = r.ulx;
		}
		if (r.ulx + r.width > pile.right)
		{
			pile.right = r.ulx + r.width;
		}
		if (r.uly < pile.back)
		{
			pile.back = r.uly;
		}
		if (r.uly + r.height > pile.front)
		{
			pile.front = r.uly + r.height;
		}
	}
	pile.center.x = (pile.left + pile.right) / 2;
	pile.center.y = (pile.front + pile.back) / 2;
	return pile;
}

point2 find_center(int color, int object, int minimum_size)
{
	point2 object_center;
	camera_update();
	if (get_object_count(color) < object + 1)
	{
		return NONE;
	}
	if (get_object_area(color, object) > minimum_size)
	{
		object_center = get_object_center(color, object);
		return object_center;
	}
	return NONE;
}

int _take_a_picture() {
	int status, errors;
	
	errors = 0;
	while (1) {
		status = camera_update();
		if (status == SUCCESS) {
			break;
		}
		++ errors;
		display_printf(0, CAMERA_ERROR_MESSAGE_LINE, "Could not update camera (i.e., take a picture.");
		msleep(MILLISECONDS_BETWEEN_PICTURES);
	}
	
	return errors;
}

void _process_buttons(int* color_model, int* milliseconds_between_pictures, int* is_paused, int* is_done) {
	Button button;
	
	button = button_pressed();
	
	if (button == NO_BUTTON) return;
	
	switch (button) {
		case A_BUTTON: hands_off(A_BUTTON);
					   _next_color_model(color_model);
					   break;
		case B_BUTTON: hands_off(B_BUTTON);
					   _increase_refresh_rate(milliseconds_between_pictures);
					   break;
		case C_BUTTON: hands_off(C_BUTTON);
					   *is_paused = ! *is_paused;
					   break;
		case X_BUTTON: hands_off(X_BUTTON);
					   _previous_color_model(color_model);
					   break;
		case Y_BUTTON: hands_off(Y_BUTTON);
					   _decrease_refresh_rate(milliseconds_between_pictures);
					   break;
		case Z_BUTTON: hands_off(Z_BUTTON);
					   *is_done = TRUE;
					   break;
	}
}

void _next_color_model(int* color_model) {
	if (*color_model >= get_channel_count() - 1) {
		show_message("Already at the biggest color model!");
	} else {
		*color_model = *color_model + 1;
		_display_model_and_resolution(*color_model, LOW_RES);
	}
}

void _previous_color_model(int* color_model) {
	if (*color_model <= 0) {
		show_message("Already at the smallest color model!");
	} else {
		*color_model = *color_model - 1;
		_display_model_and_resolution(*color_model, LOW_RES);
	}
}

void _increase_refresh_rate(int* milliseconds_between_pictures) {
	*milliseconds_between_pictures = *milliseconds_between_pictures / 2;
}

void _decrease_refresh_rate(int* milliseconds_between_pictures) {
	*milliseconds_between_pictures = *milliseconds_between_pictures * 2;
}



#endif
