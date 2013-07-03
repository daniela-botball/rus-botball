/*
 * Camera utilities:
 *   -- display_blob_numbers
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

#ifndef _RUS_CAMERA_SHOW_NUMBERS_LIBRARY_H_
#define _RUS_CAMERA_SHOW_NUMBERS_LIBRARY_H_

#include <string.h>
//#include "universal_library.h"

#define DEFAULT_COLOR_MODEL 0
#define DEFAULT_FIRST_LINE 0
#define DEFAULT_NUMBER_OF_BLOBS_TO_SHOW 4
#define DEFAULT_MILLISECONDS_BETWEEN_PICTURES 2000

typedef struct {
	int color_model;
	int number_of_blobs_to_show;
	int milliseconds_between_pictures;
	Boolean is_paused;
	int servo_positions[4];
	int resolution;
} CameraAppData;

// Functions intended to be ** PUBLIC **:
void app_to_display_blob_numbers();
void display_blob_numbers(int color_model, int blob, int line);

// Functions intended to be ** PRIVATE **:
void _initialize_buttons();
Boolean _process_buttons(CameraAppData* camera_app_data);
void _display_model_and_resolution(int color_model, int resolution);
void _more_options(CameraAppData* camera_app_data);

// FIXME - write this spec
// Preconditions: The camera is open and ...
void app_to_display_blob_numbers(int first_line, int number_of_blobs_to_show) {
	CameraAppData camera_app_data;
	Boolean old_printf_mode, is_time_to_quit;
	int k;
	
	// Initialize.
	camera_app_data.color_model = DEFAULT_COLOR_MODEL;
	camera_app_data.milliseconds_between_pictures = DEFAULT_MILLISECONDS_BETWEEN_PICTURES;
	camera_app_data.is_paused = FALSE;
	camera_app_data.resolution = LOW_RES;
	for (k = 0; k < 4; ++k) {
		camera_app_data.servo_positions[k] = 0;
	}
	
	old_printf_mode = _USE_DISPLAY_PRINTF;
	_USE_DISPLAY_PRINTF = TRUE;
	
	_initialize_buttons();	
	display_printf(0, first_line + 2, "B  Center Cntroid Area Cfd ulX ulY lrX lrY");
	
	// Repeatedly take a picture, show the blobs and process any button-presses.
	while (1) {

		// Unless paused, take a picture and show the blobs.
		if (! camera_app_data.is_paused) {
			take_a_picture();
			
			display_model_and_resolution(camera_app_data.color_model, camera_app_data.resolution);
			display_printf(0, first_line + 1, "Servos are at: %4i %4i %4i %4i",
				camera_app_data.servo_positions[0],
				camera_app_data.servo_positions[1],
				camera_app_data.servo_positions[2],
				camera_app_data.servo_positions[3]);
			for (k = 0; k < camera_app_data.number_of_blobs_to_show; ++k) {
				display_blob_numbers(camera_app_data.color_model, k, first_line + 3 + k);
			}
		}
		
		// Wait for a button press or for the time-between-pictures to elapse,
		// whichever comes first.  If a button press, process it.
		for (k = 0; k < camera_app_data.milliseconds_between_pictures / 50; ++k) {
			is_time_to_quit = _process_buttons(&camera_app_data);
			if (is_time_to_quit) {
				_USE_DISPLAY_PRINTF = old_printf_mode;
				return;
			}
			if (! camera_app_data.is_paused) {
				msleep(50);
			}
		}
	}
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
	
	display_printf(0, 0, "Color model: %i.  %-25s", color_model, resolution_string);
}

// Displays all the statistics available in the KISS library about
// the given blob (largest, next-largest, ...) in the given color model.
// Displays the header and data at the given line numbers. 
void display_blob_numbers(int color_model, int blob, int line) {
	if (get_object_count(color_model) < blob + 1) {
		display_printf(0, line, "%1i %-40s", blob, "No more blobs");
	} else {
		display_printf(0, line, "%1i %3i %3i %3i %3i %4i %3.1f %3i %3i %3i %3i",
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

/*
int take_a_picture() {
	int status, errors;
	
	errors = 0;
	while (1) {
		status = camera_update();
		if (status == SUCCESS) {
			break;
		}
		++ errors;
		display_printf(0, _MESSAGE_LINE_1, "Could not update camera (i.e., take a picture.");
		msleep(MILLISECONDS_BETWEEN_PICTURE_ATTEMPTS);
	}
	
	return errors;
}
*/
void _initialize_buttons() {
	extra_buttons_show();
	
	set_a_button_text("NextColorModel");
	set_b_button_text("RefreshFaster");
	set_c_button_text("Quit");
	set_x_button_text("Pause / resume");
	set_y_button_text("RefreshSlower");
	set_z_button_text("More options");
}

Boolean _process_buttons(CameraAppData* camera_app_data) {
	//int* color_model, int* milliseconds_between_pictures, int* is_paused, int* is_done) {
	Button button;
	
	button = button_pressed();
		
	switch (button) {
		case A_BUTTON: {
			hands_off(A_BUTTON);
			camera_app_data->color_model = (camera_app_data->color_model + 1) % 4;
			break;
		}
		case B_BUTTON: {
			hands_off(B_BUTTON);
			camera_app_data->milliseconds_between_pictures *= 2;
			break;
		}
		case C_BUTTON: {
			hands_off(C_BUTTON);
			return TRUE;
		}
		case X_BUTTON: {
			hands_off(X_BUTTON);
			camera_app_data->is_paused = ! camera_app_data->is_paused;
			break;
		}
		case Y_BUTTON: {
			hands_off(Y_BUTTON);
			camera_app_data->milliseconds_between_pictures /= 2;
			break;
		}
		case Z_BUTTON: {
			hands_off(Z_BUTTON);
			more_options(camera_app_data);
			break;
		}
	}
	
	return FALSE;
}

void _more_options(CameraAppData* camera_app_data) {
}

#endif
