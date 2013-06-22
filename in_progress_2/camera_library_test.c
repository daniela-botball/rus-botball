// Created on Fri June 21 2013

#include "camera_library.h"
#include "lego_library.h"
#include "timer.h"
#include "universal_library.h"

void spin_left_for_camera_search();
void spin_right_for_camera_search();
void move_backwards_for_camera_search();
void move_forwards_for_camera_search();
void stop_camera_search();

int main()
{
	initialize_camera(LOW_RES);
	move_so_blob_is_at(GREEN, SCREEN_SIZE.x / 2, 5, 200, CENTER_X, LEFT_RIGHT);
	return 0;
}

void spin_left_for_camera_search() { lego_spin(5, LEFT); }
void spin_right_for_camera_search() { lego_spin(5, RIGHT); }
void move_backwards_for_camera_search() { lego_drive(8, BACKWARDS); }
void move_forwards_for_camera_search() { lego_drive(8, FORWARDS); }
void stop_camera_search() { lego_stop(); }
