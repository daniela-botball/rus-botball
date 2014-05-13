// Created on Sun April 13 2014
#ifndef _MOVECALIBRATION_H_
#define _MOVECALIBRATION_H_

#define CREATE 1
#define LEGO 0
#define LARGE_INCREMENT 10
#define SMALL_INCREMENT 5

#define CALIBRATION_SPEED 20

void robot_drive_distance(float distance, float speed, int direction);
void move_calibration(float distance, float speed, int direction);
#endif
