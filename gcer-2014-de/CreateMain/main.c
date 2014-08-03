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
	int strategy;
	robot_setup();
	freeze(WINCH_MOTOR);
	printf("Select strategy\n");
	set_a_button_text("Top Rack");
	set_b_button_text("Second Rack");
	while (1) {
		if (a_button()) {
			while(a_button());
			msleep(500);
			printf("Top Rack\n");
			strategy = 0;
			break;
		}
		if (b_button()) {
			while(b_button());
			msleep(500);
			printf("Second Rack\n");
			strategy = 1;
			break;
		}
	}
	//press_a_to_continue();
	wait_for_light(0);
	motor(WINCH_MOTOR, 100);
	msleep(250);
	freeze(WINCH_MOTOR);
	shut_down_in(110);	
	//while(!a_button()); // loop and msleep() simulate wait_for_light()
	create_spin_degrees(15, 20, LEFT);
	create_drive_distance(5.5, 20, FORWARDS);
	drop_three_hangers_on_third_rack(strategy);
	create_disconnect();
	return 0;
}

void robot_setup() {
	//int i;
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
	//#endif
	//operate_winch(WINCH_START_POSITION);
	create_drive_distance(10, 20, FORWARDS);
	create_spin_degrees(15, 20, RIGHT);
}
