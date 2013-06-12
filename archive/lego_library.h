#ifndef _LEGO_LIBRARY_H_
#define _LEGO_LIBRARY_H_

#include "universal_library.h"
#include "timer.h"

#define LEFT_MOTOR 3
#define RIGHT_MOTOR 0

#define STOPPING_TOPHAT 1
#define STOPPING_TIME 2

#define GREEN 0
#define LARGEST_BLOB 0
#define BLUE 1
#define PINK 2

#define NORMAL_LSPEED 80
#define NORMAL_RSPEED 80
#define DESIRED_LREADING 400
#define DESIRED_RREADING 400
#define LKP 0.2
#define RKP 0.2
#define MIN_SPEED 10
#define MAX_SPEED 100
#define LREFLECTANCE 1
#define RREFLECTANCE 0
#define STOPPING_SENSOR 2
#define STOPPING_THRESHOLD 100

int centimeters_to_ticks(float centimeters);
void lego_stop();
void lego_drive(int speed, int direction);
int lego_drive_distance(float centimeters, int speed, int direction);
void start_timer();
int check_timer();
void reset_timer();


void lego_drive(int speed, int direction)
{
	motor(RIGHT_MOTOR, speed * direction);
	motor(LEFT_MOTOR, speed * direction);
}

int lego_drive_distance(float centimeters, int speed, int direction)
{
	clear_motor_position_counter(LEFT_MOTOR);
	int ticks = centimeters_to_ticks(centimeters);
	lego_drive(speed, direction);
	if (direction == FORWARDS)
	{
		while (get_motor_position_counter(LEFT_MOTOR) < ticks);
	}
	else
	{
		while (get_motor_position_counter(LEFT_MOTOR) > direction * ticks);
	}
	lego_stop();
	return 0; // FIXME
}

void lego_spin(int speed, int direction)
{
	motor(RIGHT_MOTOR, speed * direction);
	motor(LEFT_MOTOR, speed * -direction);
}

int lego_spin_degrees(int degrees, int speed, int direction)
{
	clear_motor_position_counter(LEFT_MOTOR);
	int ticks = degrees_to_ticks(degrees);
	lego_spin(speed, direction);
	if (direction == LEFT)
	{
		while (get_motor_position_counter(LEFT_MOTOR) > -ticks);
	}
	else
	{
		while (get_motor_position_counter(LEFT_MOTOR) < ticks);
	}
	lego_stop();
	return 0; // FIXME
}

void lego_stop()
{
	off(RIGHT_MOTOR);
	off(LEFT_MOTOR);
}

int centimeters_to_ticks(float centimeters)
{
	
	float ticks_per_centimeter = 1050.0 / 8.0;
	float ticks = ticks_per_centimeter * centimeters;
	return (int) ticks;
}

int degrees_to_ticks(int degrees)
{
	
	int ticks_per_degree = 7;
	int ticks = ticks_per_degree * degrees;
	return ticks;
}

void line_follow(int stopping_type, int i)
{
	int rspeed = NORMAL_RSPEED;
	int lspeed = NORMAL_LSPEED;
	int actual_lreading;
	int actual_rreading;
	int l_error = 0;
	int r_error = 0;
	start_timer();
	while (1)
	{
		actual_lreading = analog10(LREFLECTANCE);
		actual_rreading = analog10(RREFLECTANCE);
		
		l_error = DESIRED_LREADING - actual_lreading;
		r_error = DESIRED_RREADING - actual_rreading;
		
		rspeed = NORMAL_RSPEED + RKP * r_error;
		lspeed = NORMAL_LSPEED + LKP * l_error;
		
		if (rspeed < MIN_SPEED)
		{
			rspeed = MIN_SPEED;
		}
		if (lspeed < MIN_SPEED)
		{
			lspeed = MIN_SPEED;
		}
		if (rspeed > MAX_SPEED)
		{
			rspeed = MAX_SPEED;
		}
		if (lspeed > MAX_SPEED)
		{
			lspeed = MAX_SPEED;
		}
		if (stopping_type == STOPPING_TOPHAT && analog10(STOPPING_SENSOR) < STOPPING_THRESHOLD)
		{
			break;
		}
		if (stopping_type == STOPPING_TIME)
		{
			if (check_timer() > i)
			{
				break;
			}
		}
		motor(LEFT_MOTOR, lspeed);
		motor(RIGHT_MOTOR, rspeed);
		display_printf(0, 0, "rspeed, lspeed: %4i, %4i", rspeed, lspeed);
		display_printf(0, 1, "rreading, lreading: %4i, %4i", actual_rreading, actual_lreading);
		msleep(20);
	}
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
	reset_timer();
}
#endif

