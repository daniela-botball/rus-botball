// Created on Fri June 21 2013

#include "lego_library.h"
#include "pid.h"
#include "timer.h"
#include "universal_library.h"
#include "camera_library.h"

#define DESIRED_X 1
#define DESIRED_Y 1

#define MOVE_DELAY_TIME .05

#define SUCKER_MOTOR 2
#define LIFT_SERVO 1
#define LIFT_SERVO_DOWN_POSITION 785
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_DROP_POSITION 1885
#define BLACK_THRESHOLD 700
#define LIFT_SERVO_LOW_POSITION 1211
#define LIFT_SERVO_SEEK_POSITION 1340

void pick_up_green_pom();
void go_to_first_set_of_poms();
void get_second_green_pom();
int is_seeing_black(int sensor);
void turn_onto_line(int direction);
void arm_drop();
void arm_up();
void arm_down();
void suck_up_pom();
void test_pwm();
void line_up_far_with_green_pom();

int main()
{
	//test_pwm();
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	enable_servos();
	initialize_camera(LOW_RES);
	go_to_first_set_of_poms();
	get_second_green_pom();
	return 0;
}

void test_pwm()
{
	lego_pwm_drive(30, FORWARDS);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_drive(30, BACKWARDS);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_spin(30, RIGHT);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_spin(30, LEFT);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
}

void go_to_first_set_of_poms()
{
	pd_follow(STOPPING_TOPHAT, 0);
	lego_drive_distance(2, 20, FORWARDS);
	turn_onto_line(RIGHT);
	pd_follow(STOPPING_TIME, 2.25);
	turn_to_pile(RIGHT);
	pick_up_green_pom();
}

void get_second_green_pom()
{
	lego_spin_degrees(50, 40, LEFT);
	pick_up_green_pom();
}

void line_up_far_with_green_pom()
{
	set_servo_position(LIFT_SERVO, LIFT_SERVO_SEEK_POSITION);
	sleep(2);
	int i;
	for (i = 0; i < 2; i++)
	{
		move_so_blob_is_at(GREEN, 66, 10, MINIMUM_POM_SIZE, CENTER_X, LEFT_RIGHT, 45);
		//press_A_to_continue();
		sleep(1);
		//break;
		move_so_blob_is_at(GREEN, 99, 10, MINIMUM_POM_SIZE, CENTER_Y, BACKWARDS_FORWARDS, 45);
		//press_A_to_continue();
	}
}

void line_up_close_with_green_pom()
{
	set_servo_position(LIFT_SERVO, LIFT_SERVO_LOW_POSITION);
	sleep(2);
	int i;
	for (i = 0; i < 2; i++)
	{
		move_so_blob_is_at(GREEN, 77, 2, MINIMUM_POM_SIZE, CENTER_X, LEFT_RIGHT, 30);
		//press_A_to_continue();
		sleep(1);
		//break;
		move_so_blob_is_at(GREEN, 43, 2, MINIMUM_POM_SIZE, CENTER_Y, BACKWARDS_FORWARDS, 30);
		//press_A_to_continue();
	}
}

void pick_up_green_pom()
{
	line_up_far_with_green_pom();
	line_up_close_with_green_pom();
	set_servo_position(LIFT_SERVO, LIFT_SERVO_DOWN_POSITION);
	motor(SUCKER_MOTOR, 100);
	sleep(1);
	off(SUCKER_MOTOR);
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	sleep(1);
}

void turn_onto_line(int direction)
{
	lego_spin(30, direction);
	if (direction == RIGHT)
	{
		while (TRUE)
		{
			if (is_seeing_black(L_REFLECTANCE))
			{
				break;
			}
		}
	}
	else
	{
		while (TRUE)
		{
			if (is_seeing_black(R_REFLECTANCE))
			{
				break;
			}
		}
	}
	lego_stop();
}

int is_seeing_black(int sensor)
{
	if (analog10(sensor) > BLACK_THRESHOLD)
	{
		return TRUE;
	}
	return FALSE;
}

void turn_to_pile(int direction)
{
	lego_spin_degrees(30, 30, direction);
}
/*
void suck_up_pom()
{
	int i;
	motor(SUCKER_MOTOR, 100);
	extra_buttons_show();
	for (i = 0; i < 5; i++)
	{
		move_to_y(DESIRED_Y);
		msleep(500);
		move_to_x(DESIRED_X);
		msleep(500);
	}
	arm_down();
	sleep(1);
	arm_up();
	sleep(2);
	off(SUCKER_MOTOR);
}

void arm_down()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position > LIFT_SERVO_DOWN_POSITION; position -= 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
	off(1);
}

void arm_up()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position < LIFT_SERVO_UP_POSITION; position += 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
}

void arm_drop()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position < LIFT_SERVO_DROP_POSITION; position += 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
}
*/
void spin_left_for_camera_search(int speed) { lego_pwm_spin(speed, LEFT); }
void spin_right_for_camera_search(int speed) { lego_pwm_spin(speed, RIGHT); }
void move_backwards_for_camera_search(int speed) { lego_pwm_drive(speed, BACKWARDS); }
void move_forwards_for_camera_search(int speed) { lego_pwm_drive(speed, FORWARDS); }
void stop_camera_search() { lego_pwm_stop(); }
