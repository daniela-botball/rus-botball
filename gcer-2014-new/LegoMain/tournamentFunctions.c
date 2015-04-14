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

// ***********************************************************
// Functions for EATING POMS and SORTING POMS.
// ***********************************************************

void grab_poms() {}

void start_eating() {
	motor(TRACK_MOTOR, 100);
}

void stop_eating() {
	off(TRACK_MOTOR);
}

void eat_poms() {
	face_poms();
	eat_poms_stage1();
	eat_poms_stage2();
}

void face_poms() {
	spin_left_until_see_a_pom_pile();
	pause();
	spin_left_until_pom_pile_is_lined_up();
	pause();
}

void eat_poms_stage1() {
	// Go until all the poms are within reach of the claw.
	// Eat as you go.
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	
	go_to_pom_pile();
	pause();
}

void go_to_pom_pile() {
	lego_drive_distance(15, PICK_UP_POM_SPEED, FORWARDS);
	pause();
}

void eat_poms_stage2() {
	// Slowly close the claw, hoping to line up the poms.
	// Eat as you go.
	start_eating();
	lego_drive(SLOW_PICK_UP_POM_SPEED, FORWARDS);
	move_servo_at_speed(CLAW_SERVO, CLAW_CLOSED_POSITION, VERY_SLOW_SERVO_SPEED);
	pause();
}

void sort_while_moving(int swipes_to_make) { // FIXME: Add DISTANCE parameter.
	int i;
	
	// FIXME: The following stops at an arbitrary point.
	// FIXME: Perhaps the open-close could be done better???
	// FIXME: Add the sorting!
	set_servo_position(CLAW_SERVO, CLAW_HALF_OPEN_POSITION);
	start_eating();
	lego_drive(WHILE_SORTING_SPEED, FORWARDS);
	
	for (i = 0; i < swipes_to_make; i++) {
		set_servo_position(CLAW_SERVO, CLAW_HALF_OPEN_POSITION);
		close_servo_while_sorting();
	}
	
	msleep(2000);
	pause();
}

void close_servo_while_sorting() {
	int i;
	int initial_position;
	int distance;
	int direction;
	int sleep_per_iteration;
	
	initial_position = get_servo_position(CLAW_SERVO);
	direction = initial_position <= CLAW_CLOSED_POSITION ? 1 : -1;
	distance = abs(initial_position - CLAW_CLOSED_POSITION);
	
	sleep_per_iteration = (int) (1000.0 * (float) MINIMUM_SERVO_INCREMENT / SLOW_SERVO_SPEED);
	start_timer(0);
	for (i = 0; i < distance; i += MINIMUM_SERVO_INCREMENT) {
		if (check_timer(0) > (sleep_per_iteration / 1000.0)) {
			set_servo_position(CLAW_SERVO, initial_position + direction * i);
			reset_timer(0);
		}
		if (pom_is_in_track()) {
			sort_pom();
		}
	}
	
	// To get exactly to the desired_position (since the above has round-off error).
	msleep(200);
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
}

int pom_is_in_track() {
	// printf("track %i\n", analog10(TRACK_TOPHAT));
	return analog10(TRACK_TOPHAT) < TRACK_POMS_THRESHOLD;
}

int pom_is_in_sorter() {
	// printf("sort %i\n", analog10(SORTER_TOPHAT));
	return analog10(SORTER_TOPHAT) < SORTER_POMS_THRESHOLD;
}

void sort_pom() {
	int position_to_move;
	printf("Sorting.\n");
	set_servo_position(SORTER_SERVO, CATCH_POSITION);
	position_to_move = get_position_to_move();
	// FIXME: if get_servo_position fails, the rest of this function will not work
	while (!pom_is_in_sorter());
	stop_eating();
	move_servo_at_speed(SORTER_SERVO, position_to_move, 1600);
	wait_for_pom_to_roll_down();
	move_servo_at_speed(SORTER_SERVO, CATCH_POSITION, 1600);
	start_eating();
}

int get_position_to_move() {
	BLOB blob;
	int colors[] = {PINK, GREEN};
	int k;
	
	for (k = 0; k < 10; ++k) {
		camera_update();
	}
	blob = biggest_blob(colors, 2);
	printf("blob color, x/y, w/h: %i %3i", blob.color, get_object_area(blob.color, 0));
	if (blob.color == GREEN) {
		return GREEN_POSITION;
		} else if (blob.color == PINK) {
		return PINK_POSITION;
		} else {
		return -1;
	}
}

void wait_for_pom_to_roll_down() {
	msleep(1000);
}

int spin_left_until_see_a_pom_pile() {
	// Spin left until the camera sees a pile of 4 poms.
	// This implementation just spins left until a sufficiently large PINK or GREEN blob is seen.
	// That will work ONLY if the robot is reasonably close to the pom pile.
	
	int colors[] = {PINK, GREEN};
	int sizes[] = {MINIMUM_POM_SIZE, MINIMUM_POM_SIZE};
	int color_found;
	
	color_found = spin_until_see_color(LEFT, colors, sizes, 2);
	
	return color_found;
}

rectangle spin_left_until_pom_pile_is_lined_up() {
	int colors[] = {PINK, GREEN};
	rectangle pile;
	
	pile = spin_until_right_edge_of_pom_pile_is_at(LEFT, colors, 2, LINED_UP_TO_EAT_POMS);
	
	return pile;
}

// ***********************************************************
// Functions for MOVING TO VARIOUS PLACES.
// ***********************************************************
void get_out_of_box() {
	mc_move(MC_FORWARD, 14, 50);
	mc_move(MC_RIGHT, 51, 80);
	mc_move(MC_BACKWARD, 55, 50);
	mc_move(MC_LEFT, 25, 80);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	mc_move(MC_FORWARD, 30, 50);
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
	msleep(1000);
	turn_mc_on();
	mc_move(MC_RIGHT, 148, 80);
	mc_move(MC_FORWARD, 110, 50);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	mc_move(MC_FORWARD, 30, 50); // needs camera action before move
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
	mc_move(MC_RIGHT, 150, 80);
	mc_move(MC_BACKWARD, 0, 50);
	mc_move(MC_FORWARD, 130, 50);
	mc_move(MC_LEFT, 180, 80);
	mc_move(MC_BACKWARD, 10, 50);
	
}

void go_close_to_first_pom_pile() {
	// FIXME: Adjust this after we know the placement in the starting box.
	// May need to "wiggle".
	lego_spin_degrees(20, TURNING_SPEED, LEFT);
	lego_drive_distance(5, TRAVELLING_SPEED, FORWARDS);
	pause();
}

void turn_to_second_pom_pile() {
	lego_spin_degrees(114, TURNING_SPEED, LEFT);
	pause();
}

void go_close_to_second_pom_pile() {
	// FIXME: This may need a camera???
	lego_drive_distance(15.0, TRAVELLING_SPEED, FORWARDS);
	pause();
}

void turn_to_first_dump() {
	lego_spin(50, LEFT); // FIXME: distance! Or use camera!
	msleep(3200);
	pause();
}

void go_close_to_our_upper_storage() {
	// FIXME: This may need a camera???
	lego_drive_distance(16.0, TRAVELLING_SPEED, FORWARDS); // FIXME: Tune.
	pause();
}

void go_close_to_opponents_upper_storage() {
	// TODO
}

void go_close_to_third_pom_pile() {
	// TODO
}

void turn_to_third_pom_pile() {
	// TODO
}

void go_close_to_fourth_pom_pile() {
	// TODO
}

void turn_to_third_dump() {
	// TODO
}

void go_close_to_opponents_upper_storage_again() {
	// TODO
}

void go_close_to_our_upper_storage_again() {
	// TODO
}

// ***********************************************************
// Functions for DUMPING POMS.
// ***********************************************************

void dump_cage(int color_of_tape) {
	line_up_using_tape_facing_forward();
	spin_180();
	line_up_using_tape_facing_backward();
	back_up_to_upper_storage();
	dump();
}

void line_up_using_tape_facing_forward() {
	// TODO
}

void spin_180() {
	lego_spin(50, LEFT); // FIXME: distance! Or use camera!
	msleep(3600);
	pause();
}

void line_up_using_tape_facing_backward() {
	// TODO
}

void back_up_to_upper_storage() {
	lego_drive_distance(16.0, TRAVELLING_SPEED, BACKWARDS); // FIXME
	// FIXME: USE A SENSOR!!!
	pause();
}

void dump() {
	// TODO
}

// ***********************************************************
// Miscellaneous functions.
// ***********************************************************

void pause() {
	stop_eating();
	lego_freeze();
	press_a_to_continue();
}

// The following function belongs in another file IF it were made robot-neutral (which I think it could be).

int spin_until_see_color(int direction, int colors[], int minimum_sizes[], int number_of_colors_to_check) {
	// Spins the robot in the given direction at a slow speed.
	// Freezes the robot as soon as the camera indicates that there is a blob
	// of any one of the given colors whose area is at least the corresponding
	// minimum_size.
	// Returns the color that the robot saw (that froze the robot).
	//
	// FIXME:  Need to make this time out if it goes too long,
	// else may lose because motors not turning off at end.
	// No point in spinning more than XX degrees, I suppose.
	// Let XX be a parameter.
	
	int color_found;
	
	lego_spin(SPIN_SPEED_WHEN_USING_CAMERA, direction);
	while (1) {
		camera_update();
		color_found = has_big_enough_blob(colors, minimum_sizes, number_of_colors_to_check);
		if (color_found >= 0) {
			break;
		}
	}
	lego_freeze();
	
	return color_found;
}

rectangle spin_until_right_edge_of_pom_pile_is_at(int direction, int colors[], int number_of_colors_to_check, int desired_x) {
	rectangle pile;
	printf("Hello world!\n");
	lego_spin(SPIN_SPEED_WHEN_USING_CAMERA, direction);
	while (1) {
		camera_update();
		
		pile = get_pile_bbox(colors, number_of_colors_to_check);
		if (pile.ulx + pile.width >= desired_x - GOOD_ENOUGH_TO_EAT) {
			break;
		}
	}
	lego_freeze();
	
	return pile;
}
