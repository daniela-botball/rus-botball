#include "tournamentFunctions.h"
#include "utilities.h"
#include "movement.h"
#include "legoMovement.h"
#include "camera_rus.h"
#include "servos_and_motors.h"

/*
This file contains functions specific to this year's contest.
Functions that can be used in future years should go in other files.
*/

// ***********************************************************
// Functions for EATING POMS and SORTING POMS.
// ***********************************************************

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










/*
void pom_drive() {
	int i;
	
	motor(TRACK_MOTOR, 100);
	lego_drive(PICK_UP_POM_SPEED, FORWARDS);
	msleep(2500);  // FIXME: Should be based on DISTANCE.
	motor(TRACK_MOTOR, 0);
	lego_stop();
	
	//press_a_to_continue();
	//drive_until_analog_sensor(PICK_UP_POM_SPEED, FORWARDS, POM_S_TOPHAT, SEEING_POMS_THRESHOLD, LESS_THAN);
	//lego_drive_distance(16.0, PICK_UP_POM_SPEED, FORWARDS);
	motor(LEFT_MOTOR, 40);
	motor(RIGHT_MOTOR, 80);
	
	motor(TRACK_MOTOR, 100);
	lego_drive(PICK_UP_POM_SPEED, FORWARDS);
	move_servo_very_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
	motor(TRACK_MOTOR, 0);
	lego_stop();
	//press_a_to_continue();
	
	lego_spin(50, LEFT); // FIXME: distance!
	msleep(1800);
	motor(TRACK_MOTOR, 0);
	lego_stop();
	//press_a_to_continue();
	
	set_servo_position(CLAW_SERVO, CLAW_HALF_OPEN_POSITION);
	motor(TRACK_MOTOR, 100);
	lego_drive(PICK_UP_POM_SPEED, FORWARDS);
	for (i = 0; i < 10; i++) {
		move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
		set_servo_position(CLAW_SERVO, CLAW_HALF_OPEN_POSITION);
	} 
	move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
	msleep(20000);  // FIXME.
	motor(TRACK_MOTOR, 0);
	lego_stop();
	press_a_to_continue();
	
	start_timer(0);
	while (check_timer(0) < 3.0) {
		sort_poms();
	}
	ao();
	press_a_to_continue();
}
*/

// FIXME:  Uncomment and test the following.
	/*
//Precondition: camera must be open
void sort_poms() {

	int state = DECIDE_IF_DUMP;
	int object_count;
	int green_count;
	int pink_count;
	int bottom_pom;
	camera_update();
	green_count = get_object_count(GREEN);
	pink_count = get_object_count(PINK);
	
	if (state == DECIDE_IF_DUMP) {
	bottom_pom = get_bottom_pom();
	if (get_bottom_pom() == NO_POM) {
	state = DECIDE_IF_DUMP;
	} else if (get_bottom_pom() == GREEN_POM) {
	state = DUMP_GREEN_POM;
	} else if (get_bottom_pom() == PINK_POM) {
	state = DUMP_PINK_POM;
	}
	}
	if (state == DUMP_GREEN_POM) {
	set_servo_position(SORTER_SERVO, GREEN_POSITION);
	state = DECIDE_IF_DUMP;
	}
	else if (state == DUMP_PINK_POM) {
	set_servo_position(SORTER_SERVO, PINK_POSITION);
	state = DECIDE_IF_DUMP;
	}
}
*/

/*
int get_bottom_pom() {
	return 0; // FIXME: STUB.
	// FIXME:  Uncomment and test the following.
	int green_pom_position = -1;
	int pink_pom_position = -1;
	int green_pom_size = 0;
	int pink_pom_size = 0;
	rectangle green_bbox;
	rectangle pink_bbox;
	
	if (get_object_count(GREEN) < 1 && get_object_count(PINK) < 1) {
	return NO_POM;
	}
	if (get_object_count(GREEN) > 0) {
	green_pom_size = get_object_area(GREEN, 0);
	green_bbox = get_object_bbox(GREEN, 0);
	green_pom_position = green_bbox.uly + green_bbox.height;
	} 
	if (get_object_count(PINK) > 0) {
	pink_pom_size = get_object_area(PINK, 0);
	pink_bbox = get_object_bbox(PINK, 0);
	pink_pom_position = pink_bbox.uly + pink_bbox.height;
	}
	if (green_pom_position > pink_pom_position) {
	return GREEN_POM;
	} else if (pink_pom_position > green_pom_position) {
	return PINK_POM;
	}
}
&/

void turn_until_poms_in_sight() {
	// FIXME: NOT TUNED RIGHT.  MAYBE NOT SEEING RIGHT.
	int green_rightmost_x;
	int pink_rightmost_x;
	int rightmost_x;
	motor(RIGHT_MOTOR, TURNING_SPEED);
	while (1) {
		camera_update();
		green_rightmost_x = get_rightmost_pom(GREEN, MINIMUM_POM_SIZE);
		pink_rightmost_x = get_rightmost_pom(PINK, MINIMUM_POM_SIZE);
		rightmost_x = compare(green_rightmost_x, pink_rightmost_x, LARGER);
		printf("gr:%3i, pr:%3i, r:%3i\n", green_rightmost_x, pink_rightmost_x, rightmost_x);
		if (rightmost_x > POM_POSITION_THRESHOLD) {
			break;
		}
	}
	off(RIGHT_MOTOR);
}

void test_rightmost_point() {
	set_b_button_text("Stop");
	while (!b_button()) {
		camera_update();
		display_printf(0, 0, "rightmost point: %3i", compare(get_rightmost_pom(GREEN, MINIMUM_POM_SIZE), get_rightmost_pom(PINK, MINIMUM_POM_SIZE), LARGER));
		msleep(500);
	}
}


//returns negative number if no pom is seen in given channel. otherwise returns x value of rightmost pom of given color
int get_rightmost_pom(int channel, int minimum_size) {
	int i;
	int x = -1;
	int this_x;
	rectangle bbox;
	
	//spin_left_until_see_color(channel, minimum_size);
	
	int number_of_objects = get_object_count(channel);
	for (i = 0; i < number_of_objects; i++) {
		if (get_object_area(channel, i) < minimum_size) {
			break;
		}
		bbox = transform_bbox1(get_object_bbox(channel, i));
		printf("ulx: %3i, uly: %3i, h: %3i, w: %3i\n", bbox.ulx, bbox.uly, bbox.height, bbox.width);
		this_x = bbox.ulx + bbox.width;
		if (this_x > x) {
			x = this_x;
		}
	}
	return x;
}

int spin_left_until_rightmost_pom_has_right_edge_at(int x) {
	// Precondition:  The camera can see the pom pile.
	// Goes until the rightmost edge of the rightmost object
	// in the pom pile is at or past x.
	// Returns the rightmost edge of the rightmost object.
	//
	// Assumption: No other PINK or GREEN objects will enter the picture.
	//    FIXME: Remove that assumption?  Lots of possibilities?
	
	rectangle big_box;
	int colors[] = {PINK, GREEN};
	int sizes[] = {MINIMUM_POM_SIZE, MINIMUM_POM_SIZE};
	
	return -1; // FIXME: Stub.
	
	lego_spin(SPIN_SPEED_WHEN_USING_CAMERA, LEFT);
	/*
	while (1) {
		camera_update();
		big_bbox = get_pile_bbox(colors, sizes, 2);
		if (big_bbox.ulx + big_bbox.width >= x - GOOD_ENOUGH_SPIN) {
			lego_freeze();
			break;
		}
	}
	
	return big_bbox.ulx + big_bbox.width;
}
*/

