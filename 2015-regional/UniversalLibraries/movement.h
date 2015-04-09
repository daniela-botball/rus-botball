#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT -1
#define RIGHT 1

float drive_distance(int direction, float distance, float speed, float acceleration);
float drive(int direction, float speed);
int spin_degrees(int direction, int degrees, int speed);
int spin(int direction, int speed);

#endif
