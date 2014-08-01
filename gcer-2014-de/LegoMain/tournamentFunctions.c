#include "tournamentFunctions.h"
#include "utilities.h"
#include "movement.h"
#include "legoMovement.h"
#include "timing.h"
#include <stdlib.h>
#include "ui.h"
#include "camera_rus.h"
#include "servos_and_motors.h"
#include "mc_interface.h"
#include "mc_movements.h" // FIXME: movement instead of movements
/*
This file contains functions specific to this year's contest.
Functions that can be used in future years should go in other files.
*/

thread pom_sorting;

// ***********************************************************
// Functions for EATING POMS and SORTING POMS.
// ***********************************************************

void start_eating() {
	motor(TRACK_MOTOR, 100);
}

void stop_eating() {
	off(TRACK_MOTOR);
}

void start_sorting_poms() {
	pom_sorting = thread_create(sort_poms);
	thread_start(pom_sorting);
}

void stop_sorting_poms() {
	thread_destroy(pom_sorting);
}

int sort_poms_while_moving(float distance, float speed) {
	start_sorting_poms();
	lego_drive_distance(distance, speed, FORWARDS);
	return -1; // FIXME: change return type to void
}

void sort_poms() {
	int pom_count = 0;
	start_eating();
	while (pom_count < 8) {
		if (pom_is_in_track()) {
			printf("Pom is in track\n");
			motor(TRACK_MOTOR, 50);
			while (!pom_is_in_sorter());
			printf("pom is in sorter\n");
			stop_eating();
			motor(TRACK_MOTOR, -100);
			msleep(500);
			off(TRACK_MOTOR);
			sort_pom();
			msleep(1000);
			start_eating();
			pom_count++;
		}
	}
	stop_eating();
}

int pom_is_in_track() {
	// printf("track %i\n", analog10(TRACK_TOPHAT));
	return analog10(TRACK_TOPHAT) < TRACK_POMS_THRESHOLD;
}

int pom_is_in_sorter() {
	// printf("sort %i\n", analog10(SORTER_TOPHAT));
	return analog10(SORTER_TOPHAT) < SORTER_POMS_THRESHOLD;
}

// assumes pom is in sight
void sort_pom() {
	int colors[] = {GREEN, PINK};
	int pink_pom_size;
	int green_pom_size;
	int position_to_move;
	int i;
	for (i = 0; i < 10; i++) {
		camera_update();
	}
	while (get_pom_count(MINIMUM_POM_SIZE_TO_SORT, colors, 2) == 0) {
		camera_update();
	}
	printf("Pom in sight\n");
	pink_pom_size = get_object_count(PINK) > 0 ? get_object_area(PINK, 0) : -1;
	green_pom_size = get_object_count(GREEN) > 0 ? get_object_area(GREEN, 0) : -1;
	
	if (green_pom_size > MINIMUM_POM_SIZE_TO_SORT && pink_pom_size > MINIMUM_POM_SIZE_TO_SORT) {
		position_to_move = get_object_bbox(GREEN, 0).ulx > get_object_bbox(PINK, 0).ulx ? GREEN_POSITION : PINK_POSITION;
		printf("2 Poms seen, chose %i\n", position_to_move);
	} else if (green_pom_size > MINIMUM_POM_SIZE_TO_SORT) {
		printf("GREEN POM\n");
		position_to_move = GREEN_POSITION;
	} else if (pink_pom_size > MINIMUM_POM_SIZE_TO_SORT) {
		printf("PINK POM\n");
		position_to_move = PINK_POSITION;
	} else {
		printf("error is sort_pom\n");
	}
	set_servo_position(SORTER_SERVO, position_to_move);
	msleep(1000);
	set_servo_position(SORTER_SERVO, CATCH_POSITION);
}

int get_pom_count(int minimum_size, int colors[], int number_of_colors) {
	int i;
	for (i = 0; i < number_of_colors; i++) {
		if (get_object_count(i) > 0) {
			if (get_object_area(i, 0) > minimum_size) {
				return 1;
			}
		}
	}
	return 0;
}

// ***********************************************************
// Functions for MOVING TO VARIOUS PLACES.
// ***********************************************************
void side_one() {
	get_out_of_box();
	get_first_group_of_poms();
	get_second_group_of_poms();
	dump_first_group_of_poms();
	move_to_side_two_and_dump();
}
void get_out_of_box() {
	mc_move(MC_FORWARD, 14, 50);
	mc_move(MC_RIGHT, 51, 80); // was 51
	mc_move(MC_BACKWARD, 57, 50);
}
void get_first_group_of_poms() {
	mc_move(MC_LEFT, 23, 80); //25
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	mc_move(MC_FORWARD, 30, 50);
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
	msleep(1000);
}
void get_second_group_of_poms() {
	start_sorting_poms();
	mc_move(MC_RIGHT, 130, 80); //was 150
	mc_move(MC_FORWARD, 120, 50);
	mc_move(MC_RIGHT, 10, 80); // was 10
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	mc_move(MC_FORWARD, 30, 50); // needs camera action before move
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
}
void dump_first_group_of_poms() {
	mc_move(MC_RIGHT, 150, 80); // was 175 was 150
	mc_move(MC_BACKWARD, 0, 50);
	mc_move(MC_FORWARD, 60, 50); // was 130
	mc_move(MC_LEFT, 27, 80); // was 20
	mc_move(MC_FORWARD, 90, 50); // was not there
	mc_move(MC_LEFT, 170, 80);
	mc_move(MC_BACKWARD, 15, 50);
	stop_sorting_poms();
	dump_poms(FIRST_SIDE);
}

void move_to_side_two_and_dump() {
	//turn_mc_on();
	start_sorting_poms();
	mc_move(MC_FORWARD, 90, 80);
	mc_move(MC_LEFT, 90, 80);
	mc_move(MC_BACKWARD, 140, 80);
	mc_move(MC_LEFT, 90, 80);
	mc_move(MC_BACKWARD, 100, 50);
	dump_poms(SECOND_SIDE);
}

// ***********************************************************
// Functions for DUMPING POMS.
// ***********************************************************

void dump_poms(int side) {
	set_servo_position(SORTER_SERVO, OUT_OF_WAY_POSITION);
	msleep(1000);
	if (side == FIRST_SIDE) {
		move_servo_at_speed(DUMPER_SERVO, DUMPER_GREEN_POSITION, 600);
	} else if (side == SECOND_SIDE) {
		set_servo_position(DUMPER_SERVO, DUMPER_PINK_POSITION);
	} else {
		printf("Side not recognized\n");
	}
	msleep(2500);
	move_servo_at_speed(DUMPER_SERVO, DUMPER_CATCH_POSITION, 400);
	msleep(500);
	set_servo_position(SORTER_SERVO, CATCH_POSITION);
	msleep(500);
}

// ***********************************************************
// Miscellaneous functions.
// ***********************************************************

void pause() {
	stop_eating();
	lego_freeze();
	press_a_to_continue();
}
