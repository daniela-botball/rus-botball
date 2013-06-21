// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library.h"

int main()
{
	//SKIP_PRESS_A_TO_CONTINUE = TRUE;
	
	printf("Program starts OK\n");										// Initializing procceses and such.
	create_connect();
	printf("Connected!\n");
	create_full();
	camera_open(LOW_RES);
	printf("Have you adjusted the joint servo yet????\n");
	press_A_to_continue();
	start_servos();
	press_A_to_continue();
	relax_servos();
	press_A_to_continue();
	
	
	create_drive_distance(47, 40, BACKWARDS);	//was 20 speed
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);
	press_A_to_continue();
	
	
	move_so_blob_is_at_x(0, 91, 5, 0);			//110					//This spins to the x of the three-booster.
	press_A_to_continue();
	move_so_blob_is_at_y(0, 35, 1, 0, 0);		//85					//This moves to the y of the three-booster.
	press_A_to_continue();
	move_so_blob_is_at_x(0, 91, 5, 0);									//This fixes any inaccuracies in the previous x fix.
	press_A_to_continue();
	move_so_blob_is_at_y(0, 35, 1, 0, 0);								//This fixes any inaccuracies caused by the second fix x.
	press_A_to_continue();
	
	// 92, 31		(approximately 12 cm away from pole)
	unrelax_servos();
	grab_booster();
	press_A_to_continue();
	lift_booster();
	press_A_to_continue();	
	
	
	create_spin_degrees(87, 87, LEFT);
	press_A_to_continue();
	create_drive_distance(15, 20, BACKWARDS);
	press_A_to_continue();
	
	// 90, 16		(approximately 20 cm away from pole)
	move_so_blob_is_at_x(0, 80, 2, 0);									//FIXME
	press_A_to_continue();
	move_so_blob_is_at_y(0, 7, 2, 0, 0);
	press_A_to_continue();
	create_drive_distance(23, 20, BACKWARDS);
	press_A_to_continue();
	drop_booster(DROP_BOOSTER);	
	
	
	relax_servos();
	press_A_to_continue();
	create_drive_distance(10, 20, FORWARDS);
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);
	press_A_to_continue();
	
	
	move_so_blob_is_at_x(0, 70, 5, 0);			//110					//This spins to the x of the three-booster.
	press_A_to_continue();
	move_so_blob_is_at_y(0, 35, 1, 0, 0);		//85					//This moves to the y of the three-booster.
	press_A_to_continue();
	move_so_blob_is_at_x(0, 70, 2, 0);									//This fixes any inaccuracies in the previous x fix.
	press_A_to_continue();
	move_so_blob_is_at_y(0, 35, 1, 0, 0);								//This fixes any inaccuracies caused by the second fix x.
	press_A_to_continue();
	
	
	unrelax_servos();
	start_gate();
	grab_booster(150);
	press_A_to_continue();
	lift_booster(500);
	press_A_to_continue();
	
	
	create_spin_degrees(87, 40, LEFT);
	press_A_to_continue();
	
	
	move_so_blob_is_at_x(0, 80, 2, 0);									//FIXME
	press_A_to_continue();
	create_drive_distance(12, 20, BACKWARDS);
	press_A_to_continue();
	drop_booster(DROP_BOOSTER);	
	
	return 0;
}

void spin_left_for_camera_search() { create_spin_CCW(20); }
void spin_right_for_camera_search() { create_spin_CW(20); }
void move_backwards_for_camera_search() { create_drive_straight(-40); }
void move_forwards_for_camera_search() { create_drive_straight(40); }
void stop_camera_search() { create_stop(); }
