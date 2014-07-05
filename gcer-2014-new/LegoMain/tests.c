#include "tests.h"

#include "tournamentFunctions.h"
#include "legoMovement.h"
#include "movement.h"
#include "moveCalibration.h"
#include "timing.h"
#include "ui.h"
#include "utilities.h"
#include "camera_rus.h"
#include "score_8_plus_8.h"

// FIXME: Don't need all the above.

// FIXME: These tests are a mess.
// Many belong elsewhere.

void get_camera_numbers() {
	int colors[] = {PINK_CHANNEL, GREEN_CHANNEL};
	show_blobs(colors, 2);
}

void run_test() {
	test_spin_left_until_see_a_pom_pile();

	// test_camera_speed();
	
	//test_sucker_upper();
	//test_rightmost_point();
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

void sorter_test(int speed_pot, int button_port) {
	int speed;
	int servo_state = 1;
	set_b_button_text("Continue");
	while (!b_button()) {
		speed = map(analog10(speed_pot), 0, 1023, 0, 100);
		display_printf(0, 0, "speed = %4i", speed);
	}
	msleep(500);
	set_a_button_text("Resume");
	set_b_button_text("Pause");
	set_c_button_text("Stop");
	lego_drive(speed, FORWARDS);
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(200);
			lego_drive(speed, FORWARDS);
		}
		if (b_button()) {
			lego_stop();
			while (b_button());
			msleep(200);
		}
		if (c_button()) {
			lego_stop();
			return;
		}
		if (digital(button_port)) {
			servo_state = -servo_state;
			if (servo_state > 0) {
				set_servo_position(SORTER_SERVO, GREEN_POSITION);
			} else {
				set_servo_position(SORTER_SERVO, PINK_POSITION);
			}
			while (digital(button_port));
		}
	}
}

void test_analog_comparator() {
	display_printf(0, 0, "While tophat reading is GREATER THAN the threshold");
	int value;
	while (!a_button()) {
		value = analog_comparator(POM_S_TOPHAT, SEEING_POMS_THRESHOLD, LESS_THAN);
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
			if (get_object_count(GREEN_CHANNEL) > 0) {
				display_printf(0, 2, "green pom");
			}
			if (get_object_count(PINK_CHANNEL) > 0) {
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
	press_A_to_continue();
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
	
	press_A_to_continue();
	
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

void test_spin_left_until_see_a_pom_pile() {
	int color;

	initialize_servos();
	
	while (1) {
		initialize_camera(); // Takes pictures, ensuring a name frame.
		color = spin_left_until_see_a_pom_pile();
		printf("Found %i\n", color);
		
		press_A_to_continue();
	}
}


