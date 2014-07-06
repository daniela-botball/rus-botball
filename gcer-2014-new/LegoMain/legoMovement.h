// Created on Tue June 17 2014

#ifndef _LEGOMOVEMENT_H_
#define _LEGOMOVEMENT_H_

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2


#define RIGHT_MOTOR_TICKS_PER_ROTATION 864 // was 940
#define LEFT_MOTOR_TICKS_PER_ROTATION 851 // was 900
#define TICKS_PER_DEGREE 8.5 // FIXME
// Calculate the following by:
//    ticks per centimeter = ticks per rotation / circumference of wheel
//                         = ticks per rotation / (diameter of wheel * pi)
#define RIGHT_MOTOR_TICKS_PER_CENTIMETER 48.123 // was 52.0, COMPUTE BY HAND
#define LEFT_MOTOR_TICKS_PER_CENTIMETER 49.0 // computed suggests 47.398
#define TICKS_PER_CENTIMETER LEFT_MOTOR_TICKS_PER_CENTIMETER

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
