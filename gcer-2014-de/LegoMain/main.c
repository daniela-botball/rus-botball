#include "utilities.h"
#include "tournamentFunctions.h"
#include "tests.h"
#include <string.h>
#include "legoMovement.h"
#include "movement.h"
#include "de.h"
extern int _ROBOT;
extern int _MODE;
extern char _STRATEGY[];

int main() {
	_ROBOT = LEGO;
	_MODE = PRACTICE;
	strcpy(_STRATEGY, "score_8_plus_8_poms_in_upper_storage");
	set_servo_position(0, 5);
	enable_servos();
	//test();
	//return 0;
	//780 - servo position
	int i;
	camera_open();
	for (i = 0; i < 20; i++) {
		camera_update();
	}
	int strategy = select_strategy();
	wait_for_light(0);
	move_servo_at_speed(0, 600, 800);
	msleep(700);
	if (strategy == 0) {
		set_servo_position(0, 780);
		block_poms();
	} else if (strategy == 1) {
		block_small_cubes();
	} else if (strategy == 2) {
		block_hangers();
	} else if (strategy == 3) {
		block_botguy();
	}
	shut_down_in(114.0);
	ao();
	return 0;
	lego_drive_distance(42, 80, FORWARDS);
	lego_spin_degrees(80, 80, LEFT);
	set_servo_position(3, 1900); // open claw
	lego_drive_distance(170, 80, FORWARDS);
	lego_spin_degrees(80, 80, LEFT);
	lego_drive_distance(20, 80, FORWARDS);
	return 0;
	// cube should be on tape now
	
	lego_drive_distance(20, 80, BACKWARDS);
	lego_spin_degrees(90, 80, RIGHT);
	lego_drive_distance(90, 80, BACKWARDS);
	lego_spin_degrees(90, 80, RIGHT);
	lego_drive_distance(30, 80, FORWARDS);
	set_servo_position(3, 1900);
	lego_drive_distance(80, 80, BACKWARDS);
	lego_spin_degrees(90, 80, LEFT);
	lego_drive_distance(80, 80, FORWARDS);
	lego_spin_degrees(90, 80, LEFT);
	
	lego_drive_distance(10, 80, FORWARDS);
	//drop arm
	
	return 0;
	
	setup();
    wait_for_light(0);	
	run();
	teardown();
	
	return 0;
}
