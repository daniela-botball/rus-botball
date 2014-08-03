#include "kovan/kovan.h"
#include "createMovement.h"
#include "tournamentFunctions.h"
#include "timing.h"
#include "moveCalibration.h"
#include "movement.h"
#include "ui.h"
#include "teleoperation.h"

#define bool int
#define false 0
#define true 1

void robot_setup() {
	display_clear();
	printf("Connecting to the Create...\n");
	while(!create_connect_once()){
		printf("\a.");
		msleep(100);
	}
	printf("Create connected!");
	create_full();
	create_drive_distance(10, 20, FORWARDS);
	create_spin_degrees(15, 20, RIGHT);
}

bool isDoubleStrategy(){
	set_a_button_text("SEEDING");set_c_button_text("DOUBLE");
	bool a = false, c = false;
	do{
		while(!a && !c){
			a = a_button();
			c = c_button();
			msleep(100);
		}
	}while(a == c);
	if(a){
		printf("SEEDING\r\n");
		while(a_button()){msleep(10);}
	}
	if(c){
		printf("DOUBLE\r\n");
		while(c_button()){msleep(10);}
	}
	set_a_button_text("A");set_c_button_text("C");
	return a;
}

int main()
{	
	robot_setup();
	freeze(WINCH_MOTOR);
	printf("Select strategy\n");
	bool strategy  = isDoubleStrategy();
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
