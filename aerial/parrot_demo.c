// Created on Tue July 2 2013

#include "universal_library.h"

void take_off_stay_up_land(int milliseconds_to_stay_up);
void take_off_show_data_land();
void show_data();
void show_data_until_C(int milliseconds_between_refreshes);
void g_drone_up();
void g_drone_down();

int main() {
	int status;
	
	printf("Trying out the Parrot Drone!\n");
	
	// Connect to the Parrot Drone.
	status = drone_connect();
	if (status == FALSE) {
		printf("Drone connection failed!  Fix and restart!\n");
		return FAILURE;
	}
	
	// Calibrate the accelerometer to know what "flat" is.
	drone_calibrate();
	
	// Take off, stay up for 5 seconds, then land.
	// take_off_stay_up_land(5000);
	
	// Take off, show data every time you press A, land when you press B.
	take_off_show_data_land();
	
	return SUCCESS;
}

// Take off, stay up for the given number of milliseconds, then land.
void take_off_stay_up_land(int milliseconds_to_stay_up) {
	printf("Takeoff!\n");
	drone_takeoff();
	msleep(3000); // Time to get up to its standard height
	
	printf("In the air!\n");
	msleep(milliseconds_to_stay_up);
	
	printf("Land!\n");
	drone_land();
	msleep(1000); // Time to land from its standard height
	
	printf("Landed!\n");
}

void show_data() {
	display_printf(0, 0, "x, y, z: %6.2f %6.2f %6.2f",
		get_drone_x(), get_drone_y(), get_drone_z());
}

void show_data_until_C(int milliseconds_between_refreshes) {
	Button button;
	int is_done;
	int k;
	
	set_a_button_text("Go up");
	set_b_button_text("Go down");
	set_c_button_text("Land");
	
	is_done = FALSE;
	k = 0;
	while (TRUE) {
		button = button_pressed();
		switch (button) {
			case A_BUTTON: { g_drone_up(); break; }
			case B_BUTTON: { g_drone_down(); break; }
			case C_BUTTON: { is_done = TRUE; break; }
		}
		if (is_done) {
			break;
		}
		if (k * 10 == milliseconds_between_refreshes) {
			show_data();
			k = 0;
		}
		k = k + 1;
		msleep(10);
	}
}

void take_off_show_data_land() {
	printf("Takeoff!\n");
	drone_takeoff();
	msleep(3000); // Time to get up to its standard height
	
	drone_hover();
	show_data_until_C(1000);
	
	printf("Land!\n");
	drone_land();
	msleep(1000); // Time to land from its standard height
	
	printf("Landed!\n");
}

void g_drone_up() {
	drone_move(0, 0, 150, 0);
	msleep(3000);
	drone_move(0, 0, 0, 0);
}

void g_drone_down() {
	drone_move(0, 0, -150, 0);
	msleep(3000);
	drone_move(0, 0, 0, 0);
}
