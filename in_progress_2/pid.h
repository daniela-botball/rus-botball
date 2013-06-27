// Created on Fri June 14 2013

#ifndef _RUS_PID_H_
#define _RUS_PID_H_

#include "lego_library.h"
#include "universal_library.h"
#include "timer.h"

#define NORMAL_LSPEED 60
#define NORMAL_RSPEED 60
#define DESIRED_L_VALUE 220
#define DESIRED_R_VALUE 180
#define KP 5.0
#define KD 0.0
#define MIN_SPEED 10
#define MAX_SPEED 100
#define L_REFLECTANCE 0
#define R_REFLECTANCE 2
#define STOPPING_BUMP 0
#define LEVER 1
//#define STOPPING_TOPHAT 3
//#define STOPPING_TIME 2
//#define STOPPING_SENSOR 1

int pd_follow(int stopping_type, int i)
{
	float new_l_error, old_l_error, new_r_error, old_r_error;
	
	int l_speed, r_speed;
	
	int l_current_value, r_current_value, m_current_value;
	
	float l_derivative, r_derivative = 0;
	
	float l_multiplier, r_multiplier;
	
	int flag = 0;
	
	clear_motor_position_counter(RIGHT_MOTOR);
	
	start_timer();
	
	while (TRUE)
	{
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
		if (stopping_type == STOPPING_BUMP && digital(LEVER) == 1)
		{
			break;
		}
		
		l_current_value = analog10(L_REFLECTANCE);
		r_current_value = analog10(R_REFLECTANCE);
		
		new_l_error = (DESIRED_L_VALUE - l_current_value) / 500.0;
		new_r_error = (DESIRED_R_VALUE - r_current_value) / 500.0;
		
		if (flag > 0)
		{
			l_derivative = new_l_error - old_l_error;
			r_derivative = new_r_error - old_r_error;
		}
		flag = 1;
		
		l_multiplier = (new_l_error * KP) + (l_derivative * KD);
		r_multiplier = (new_r_error * KP) + (r_derivative * KD);
		display_printf(0, 1, "left, right current value: %4i  %4i", l_current_value, r_current_value);
		display_printf(0, 2, "left, right multiplier: %6.2f  %6.2f", l_multiplier, r_multiplier);

		if (l_multiplier < -1.0)
		{
			l_multiplier = -1.0;
		}
		if (r_multiplier < -1.0)
		{
			r_multiplier = -1.0;
		}
		if (l_multiplier > 1.0)
		{
			l_multiplier = 1.0;
		}
		if (r_multiplier > 1.0)
		{
			r_multiplier = 1.0;
		}
		l_speed = l_multiplier * 20.0 + 80.0;
		r_speed = r_multiplier * 20.0 + 80.0;
		motor(LEFT_MOTOR, l_speed);
		motor(RIGHT_MOTOR, r_speed);
		display_printf(0, 0, "left, right - %4i, %4i", l_speed, r_speed);
		
		sleep(.05);
		//display_printf(0,"%0.2f ", new);
		//display_printf("%0.2f ", old);
		//display_printf("%0.2f ", d);
		//display_printf("%3d ", ad);
		//display_printf("%0.2f ", cv);
		//display_printf("%4d ", l_speed);
		//display_printf("%4d ", r_speed);
		
		old_r_error = new_r_error;
		old_l_error = new_l_error;
	}
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
	return get_motor_position_counter(RIGHT_MOTOR);
}

#endif
