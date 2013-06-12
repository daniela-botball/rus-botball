// Created on Thu May 16 2013
#include "script_library.h"
int main()
{
	create_connect();
	create_full();
	//create_script.length = 0;
	//printf("%i\n", create_script.length);
	//write_script_byte(DRIVE_DIRECT);
	//write_script_byte(get_high_byte(100));
	//write_script_byte(get_low_byte(100));
	//write_script_byte(get_high_byte(100));
	//write_script_byte(get_low_byte(100));
	script_wait_event(7);
	create_script_drive_distance(510, 500, FORWARDS);
	create_script_spin_degrees(84, 500, RIGHT);
	create_script_drive_distance(1410, 500, FORWARDS);
	create_script_spin_degrees(90, 500, RIGHT);
	create_script_halt();
	load_script();
	//msleep(3000);
	write_byte(153);
	create_disconnect();
	return 0;
}
