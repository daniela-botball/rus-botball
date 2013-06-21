// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library.h"

int main()
{
	int press_a = 0;													// If you want to use the wait for button, set this value to 1. Otherwise, set this value to 0.
	
	
	printf("Program starts OK\n");										// Initializing procceses and such.
	create_connect();
	printf("Connected!\n");
	create_full();
	camera_open(LOW_RES);
	printf("Have you adjusted the joint servo yet????\n");
	press_a_to_continue(press_a);
	start_servos();
	press_a_to_continue(press_a);
	relax_servos();
	press_a_to_continue(press_a);
	
	
	create_drive_distance(47, 20, BACKWARDS);
	press_a_to_continue(press_a);
	create_spin_degrees(87, 30, RIGHT);
	press_a_to_continue(press_a);
	
	
	move_so_blob_is_at_x(0, 91, 5, 0);			//110					//This spins to the x of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 35, 1, 0, 0);		//85					//This moves to the y of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_x(0, 91, 5, 0);									//This fixes any inaccuracies in the previous x fix.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 35, 1, 0, 0);								//This fixes any inaccuracies caused by the second fix x.
	press_a_to_continue(press_a);
	
	// 92, 31		(approximately 12 cm away from pole)
	unrelax_servos();
	grab_booster(150);
	press_a_to_continue(press_a);
	lift_booster(500);
	press_a_to_continue(press_a);	
	
	
	create_spin_degrees(87, 40, LEFT);
	press_a_to_continue(press_a);
	create_drive_distance(15, 20, BACKWARDS);
	press_a_to_continue(press_a);
	
	// 90, 16		(approximately 20 cm away from pole)
	move_so_blob_is_at_x(0, 80, 2, 0);									//FIXME
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 7, 2, 0, 0);
	press_a_to_continue(press_a);
	create_drive_distance(23, 20, BACKWARDS);
	press_a_to_continue(press_a);
	drop_booster(700, 0);	
	
	
	relax_servos();
	press_a_to_continue(press_a);
	create_drive_distance(20, 20, FORWARDS);
	press_a_to_continue(press_a);
	create_spin_degrees(87, 30, RIGHT);
	press_a_to_continue(press_a);
	
	
	move_so_blob_is_at_x(0, 70, 5, 0);			//110					//This spins to the x of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 35, 1, 0, 0);		//85					//This moves to the y of the three-booster.
	press_a_to_continue(press_a);
	move_so_blob_is_at_x(0, 70, 5, 0);									//This fixes any inaccuracies in the previous x fix.
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 35, 1, 0, 0);								//This fixes any inaccuracies caused by the second fix x.
	press_a_to_continue(press_a);
	
	
	unrelax_servos();
	start_gate();
	grab_booster(150);
	press_a_to_continue(press_a);
	lift_booster(500);
	press_a_to_continue(press_a);
	
	
	create_spin_degrees(87, 40, LEFT);
	press_a_to_continue(press_a);
	create_drive_distance(5, 20, BACKWARDS);
	press_a_to_continue(press_a);
	
	
	move_so_blob_is_at_x(0, 80, 2, 0);									//FIXME
	press_a_to_continue(press_a);
	move_so_blob_is_at_y(0, 7, 2, 0, 0);
	press_a_to_continue(press_a);
	create_drive_distance(23, 20, BACKWARDS);
	press_a_to_continue(press_a);
	drop_booster(700, 0);	
	
	return 0;
}

void spin_left_for_camera_search() { create_spin_CCW(10); }
void spin_right_for_camera_search() { create_spin_CW(10); }
void move_backwards_for_camera_search() { create_drive_straight(-20); }
void move_forwards_for_camera_search() { create_drive_straight(20); }
void stop_camera_search() { create_stop(); }
