#ifndef _LEGOMOVEMENT_H_
#define _LEGOMOVEMENT_H_

// The next 5 really belong in the (generic) MOVEMENT library.
#define FORWARDS 1
#define BACKWARDS -1
#define LEFT -1
#define RIGHT 1
#define TRUE 1

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2

void lego_drive_distance(int direction, float distance, float speed);
void lego_spin_degrees(int direction, int degrees, int speed);

#endif
