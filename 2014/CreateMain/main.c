// Created on Wed March 12 2014
//#include "createMovement.h"
//#include "tournamentFunctions.h"
//#include "timing.h"
//#include "moveCalibration.h"

void robot_setup();

int main()
{	
	get_robot();
	return 0;
	create_connect();
	move_calibration(10, 10, FORWARDS);
	create_disconnect();
	return 0;
	get_mode();
	robot_setup();
	press_a_to_continue();
	//wait_for_light();
	
	while(!a_button()); // loop and msleep() simulate wait_for_light()
	//msleep(1000);
	
	move_servo_slowly(BAR_SERVO, BAR_CLOSED_POSITION);
	drop_three_hangers();
	score_cubes();


	create_disconnect();
	return 0;
}

void robot_setup() {
	
	msleep(100);
	int i;
	#define _ROBOT CREATE
	printf("Connecting to the Create...\n");
	create_connect();
	printf("Create connected!");
	create_full();
	set_analog_pullup(1, 0);
	set_analog_pullup(2, 0);
	set_servo_position(BAR_SERVO, BAR_START_POSITION);
	set_servo_position(CLAW_SERVO, CLAW_START_POSITION);
	set_servo_position(GYRO_SERVO, GYRO_START_POSITION);
	enable_servos();
	msleep(3000);
	camera_open();
	for (i = 0; i < 15; i++) {
		camera_update();
		msleep(100);
	}
	operate_winch(WINCH_START_POSITION);
	create_drive_distance(15.5, 20, FORWARDS);
}

void get_robot() {
	display_clear();
	display_printf(0, 0, "Select robot running");
	set_a_button_text("LEGO");
	set_b_button_text("CREATE");
	while (1) {
		if (a_button()) {
			#define _ROBOT LEGO
			display_printf(0, 0, "The LEGO robot has been selected");
			if (confirm_selection(1)) {
				break;
			} else {
				#undefine _ROBOT
				continue;
			}
			break;
		}
		if (b_button()) {
			#define _ROBOT CREATE
			display_printf(0, 0, "The CREATE robot has been selected");
			if (confirm_selection(1)) {
				break;
			} else {
				#undefine _ROBOT
				continue;
			}
			break;
		}
	}
}

int confirm_selection(int message_line_number) {
	set_a_button_text("Yes");
	set_b_button_text("No");
	display_printf(0, message_line_number, "Please confirm your selection");
	while (1) {
		if (a_button()) {
			while (a_button());
			display_printf(0, message_line_number + 1, "Selection confirmed");
			msleep(100);
			return 1;
		}
		if (b_button()) {
			while (b_button());
			display_printf(0, message_line_number + 1, "Selection canceled");
			msleep(100);
			return 0;
		}
	}
}
