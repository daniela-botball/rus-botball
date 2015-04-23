// Created on Tue April 21 2015

// Replace FILE with your file's name
#ifndef _LineFollow2_H_
#define _LineFollow2_H_

#define L_TOPHAT 0
#define R_TOPHAT 1
#define ET_SENSOR 2

#define STOP_BY_ET 0
#define STOP_BY_TOPHAT 1
#define STOP_BY_CAMERA 2

#define LESS_THAN 0
#define GREATER_THAN 1

// Measure these:
#define LEFT_SENSOR_ON_BLACK_DIVIDER 750 // on blue: 840
#define RIGHT_SENSOR_ON_BLACK_DIVIDER 750 // on blue: 820
#define LEFT_SENSOR_ON_WHITE 460
#define RIGHT_SENSOR_ON_WHITE 530

// MEASURE these:
#define LEFT_LINE_SENSOR_DESIRED_VALUE_ON_FRP 640 // on blue: 633 // on thick line: 955
#define RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_FRP 670 // on blue: 658 // on thick line: 980
#define LEFT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE 970
#define RIGHT_LINE_SENSOR_DESIRED_VALUE_ON_WIDE_TAPE 985

// MEASURE these.  They are not used in the code
// but are helpful to know in figuring out the TUNINGs below.
#define LEFT_LINE_SENSOR_ON_MOST_BLACK_PLACE_OF_FRP 840 // 970
#define RIGHT_LINE_SENSOR_ON_MOST_BLACK_PLACE_OF_FRP 820 // 940
#define LEFT_LINE_SENSOR_ON_MOST_WHITE_PLACE_NEAR_FRP 540 // 460
#define RIGHT_LINE_SENSOR_ON_MOST_WHITE_PLACE_NEAR_FRP 580 // 570

// TUNE (choose) these by experimenting to see what works best.
#define LINE_FOLLOWING_MAXIMUM_SPEED 80
#define LINE_FOLLOWING_MINIMUM_SPEED 5
#define LINE_FOLLOWING_NORMAL_SPEED 20
#define LEFT_kP_FOR_FRP 0.5
#define RIGHT_kP_FOR_FRP 0.5
#define LEFT_kP_FOR_WIDE_TAPE 0.15
#define RIGHT_kP_FOR_WIDE_TAPE 0.15

#define ORANGE 0

#define PINGPONG_THRESHOLD 1000

void follow_black_line(int normal_speed, int minimum_speed, int maximum_speed, int left_desired_value, int right_desired_value, float left_kP, float right_kP, int (*stopping_function)());
void drive_until(int direction, int speed, int sensor, int (*comparator)(int, int), int threshold);
void spin_until(int direction, int speed, int sensor, int (*comparator)(int, int), int threshold);
void turn_around_on_black_line(int direction, int speed);
int ET_stop();
int camera_stop();
int camera_with_time_stop();
int wall_opening_stop();
#endif
