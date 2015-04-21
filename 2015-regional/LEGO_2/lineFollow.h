// Created on Sat April 18 2015

// Replace FILE with your file's name
#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#define kP 4 //2

extern float L_kP;
extern float R_Kp;

#define MAXIMUM_SPEED_DEVIATION 10
#define ET_MAXIMUM_SPEED_DEVIATION 20

extern int L_DESIRED_VALUE; // 800
extern int R_DESIRED_VALUE; //  800

#define L_TOPHAT 0
#define R_TOPHAT 1

#define ET_kP 8

#define ET_DESIRED_VALUE 500 // was 250

#define ET_SENSOR 2

#define STOP_BY_ET 0
#define STOP_BY_TOPHAT 1
#define STOP_BY_CAMERA 2

#define PINGPONG_THRESHOLD 1000

void line_follow(int direction, int desired_speed, int stopping_event);
void wall_follow(int direction, int desired_speed, int stopping_event);
int check_stopping_event(int stopping_event);
void adjust_onto_line(int direction);

#endif
