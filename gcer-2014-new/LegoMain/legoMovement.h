// Created on Tue June 17 2014

#ifndef _LEGOMOVEMENT_H_
#define _LEGOMOVEMENT_H_

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2

#define TICKS_PER_DEGREE 10 // FIXME
#define TICKS_PER_CENTIMETER 52.0 //should be correct
#define RIGHT_MOTOR_TICKS_PER_ROTATION 940
#define LEFT_MOTOR_TICKS_PER_ROTATION 900

typedef struct {
	int left_power;
	int right_power;
} WHEELS_MOTOR_POWER;

// FIXME: These don't really belong here, perhaps.
#define ADJUST_LEFT 1.0
#define ADJUST_RIGHT 1.0

void lego_drive(float speed, int direction); 
void lego_spin(int speed, int direction);
void lego_stop();
void lego_freeze();
void lego_drive_distance(float distance, float speed, int direction);
void lego_spin_degrees(int degrees, int speed, int direction);

WHEELS_MOTOR_POWER lego_drive_powers(float speed, int direction);
WHEELS_MOTOR_POWER lego_spin_powers(float speed, int direction);

#endif
