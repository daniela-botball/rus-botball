// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library.h"

int main()
{
	int press_a = 1;													// If you want to use the wait for button, set this value to 1. Otherwise, set this value to 0.
	
	
	printf("Program starts OK\n");
	create_connect();
	printf("Connected!\n");
	create_full();
	camera_open(LOW_RES);
	printf("Have you adjusted the joint servo yet????\n");
	press_a_to_continue(press_a);
	
	
	start_servos();
	press_a_to_continue(press_a);
	sleep(1);
	relax_servos();
	press_a_to_continue(press_a);
	create_drive_distance(49, 20, BACKWARDS);
	press_a_to_continue(press_a);
	create_spin_degrees(87, 20, RIGHT);
	press_a_to_continue(press_a);
	
	
	move_so_blob_is_at_x(0, 110, 5, 0);									//This spins to the x of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 85, 1, 0, 1);								//This moves to the y of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_x(0, 110, 5, 0);									//This fixes any inaccuracies in the previous x fix.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 85, 1, 0, 1);								//This fixes any inaccuracies caused by the second fix x.
	press_a_to_continue(press_a);
	
	
	unrelax_servos();
	grab_booster();
	press_a_to_continue(press_a);
	lift_booster();
	press_a_to_continue(press_a);
	
	
	create_spin_degrees(87, 20, LEFT);
	press_a_to_continue(press_a);
	move_so_blob_is_at_x(1, 94, 2, 0);  // 94
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(1, 47, 2, 0, 0);  // 47
	press_a_to_continue(press_a);
	create_drive_distance(15, 20, BACKWARDS);
	press_a_to_continue(press_a);
	move_so_blob_is_at_x(1, 94, 2, 0);
	press_a_to_continue(press_a);
	create_drive_distance(20, 20, BACKWARDS);
	press_a_to_continue(press_a);
	sleep(2);
	open_claw();
	
	
	return 0;
}

void spin_left_for_camera_search() { create_spin_CCW(5); }
void spin_right_for_camera_search() { create_spin_CW(5); }
void move_backwards_for_camera_search() { create_drive_straight(-10); }
void move_forwards_for_camera_search() { create_drive_straight(10); }
void stop_camera_search() { create_stop(); }
