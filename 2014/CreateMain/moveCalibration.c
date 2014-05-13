#include "moveCalibration.h"
#include <string.h>
#include "tournamentFunctions.h"

void move_calibration(float distance, float speed, int direction) {
	float new_distance = distance;
	
	robot_drive_distance(distance, speed, direction);
	
	#if _MODE == PRACTICE
	extra_buttons_show();
	char fwds_small_message[11];
	char fwds_large_message[11];
	char bwds_small_message[11];
	char bwds_large_message[11];
	sprintf(fwds_small_message, "Fwds %i cm", SMALL_INCREMENT);
	sprintf(fwds_large_message, "Fwds %i cm", LARGE_INCREMENT);
	sprintf(bwds_small_message, "Bwds %i cm", SMALL_INCREMENT);
	sprintf(bwds_large_message, "Bwds %i cm", LARGE_INCREMENT);
	
	set_a_button_text("Continue");
	set_b_button_text(fwds_small_message);
	set_c_button_text(fwds_large_message);
	set_x_button_text("Menu 2");
	set_y_button_text(bwds_small_message);
	set_z_button_text(bwds_large_message);
	
	while (1) {
		if (a_button()) {
			while (a_button());
			display_clear();
			display_printf(0, 0, "given distance: %.2f cm", distance);
			display_printf(0, 1, "new distance: %.2f cm", new_distance);
			display_printf(0, 2, "press 'a' to continue");
			msleep(100);
			while (!a_button());
			msleep(500);
			break;
		}
		if (b_button()) {
			while (b_button());
			msleep(500);
			robot_drive_distance(SMALL_INCREMENT, CALIBRATION_SPEED, FORWARDS);
			new_distance += SMALL_INCREMENT;
			display_printf(0, 0, "distance: %.2f cm", new_distance);
		}
		if (c_button()) {
			while (c_button());
			msleep(500);
			robot_drive_distance(LARGE_INCREMENT, CALIBRATION_SPEED, FORWARDS);
			new_distance += LARGE_INCREMENT;
			display_printf(0, 0, "distance: %.2f cm", new_distance);
		}
		if (y_button()) {
			while (y_button());
			msleep(500);
			robot_drive_distance(SMALL_INCREMENT, CALIBRATION_SPEED, BACKWARDS);
			new_distance -= SMALL_INCREMENT;
			display_printf(0, 0, "distance: %.2f cm", new_distance);
		}
		if (z_button()) {
			while (z_button());
			msleep(500);
			robot_drive_distance(LARGE_INCREMENT, CALIBRATION_SPEED, BACKWARDS);
			new_distance -= LARGE_INCREMENT;
			display_printf(0, 0, "distance: %.2f cm", new_distance);
		}
	}
	#endif
	display_clear();
	display_printf(0, 0, "New distance: %f cm", new_distance);
}

void robot_drive_distance(float distance, float speed, int direction) {
	#if _ROBOT == CREATE
	create_drive_distance(distance, speed, direction);
	#elif _ROBOT == LEGO
	lego_drive_distance();
	#endif
}
