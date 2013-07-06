// Show 

#include "/kovan/archives/opencv/universal_library.h"
#include "/kovan/archives/opencv/rus_opencv_library.h"

void start_buttons();

int main() {
	Button button;
	int status;
	
	start_buttons();
	
	status = camera_open();
	if (status == FALSE) {
		printf("Could not open the camera.\n");
		return 1;
	}
	
	while (TRUE) {
		button = button_pressed();
		switch (button) {
			case A_BUTTON: cv_show_image(RAW_IMAGE); break;
			case B_BUTTON: cv_show_image(GRAYSCALE); break;
			case C_BUTTON: cv_show_image(CANNY); break;
			case X_BUTTON: cv_show_image(HOUGHLINES); break;
			case Y_BUTTON: camera_update(); break;
			case Z_BUTTON: cv_show_image(RAW_IMAGE); break;
		}
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
