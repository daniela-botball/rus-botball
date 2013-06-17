// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library2.h"

int main()
{
	printf("Program starts OK\n");
	create_connect();
	printf("Connected!");
	create_full();
	
	start_servos();
	press_a_to_continue();
	begin_servos();
	press_a_to_continue();
	sleep(1);
	relax_servos();	
	press_a_to_continue();
	create_drive_distance(10, 5, FORWARDS);
	
	return 0;
}

void spin_left_for_camera_search() { create_spin_CCW(5); }
void spin_right_for_camera_search() { create_spin_CW(5); }
void move_backwards_for_camera_search() { create_drive_straight(10); }
void move_forwards_for_camera_search() { create_drive_straight(-10); }
void stop_camera_search() { create_stop(); }
