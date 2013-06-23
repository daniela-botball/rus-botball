// Created on Fri June 21 2013

#include "lego_library.h"
#include "pid.h"
#include "timer.h"
#include "universal_library.h"
#include "camera_library.h"

#define DESIRED_X 1
#define DESIRED_Y 1

#define MOVE_DELAY_TIME .1

#define SUCKER_MOTOR 2
#define LIFT_SERVO 1
#define LIFT_SERVO_DOWN_POSITION 785
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_DROP_POSITION 1885
#define BLACK_THRESHOLD 700
#define LIFT_SERVO_LOW_POSITION 1192

void pick_up_green_pom();
void go_to_first_set_of_poms();
int is_seeing_black(int sensor);
void turn_onto_line(int direction);
void arm_drop();
void arm_up();
void arm_down();
void suck_up_pom();

int main()
{
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	enable_servos();
	initialize_camera(LOW_RES);
	go_to_first_set_of_poms();
	return 0;
}

void go_to_first_set_of_poms()
{
	//pd_follow(STOPPING_TOPHAT, 0);
	//lego_drive_distance(2, 20, FORWARDS);
	//turn_onto_line(RIGHT);
	//pd_follow(STOPPING_TIME, 1.5);
	//turn_to_pile(RIGHT);
	//sleep(1);
	pick_up_green_pom();
}

void line_up_with_green_pom()
{
	set_servo_position(LIFT_SERVO, LIFT_SERVO_LOW_POSITION);
	sleep(2);
	int i;
	for (i = 0; i < 2; i++)
	{
		move_so_blob_is_at(GREEN, find_center(ROBOT_MARKER, LARGEST_BLOB, MINIMUM_ROBOT_MARKER_SIZE).x, 3, MINIMUM_POM_SIZE, CENTER_X, LEFT_RIGHT);
		press_A_to_continue();
		sleep(1);
		//break;
		move_so_blob_is_at(GREEN, 95, 3, MINIMUM_POM_SIZE, CENTER_Y, BACKWARDS_FORWARDS);
		press_A_to_continue();
	}
}

void pick_up_green_pom()
{
	line_up_with_green_pom();
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
	int pile_center;
	lego_spin(10, direction);
	while (TRUE)
	{
		pile_center = get_pile_bbox(ORANGE).center.x;
		if (pile_center > (SCREEN_SIZE.x / 2) - 15 && pile_center < (SCREEN_SIZE.x / 2) + 15)
		{
			break;
		}
	}
	lego_stop();
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
void spin_left_for_camera_search() {
	lego_spin(6, LEFT);
	sleep(MOVE_DELAY_TIME);
	lego_stop();
}
void spin_right_for_camera_search() {
	lego_spin(6, RIGHT);
	sleep(MOVE_DELAY_TIME);
	lego_stop();
}
void move_backwards_for_camera_search() {
	lego_drive(6, BACKWARDS);
	sleep(MOVE_DELAY_TIME);
	lego_stop();
}
void move_forwards_for_camera_search() {
	lego_drive(6, FORWARDS);
	sleep(MOVE_DELAY_TIME);
	lego_stop();
}
void stop_camera_search() { lego_stop(); }
