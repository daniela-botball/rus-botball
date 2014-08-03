// Created on Tue May 13 2014
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#define BLACK_LINE_SENSOR 0 //UNUSED
#define CREATE_THRESHOLD 1000
#define THRESHOLD 770
#define CURRENT_THRESHOLD 64680

#define CREATE 1
#define LEGO 0

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

void create_drive_until_bump(int speed);
void move_until_line();
void move_until_line_old();
void move_until_bump(int speed, int direction, int port);
void create_virtual_bump(int speed, int direction, float maxTime);
void robot_drive_distance(float distance, float speed, int direction);

#endif
