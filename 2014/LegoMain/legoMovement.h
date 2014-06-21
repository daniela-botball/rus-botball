// Created on Tue June 17 2014

#ifndef _LEGOMOVEMENT_H_
#define _LEGOMOVEMENT_H_

#define LEFT_MOTOR 1
#define RIGHT_MOTOR 3

#define TICKS_PER_DEGREE 10 // FIXME
#define TICKS_PER_CENTIMETER 52.0 //should be correct
#define RIGHT_MOTOR_TICKS_PER_ROTATION 940
#define LEFT_MOTOR_TICKS_PER_ROTATION 900

void lego_drive(int speed, int direction); 
void lego_spin(int speed, int direction);
void lego_stop();
void lego_drive_distance(float distance, float speed, int direction);
void lego_spin_degrees(int degrees, int speed, int direction);
#endif
