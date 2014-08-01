#include "tests.h"

#include "tournamentFunctions.h"
#include "legoMovement.h"
#include "movement.h"
//#include "moveCalibration.h"
#include "timing.h"
#include "ui.h"
#include "utilities.h"
#include "camera_rus.h"
#include "score_8_plus_8.h"

// FIXME: Don't need all the above.

// FIXME: These tests are a mess.
// Many belong elsewhere.

void test() {
	setup();
	dump_poms(FIRST_SIDE);
	msleep(3000);
	dump_poms(SECOND_SIDE);
	return;
	//determine_camera_speed(GREEN);
	//sort_while_moving(8);
	//test_sorting();
	//spin_left_until_pom_pile_is_lined_up();
	//test_show_blobs();
	//try_motor_speeds();
	//get_ticks_per_rotation(2);
	//get_ticks_per_rotation(0);
	// test_degrees();
	//test_drive_straight();
	// test_face_poms();
	
	//test_spin_left_until_see_a_pom_pile();

	// test_camera_speed();
	
	//test_sucker_upper();
	//test_rightmost_point();
}

void test_show_blobs() {
	int colors[] = {PINK, GREEN};
	
	show_blobs(colors, 2);
}

int get_ticks_per_rotation(int motor) {
	clear_motor_position_counter(motor);
	display_printf(0, 0, "Spin the motor %d 360 degrees", motor);
	set_a_button_text("Done");
	int ticks;
	while (!a_button()) {
		ticks = get_motor_position_counter(motor);
		display_printf(0, 1, "ticks: %4d", ticks);
	}
	display_clear();
	display_printf(0, 0, "There are %d ticks per rotation", ticks);
	display_printf(0, 1, "on motor %d", motor);
	return ticks;
}

void test_analog_comparator() {
	display_printf(0, 0, "While tophat reading is GREATER THAN the threshold");
	int value;
	while (!a_button()) {
		value = analog_comparator(TRACK_TOPHAT, TRACK_POMS_THRESHOLD, LESS_THAN);
		display_printf(0, 1, "%i", value);
	}
}

void test_multiple_cameras() {
	set_a_button_text("Camera 1");
	set_b_button_text("Camera 2");
	set_c_button_text("Take Picture");
	display_printf(0, 0, "Select Camera");
	display_printf(0, 1, "Camera 1 selected");
	int camera;
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(200);
			//camera_close();
			camera = camera_open_device(0, LOW_RES);
			display_printf(0, 1, "Camera 1 selected - %i", camera);
		}
		if (b_button()) {
			while (b_button());
			msleep(200);
			//camera_close();
			camera = camera_open_device(1, LOW_RES);
			display_printf(0, 1, "Camera 2 selected - %i", camera);
		}
		if (c_button()) {
			while (c_button());
			msleep(200);
			camera_update();
			if (get_object_count(GREEN) > 0) {
				display_printf(0, 2, "green pom");
			}
			if (get_object_count(PINK) > 0) {
				display_printf(0, 2, "green pom");
			}
		}
		
	}
}

/*
	// FIXME:  WHILE loop in the following is not needed.
    // FIX AS DESIRED, OR DELETE.
	set_a_button_text("No");
	set_b_button_text("Yes");
	printf("Are you using the camera?\n");
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(200);
			printf("Camera will not be initialized\n");
			break;
		}
		if (b_button()) {
			while (b_button());
			msleep(200);
			printf("Intializing camera\n");
			camera_open();
			int i;
			for (i = 0; i < 20; i++) {
				camera_update();
			}
			break;
		}
	}
	press_a_to_continue();
}
*/

void test_camera_speed() {
	int k;
	int n = 100;
	float s;
	
	printf("Initializing camera.\n");
	camera_open();
	for (k = 0; k < 20; k++) {
		camera_update();
	}
	
	press_a_to_continue();
	
	s = seconds();
	for (k = 0; k < n; ++k) {
		camera_update();
	}
	s = seconds() - s;
	printf("Seconds per update = %6.3f\n", s / n);
}

void test_sucker_upper() {
	int speed;
	
	extra_buttons_show();
	
	set_a_button_text("5");
	set_b_button_text("10");
	set_c_button_text("20");
	
	set_x_button_text("40");
	set_y_button_text("70");
	set_z_button_text("100");
	
	speed = 5;
	motor(0, 100);
	
	while (1) {
		if (a_button()) {
			speed = 5;
		}
		if (b_button()) {
			speed = 10;
		}
		if (c_button()) {
			speed = 20;
		}
		if (x_button()) {
			speed = 40;
		}
		if (y_button()) {
			speed = 70;
		}
		if (z_button()) {
			speed = 100;
		}
		motor(3, speed);
		motor(1, speed);
	}
}

void test_distance_degrees() {
	// FIXME.
	float speed, degrees;
	
	extra_buttons_show();
	
	speed = 80;
	degrees = 80;
	
	
	printf("Set the speed/degrees, as follows:\n");
	printf("A/B increase/decrease speed.\n");
	printf("X/Y do same for degrees.\n");
	printf("C to run a 1 foot test.\n");
	printf("Z to run a 2.5 foot test.\n");
	printf("Current speed, degrees: %5.2f %5.2f\n", speed, degrees);
	
	/*while (1) {
		
		if (a_button()) {
			left_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (a_button()) ;
		}
		if (b_button()) {
			left_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (b_button()) ;
		}
		if (x_button()) {
			right_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (x_button()) ;
		}
		if (y_button()) {
			right_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (y_button()) ;
		}
		if (c_button()) {
			printf("Running at: %3i %3i\n", left_speed, right_speed);
			while (c_button()) ;
			msleep(500);
			run_wheel_motors(0, 2, left_speed, right_speed, 8.0);
			printf("Done, change speeds as desired.\n");
		}
		if (z_button()) {
			printf("Running at: %3i %3i\n", left_speed, right_speed);
			while (z_button()) ;
			msleep(500);
			run_wheel_motors(0, 2, left_speed, right_speed, 4.0);
			printf("Done, change speeds as desired.\n");
		}
	}*/
}

void try_motor_speeds() {
	int left_speed, right_speed;
	
	extra_buttons_show();
	
	left_speed = 80;
	right_speed = 80;
	
	
	printf("Set the motor speeds, as follows:\n");
	printf("A/B increase/decrease LEFT motor speed.\n");
	printf("X/Y do same for the RIGHT motor speed.\n");
	printf("C to run an 8 second test.\n");
	printf("Z to run a 4 second test.\n");
	printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
	
	while (1) {
		
		if (a_button()) {
			left_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (a_button()) ;
		}
		if (b_button()) {
			left_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (b_button()) ;
		}
		if (x_button()) {
			right_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (x_button()) ;
		}
		if (y_button()) {
			right_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (y_button()) ;
		}
		if (c_button()) {
			printf("Running at: %3i %3i\n", left_speed, right_speed);
			while (c_button()) ;
			msleep(500);
			run_wheel_motors(0, 2, left_speed, right_speed, 8.0);
			printf("Done, change speeds as desired.\n");
		}
		if (z_button()) {
			printf("Running at: %3i %3i\n", left_speed, right_speed);
			while (z_button()) ;
			msleep(500);
			run_wheel_motors(0, 2, left_speed, right_speed, 4.0);
			printf("Done, change speeds as desired.\n");
		}
	}
}

void test_motor_speeds() {
	int port;
	int powers[] = {100, 80, 50, 10, 5, -5, -10, -50, -80, -100};
	int number_of_powers = 10;
	int k;
	
	int seconds_to_run = 5.0;
	
	for (port = 2; port < 3; ++port) {
		for (k = 0; k < number_of_powers; ++k) {
			run_motor(port, powers[k], seconds_to_run);
		}
	}
}

/* Plug in the motor with green being "forward",
   with left ports to left wheel and right ports to right wheel.
*/
void run_motor(int port, int power, float seconds_to_run) {
	float s;
	
	motor(port, power);
	
	clear_motor_position_counter(port);
	
	s = seconds();
	while (1) {
		if (seconds() - s > seconds_to_run) {
			break;
		}
	}
	
	off(port);
	
	printf("Port, power, counter:  %1i %3i %5i \n", port, power, get_motor_position_counter(port));
	press_a_to_continue();
}


void run_wheel_motors(int port1, int port2, int power1, int power2, float seconds_to_run) {
	float s;
	
	motor(port1, power1);
	motor(port2, power2);
	
	clear_motor_position_counter(port1);
	clear_motor_position_counter(port2);
	
	s = seconds();
	while (1) {
		if (seconds() - s > seconds_to_run) {
			break;
		}
	}
	
	off(port1);
	off(port2);
	printf("Motor counters:  %5i %5i\n", get_motor_position_counter(port1), get_motor_position_counter(port2));
}

void test_degrees() {
	lego_spin_degrees(30, 40, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(45, 40, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(90, 40, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(180, 40, FORWARDS);
	press_a_to_continue();
	
	lego_spin_degrees(30, 80, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(45, 80, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(90, 80, FORWARDS);
	press_a_to_continue();
	lego_spin_degrees(180, 80, FORWARDS);
	press_a_to_continue();
	
	lego_spin_degrees(30, 40, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(45, 40, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(90, 40, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(180, 40, BACKWARDS);
	press_a_to_continue();
	
	lego_spin_degrees(30, 80, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(45, 80, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(90, 80, BACKWARDS);
	press_a_to_continue();
	lego_spin_degrees(180, 80, BACKWARDS);
	press_a_to_continue();
}

void test_drive_straight() {
	lego_drive_distance(25, 80, FORWARDS);
	press_a_to_continue();
	lego_drive_distance(50, 80, FORWARDS);
	press_a_to_continue();
	
	lego_drive_distance(25, 40, FORWARDS);
	press_a_to_continue();
	lego_drive_distance(50, 40, FORWARDS);
	press_a_to_continue();
	
	lego_drive_distance(25, 100, FORWARDS);
	press_a_to_continue();
	lego_drive_distance(50, 100, FORWARDS);
	press_a_to_continue();
	
	lego_drive_distance(25, 40, FORWARDS);
	press_a_to_continue();
	lego_drive_distance(50, 40, FORWARDS);
	press_a_to_continue();
}
