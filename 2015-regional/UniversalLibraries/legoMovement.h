#ifndef _LEGOMOVEMENT_H_
#define _LEGOMOVEMENT_H_

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

float lego_drive_distance(int direction, float distance, float speed);
float lego_drive(int direction, float speed);
int lego_spin_degrees(int direction, int degrees, int speed);
int lego_spin(int direction, int speed);


#endif
