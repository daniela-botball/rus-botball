// Created on Thu June 20 2013

#include "universal_library.h"
#include "create_library.h"
#include "camera_library.h"

int main()
{
	printf("Hello, World!\n");
	return 0;
}

void spin_left_for_camera_search() { create_spin_CCW(5); }
void spin_right_for_camera_search() { create_spin_CW(5); }
void move_backwards_for_camera_search() { create_drive_straight(-10); }
void move_forwards_for_camera_search() { create_drive_straight(10); }
void stop_camera_search() { create_stop(); }
