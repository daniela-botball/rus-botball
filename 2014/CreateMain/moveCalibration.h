// Created on Sun April 13 2014

// Replace FILE with your file's name
#ifndef _MOVECALIBRATION_H_
#define _MOVECALIBRATION_H_

#define _ROBOT LEGO
#define CREATE 1
#define LEGO 0

#define LARGE_INCREMENT 10
#define SMALL_INCREMENT 5

#define CALIBRATION_SPEED 20

void robot_drive(float distance, float speed, int direction);
void move_calibration(float distance, float speed, int direction)


void move_calibration(float distance, float speed, int direction) {
	float new_distance = distance;
	
	robot_drive(distance, speed, direction);
	
	extra_buttons_show();
	set_a_button_text("Continue");
	set_b_button_text("Fwds %i cm", SMALL_INCREMENT);
	set_c_button_text("Fwds %i cm", LARGE_INCREMENT);
	set_x_button_text("Menu 2");
	set_y_button_text("Bwds %i cm", SMALL_INCREMENT);
	set_z_button_text("Fwds %i cm", LARGE_INCREMENT);
	
	while (1) {
		if (a_button()) {
			while (a_button());
			display_clear();
			display_printf(0, 0, "given distance: %f cm", distance);
			display_printf(0, 1, "new distance: %f cm", new_distance);
			return;
		}
		if (b_button()) {
			while (b_button());
			msleep(500);
			robot_drive_distance(SMALL_INCREMENT, CALIBRATION_SPEED, FORWARDS);
			new_distance += SMALL_INCREMENT;
		}
		if (c_button()) {
			while (c_button());
			msleep(500);
			robot_drive_distance(LARGE_INCREMENT, CALIBRATION_SPEED, FORWARDS);
			new_distance += LARGE_INCREMENT;
		}
		if (y_button()) {
			while (b_button());
			msleep(500);
			robot_drive_distance(SMALL_INCREMENT, CALIBRATION_SPEED, BACKWARDS);
			new_distance -= SMALL_INCREMENT;
		}
		if (z_button()) {
			while (c_button());
			msleep(500);
			robot_drive_distance(LARGE_INCREMENT, CALIBRATION_SPEED, BACKWARDS);
			new_distance -= LARGE_INCREMENT;
		}
		
		
	}
	
}


void robot_drive(float distance, float speed, int direction) {
	#if _ROBOT == CREATE
	create_drive_distance(distance, speed, direction);
	#elif _ROBOT == LEGO
	lego_drive_distance();
	#endif
}

#endif
