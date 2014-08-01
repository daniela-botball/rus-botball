// Created on Fri June 13 2014

#ifndef _TOURNAMENTFUNCTIONS_H_
#define _TOURNAMENTFUNCTIONS_H_

// Motor ports for this robot:
// See legoMovement.h for LEFT_MOTOR and RIGHT_MOTOR
#define TRACK_MOTOR 1

#define SORTER_SERVO 0
#define CLAW_SERVO 1
#define DUMPER_SERVO 2
#define CAMERA_SERVO 3

#define CLAW_START_POSITION CLAW_CLOSED_POSITION
#define SORTER_START_POSITION CATCH_POSITION // FIXME: Tune.
#define CAMERA_START_POSITION 2030 // was 427
#define DUMPER_START_POSITION DUMPER_CATCH_POSITION

#define FIRST_SIDE 0
#define SECOND_SIDE 1

#define CLAW_OPEN_POSITION 200
#define CLAW_HALF_OPEN_POSITION 500
#define CLAW_CLOSED_POSITION 1150

#define DUMPER_CATCH_POSITION 1670
#define DUMPER_GREEN_POSITION 530
#define DUMPER_PINK_POSITION 20

#define PINK 0
#define GREEN 1

#define MINIMUM_POM_SIZE_TO_SORT 900
#define MINIMUM_POM_SIZE 30
#define SPIN_SPEED_WHEN_USING_CAMERA 10

#define TRACK_TOPHAT 1
#define NO_POM_IN_TRACK 953
#define POM_TRACK_DELTA 100
#define TRACK_POMS_THRESHOLD NO_POM_IN_TRACK - POM_TRACK_DELTA

#define SORTER_TOPHAT 2
#define NO_POM_IN_SORTER 990
#define POM_SORTER_DELTA 250
#define SORTER_POMS_THRESHOLD NO_POM_IN_SORTER - POM_SORTER_DELTA

#define CATCH_POSITION 380
#define GREEN_POSITION 150
#define PINK_POSITION 700
#define OUT_OF_WAY_POSITION 2000

// ***********************************************************
// Functions for EATING POMS and SORTING POMS.
// ***********************************************************
void start_eating();
void stop_eating();
void start_sorting_poms();
void stop_sorting_poms();
int sort_poms_while_moving(float distance, float speed);
void sort_poms();
int pom_is_in_track();
int pom_is_in_sorter();
void sort_pom(); 
int get_pom_count(int minimum_size, int colors[], int number_of_colors);
// ***********************************************************
// Functions for MOVING TO VARIOUS PLACES.
// ***********************************************************
void side_one();
void get_out_of_box();
void get_first_group_of_poms();
void get_second_group_of_poms();
void dump_first_group_of_poms();
void move_to_side_two_and_dump();
// ***********************************************************
// Functions for DUMPING POMS.
// ***********************************************************
void dump_poms(int side);
// ***********************************************************
// Miscellaneous functions.
// ***********************************************************
void pause();
#endif
