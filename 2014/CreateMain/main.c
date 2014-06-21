// Created on Wed March 12 2014
#include "createMovement.h"
#include "tournamentFunctions.h"
#include "timing.h"
#include "moveCalibration.h"
#include "movement.h"
#include "ui.h"
#include "teleoperation.h"

void robot_setup();

int main()
{	
	create_connect();
	drive_distance(20, 35, FORWARDS);
	spin_degrees(90, 50, LEFT);
	drive_distance(14, 35, FORWARDS);
	create_disconnect();
}
	
	/*create_connect();
	teleoperate();
	return 0;
	printf("connecting to create\n");
	int k = create_connect();
	printf("%i\n", k);
	int i;
	while (1) {
		i = create_get_sensor(17);
		if (i != 255) {
		printf("%i\n", i);
		msleep(100);
		}
	}
	return 0;*/
	//#define _ROBOT CREATE
	//#define _MODE PRACTICE
	//create_connect();
	robot_setup();
	//return 0;
	move_calibration(10, 10, FORWARDS);
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
	int i;
	get_robot();
	get_mode();
	display_clear();
	#if _ROBOT == CREATE
	printf("Connecting to the Create...\n");
	create_connect();
	printf("Create connected!");
	create_full();
	#endif
	set_analog_pullup(1, 0);
	set_analog_pullup(2, 0);
	set_servo_position(BAR_SERVO, BAR_START_POSITION);
	set_servo_position(CLAW_SERVO, CLAW_START_POSITION);
	set_servo_position(GYRO_SERVO, GYRO_START_POSITION);
	printf("Initializing servos...\n");
	enable_servos();
	msleep(3000);
	printf("Initializing camera...\n");
	camera_open();
	for (i = 0; i < 15; i++) {
		camera_update();
		msleep(100);
	}
	printf("Camera initialized!\n");
	operate_winch(WINCH_START_POSITION);
	create_drive_distance(15.5, 20, FORWARDS);
}
