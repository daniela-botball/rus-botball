// Created on Fri June 13 2014
#include "tournamentFunctions.h"
#include "legoMovement.h"
#include "movement.h"
#include "moveCalibration.h"
#include "timing.h"
#include "ui.h"
#include "tests.h"

void pick_up_poms();

int main()
{
	#define _ROBOT LEGO
	#define _MODE TOURNAMENT
	lego_drive_distance(2000, 80, FORWARDS);
	return 0;
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	enable_servos();
	pick_up_poms();
	return 0;
}

void pick_up_poms() {
	thread movement;
	movement = thread_create(lego_drive_distance(20, 50, FORWARDS);
	drive_to_poms(70);
	lego_spin_degrees(20, 50, LEFT);
	track_on();
	thread_run(movement);
	move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
	lego_drive_distance(200, 50, FORWARDS);
	ao();
}


