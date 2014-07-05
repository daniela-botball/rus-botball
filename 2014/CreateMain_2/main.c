// Created on Wed March 12 2014
#include "createMovement.h"
#include "main.h"

void test();
void test_1();
void getmode();

int main()
{
	run_for(100, (void*) getmode);
	get_mode();
	create_connect();
	create_full();
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	set_servo_position(GYRO_SERVO, GYRO_SETTING_POSITION);
	enable_servos();
	msleep(3000);
	// operate_winch(WINCH_START_POSITION);
	// set_servo_position(GYRO_SERVO, GYRO_START_POSITION);
	// press_a_to_continue();
	
	// set_servo_position(GYRO_SERVO, GYRO_SETTING_POSITION);
	// msleep(2000);
	drop_three_hangers();
	//pick_up_first_doubler();
	pick_up_cube();
	
	
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
