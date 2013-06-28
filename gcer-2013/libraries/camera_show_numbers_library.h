/*
 * Camera utilities:
 *   -- display_blob_numbers
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

#ifndef _RUS_CAMERA_SHOW_NUMBERS_LIBRARY_H_
#define _RUS_CAMERA_SHOW_NUMBERS_LIBRARY_H_

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
int move_so_blob_is_at(int color_model, int desired_number, int delta, int minimum_area, CameraStatistic statistic, X_OR_Y direction, int speed);

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


// FIXME - write this spec
// Preconditions: The camera is open and ...
void app_to_display_blob_numbers(int first_line, int number_of_blobs_to_show) {
	int color_model, milliseconds_between_pictures, is_paused;
	int old_printf_mode, old_error_message_line;
	int k;
	int servos[4] = {-1, -1, -1, -1}; // No servos set yet.
	
	// Starting values of variables the user can change.
	color_model = 0;
	milliseconds_between_pictures = APP_MILLISECONDS_BETWEEN_PICTURES;
	is_paused = FALSE;
	
	// Initialize.
	old_printf_mode = _DISPLAY_PRINTF_MODE;
	old_error_message_line = _MESSAGE_LINE;
	_DISPLAY_PRINTF_MODE = TRUE;
	_MESSAGE_LINE = first_line + 3 + number_of_blobs_to_show
	
	_initialize_buttons();
	_display_model(color_model);
	_display_resolution(resolution);
	
	// Repeatedly take a picture, show the blobs and process any button-presses.
	while (1) {
		
		// Unless paused, take a picture and show the blobs.
		if (! is_paused) {
			_take_a_picture();
			
			for (k = 0; k < NUMBER_OF_BLOBS_TO_SHOW; ++k) {
				display_blob_numbers(color_model, k, header_line, k + 2);
			}
		}
		
		// Wait for a button press or for the time-between-pictures to elapse,
		// whichever comes first.  If a button press, process it.
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
	set_z_button_text("More");
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
