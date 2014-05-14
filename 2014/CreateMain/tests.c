#include "tests.h"
#include "movement.h"
#include "ui.h"

void test_ET() {	
	set_analog_pullup(0, 0);
	msleep(200);
	// set_each_analog_state(0, 1, 0, 0, 0, 0, 0, 0);  // DOES NOT COMPILE
	while (!a_button()) {
		display_printf(0, 0, "%4i", analog_et(0));
		//msleep(200)0
	}
}


void test()
{
	create_connect();
	raise_winch();
	create_drive_distance(100, 25, FORWARDS);
}

void test_1() {
	set_mode(PRACTICE);
	int k = 0;
	while (k <= 1000) {
		operate_winch(-1900);
		press_a_to_continue();
		operate_winch(-1000 + k);
		press_a_to_continue();
		k += 100;
	}
}
