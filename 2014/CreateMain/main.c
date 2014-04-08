// Created on Wed March 12 2014
#include "createMovement.h"
#include "main.h"

void test();
void test_1();
void robot_setup();

int main()
{
	//create_virtual_bump(200, BACKWARDS);
	//return 0;
	get_mode();
	robot_setup();
	press_a_to_continue();
	// wait_for_light();
	
	while(!a_button()); // loop and msleep() simulate wait_for_light()
	msleep(1000);
	
	move_servo_slowly(BAR_SERVO, BAR_CLOSED_POSITION);
	msleep(500);
	drop_three_hangers();
	score_cubes();


	create_disconnect();
	return 0;
}

void test()
{
	create_connect();
	raise_winch();
	create_drive_distance(100, 25, FORWARDS);
}

void test_1() {
	_mode = PRACTICE;
	int k = 0;
	while (k <= 1000) {
		operate_winch(-1900);
		press_a_to_continue();
		operate_winch(-1000 + k);
		press_a_to_continue();
		k += 100;
	}
}

void robot_setup() {
	int i;
	create_connect();
	create_full();
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
	create_drive_distance(16.5, 20, FORWARDS);
}
