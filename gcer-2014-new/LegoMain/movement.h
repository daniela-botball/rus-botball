// Created on Tue May 13 2014
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#define CREATE 1
#define LEGO 0

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

#define LESS_THAN -1
#define GREATER_THAN 1

extern int _ROBOT;

void robot_drive_distance(float distance, float speed, int direction);
void robot_spin_degrees(int degrees, int speed, int direction);
void robot_drive(float speed, int direction);
void robot_stop();
void lego_freeze();
void drive_until_analog_sensor(float speed, int direction, int port, int threshold, int direction_of_comparison);
int analog_comparator(int port, int threshold, int direction_of_comparison);

#endif
