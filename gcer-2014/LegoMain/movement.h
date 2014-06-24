// Created on Tue May 13 2014
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#define CREATE 1
#define LEGO 0

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

#define POM_S_TOPHAT 1
#define SEEING_POMS_THRESHOLD 800

void robot_drive_distance(float distance, float speed, int direction);
void drive_to_poms(int speed);

#endif
