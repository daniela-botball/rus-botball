#include "kovan/kovan.h"
#include "createMovement.h"
#include "tournamentFunctions.h"
#include "timing.h"
#include "moveCalibration.h"
#include "movement.h"
#include "ui.h"
#include "teleoperation.h"

void robot_setup();
#define bool int
#define false 0
#define true 1

int main()
{	
	int strategy;
	robot_setup();
	freeze(WINCH_MOTOR);
	printf("Select strategy\n");
	set_a_button_text("Seeding");
	set_b_button_text("DE");
	while (1) {
		if (a_button()) {
			while(a_button());
			msleep(500);
			printf("Seeding strategy\n");
			strategy = 0;
			break;
		}
		if (b_button()) {
			while(b_button());
			msleep(500);
			printf("DE strategy\n");
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
	if (strategy == 1) {
		msleep(10000); // FIXME: needs tuning
	}
	
	//while(!a_button()); // loop and msleep() simulate wait_for_light()
	create_spin_degrees(15, 20, LEFT);
	create_drive_distance(5.5, 20, FORWARDS);
	drop_three_hangers_on_third_rack();
	create_disconnect();
	return 0;
}

void robot_setup() {
	display_clear();
	printf("Connecting to the Create...\n");
	create_connect();
	printf("Create connected!");
	create_full();
	create_drive_distance(10, 20, FORWARDS);
	create_spin_degrees(15, 20, RIGHT);
}
