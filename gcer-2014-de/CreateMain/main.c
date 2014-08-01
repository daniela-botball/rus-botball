// Created on Wed March 12 2014
#include "createMovement.h"
#include "tournamentFunctions.h"
#include "timing.h"
#include "moveCalibration.h"
#include "movement.h"
#include "ui.h"
#include "teleoperation.h"

void robot_setup();

int main()
{	
	robot_setup();
	freeze(WINCH_MOTOR);
	//press_a_to_continue();
	wait_for_light(0);
	shut_down_in(110);
	msleep(10000); // FIXME: needs tuning
	
	//while(!a_button()); // loop and msleep() simulate wait_for_light()
	create_spin_degrees(10, 20, LEFT);
	create_drive_distance(5.5, 20, FORWARDS);
	drop_three_hangers_on_third_rack();
	create_disconnect();
	return 0;
}

void robot_setup() {
	int i;
	//#define _ROBOT CREATE
	//#define _MODE TOURNAMENT
	//get_robot();
	//get_mode();
	display_clear();
	//#if _ROBOT == CREATE
	printf("Connecting to the Create...\n");
	create_connect();
	printf("Create connected!");
	create_full();
	set_servo_position(LOCK_SERVO, 2000);
	enable_servos();
	//#endif
	//operate_winch(WINCH_START_POSITION);
	create_drive_distance(10, 20, FORWARDS);
	create_spin_degrees(10, 20, RIGHT);
}
