// Show 

#include "universal_library.h"
#include "rus_opencv_library.h"

#define TIME_TO_SHOW_IMAGE 3000

void start_buttons();

int main() {
	Button button;
	int status;
	int number_of_lines = -1;
	
	CANNY_1 = 80;
	CANNY_2 = 120;

	HOUGH_1 = 180;
	HOUGH_2 = 20;
	HOUGH_3 = 1;
	HOUGH_4 = 30;

	start_buttons();
	
	status = camera_open(LOW_RES);
	if (status == FALSE) {
		printf("Could not open the camera.\n");
		return 1;
	}

	_DISPLAY_PRINTF_MODE = TRUE;
	camera_update();
	
	while (TRUE) {
		button = button_pressed();
		switch (button) {
			case A_BUTTON: { number_of_lines = cv_show_image(RAW_IMAGE, TIME_TO_SHOW_IMAGE); break; }
			case B_BUTTON: { number_of_lines = cv_show_image(GRAYSCALE, TIME_TO_SHOW_IMAGE); break; }
			case C_BUTTON: { number_of_lines = cv_show_image(CANNY, TIME_TO_SHOW_IMAGE); break; }
			case X_BUTTON: { number_of_lines = cv_show_image(HOUGHLINES, TIME_TO_SHOW_IMAGE); break; }
			case Y_BUTTON: { camera_update(); break; }
			case Z_BUTTON: { break; }
			default: {}
		}
		display_printf(0, 6, "%5i", number_of_lines);
	}
	
	camera_close();
	return 0;
}

void start_buttons() {
	extra_buttons_show();
	set_a_button_text("Image");
	set_b_button_text("Grayscale");
	set_c_button_text("Canny");
	set_x_button_text("HoughLines");
	set_y_button_text("Take picture");
}
