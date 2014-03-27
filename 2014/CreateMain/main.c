// Created on Wed March 12 2014
#include "createMovement.h"
#include "main.h"

void test();
void test_1();

int main()
{
	get_mode();
	create_connect();
	create_full();
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	enable_servos();
	drop_three_hangers();
	pick_up_first_doubler();
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
