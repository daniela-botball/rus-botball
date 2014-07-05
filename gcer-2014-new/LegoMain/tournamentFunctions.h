// Created on Fri June 13 2014

#ifndef _TOURNAMENTFUNCTIONS_H_
#define _TOURNAMENTFUNCTIONS_H_

// Motor ports for this robot:
// See legoMovement.h for LEFT_MOTOR and RIGHT_MOTOR
#define TRACK_MOTOR 1

// Servo ports for this robot:
#define CLAW_SERVO 1
#define SORTER_SERVO 0
#define CAMERA_SERVO 3
#define DUMPER_SERVO 2

#define CLAW_START_POSITION 200 // ALL THE WAY OPEN
#define SORTER_START_POSITION 0 // FIXME: Tune.
#define CAMERA_START_POSITION 772 // FIXME: Tune.
#define DUMPER_START_POSITION 0 // FIXME: Tune.

#define CLAW_OPEN_POSITION 200
#define CLAW_HALF_OPEN_POSITION 500
#define CLAW_CLOSED_POSITION 1150

#define PINK_CHANNEL 0
#define GREEN_CHANNEL 1

#define MINIMUM_POM_SIZE 30
#define SPIN_SPEED_WHEN_USING_CAMERA 10

// X coordinate of right edge of pile when the robot
// is lined up to move forward to eat poms.
// Assumes that the distance is roughly some fixed amount.
#define LINED_UP_TO_EAT_POMS 100 // FIXME: Tune.
#define GOOD_ENOUGH_TO_EAT 5 // FIXME: Tune.


#define POM_S_TOPHAT 1
#define NO_POM_IN_TRACK 953
#define POM_DELTA 20
#define SEEING_POMS_THRESHOLD NO_POM_IN_TRACK - POM_DELTA

#define POM_SIZE_THRESHOLD 500

#define PICK_UP_POM_SPEED 40 // was 90.0
#define TRAVELLING_SPEED 80




#define POM_POSITION_THRESHOLD 75
#define TURNING_SPEED 30


#define GREEN_POSITION 403
#define PINK_POSITION 780



#define SLOW 10
#define MEDIUM 50
#define FAST 100


#define NO_POM -1
#define GREEN_POM 0
#define PINK_POM 1

#define DECIDE_IF_DUMP -1
#define DUMP_GREEN_POM 0
#define DUMP_PINK_POM 1

// ***********************************************************
// Functions for EATING POMS and SORTING POMS.
// ***********************************************************
void start_eating();
void stop_eating();
void eat_poms();
void face_poms();
void go_to_pom_pile();
void eat_poms_stage1();
void eat_poms_stage2();
void sort_while_moving(); // FIXME: Add DISTANCE parameter.

int spin_left_until_see_a_pom_pile();
rectangle spin_left_until_pom_pile_is_lined_up();
int spin_until_see_color(int direction, int colors[], int minimum_sizes[], int number_of_colors_to_check);
rectangle spin_until_right_edge_of_pom_pile_is_at(int direction, int colors[], int number_of_colors_to_check, int desired_x);

// ***********************************************************
// Functions for MOVING TO VARIOUS PLACES.
// ***********************************************************
void go_close_to_first_pom_pile();
void turn_to_second_pom_pile();
void go_close_to_second_pom_pile();
void turn_to_first_dump();
void go_close_to_our_upper_storage();
void go_close_to_opponents_upper_storage();
void go_close_to_third_pom_pile();
void turn_to_third_pom_pile();
void go_close_to_fourth_pom_pile();
void turn_to_third_dump();
void go_close_to_opponents_upper_storage_again();
void go_close_to_our_upper_storage_again();

// ***********************************************************
// Functions for DUMPING POMS.
// ***********************************************************

void dump_cage(int color_of_tape);
void line_up_using_tape_facing_forward();
void spin_180();
void line_up_using_tape_facing_backward();
void back_up_to_upper_storage();
void dump();
	
// ***********************************************************
// Miscellaneous functions.
// ***********************************************************
void pause();

// These are specific to this year's contest.
/*
void move_out_of_starting_box();

void face_poms();
void eat_poms_stage1();
void eat_poms_stage2();
void eat_poms_stage3();

void turn_to_2nd_poms();
void go_to_2nd_poms();
void turn_to_1st_dump();

void go_to_1st_dump();
void turn_for_dump();
void reverse_to_wall();
void dump_small_bin();
	
void pom_drive();
void sort_poms();
int get_bottom_pom();
rectangle transform_bbox(rectangle bbox);
int get_rightmost_pom(int channel, int minimum_size);
void test_rightmost_point();
void turn_until_poms_in_sight();


*/
#endif
