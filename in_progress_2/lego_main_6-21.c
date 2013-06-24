// Created on Fri June 21 2013

/*
Failures:
1) the sucker does not always activate
2) the robot often bounces (use accelerometer to fix)
3) it must avoid running over poms, either with a pusher or using the camera
4) must secure the camera, and have a simple test that confirms that it is in the right place
*/

#include "lego_library.h"
#include "pid.h"
#include "timer.h"
#include "universal_library.h"
#include "camera_library.h"

#define DESIRED_X 1
#define DESIRED_Y 1

#define MOVE_DELAY_TIME .05

#define SUCKER_MOTOR 1
#define LIFT_SERVO 1

#define LIFT_SERVO_DOWN_POSITION 1000
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_HIGH_POSITION 1460
#define LIFT_SERVO_MIDDLE_POSITION 1340
#define LIFT_SERVO_LOW_POSITION 1211

#define BLACK_THRESHOLD 700
#define MINIMUM_GREEN_SEARCH_SIZE 1500

void test_pwm();
void go_to_first_green_pom();
void go_to_second_green_pom();
void go_to_third_green_pom();
void go_to_fourth_green_pom();
void go_to_pom(int servo_position, int color, int x, int y, int delta, int speed);
void pick_up_green_pom();
void turn_onto_line(int direction);
int is_seeing_black(int sensor);
void move_servo_gently(int servo, int position);

int main()
{
	motor(SUCKER_MOTOR, 100);
	sleep(100);
	//off(SUCKER_MOTOR);
	return 0;
	//test_pwm();
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	enable_servos();
	sleep(2);
	initialize_camera(LOW_RES);
	press_A_to_continue();

	go_to_first_green_pom();
	press_A_to_continue();
	go_to_second_green_pom();
	press_A_to_continue();
	go_to_third_green_pom();
	press_A_to_continue();
	go_to_fourth_green_pom();
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

void go_to_first_green_pom()
{
	lego_drive_distance(5, 30, FORWARDS);
	lego_drive_distance(5, 60, FORWARDS);

	pd_follow(STOPPING_TOPHAT, 0);
	turn_onto_line(RIGHT);
	
	sleep(0.2);
	lego_drive_distance(2, 30, FORWARDS);
	lego_drive_distance(2, 60, FORWARDS);
	pd_follow(STOPPING_TIME, 1.5);
	lego_spin_degrees(25, 25, RIGHT);
	pick_up_green_pom();
}

void go_to_second_green_pom()
{
	lego_drive_distance(25, 40, FORWARDS);
	lego_spin_degrees(5, 30, LEFT);
	lego_drive_distance(50, 40, FORWARDS);
	pick_up_green_pom();
}

void go_to_third_green_pom()
{
	lego_drive_distance(5, 20, BACKWARDS);
	lego_spin_degrees(80, 40, LEFT);
	pick_up_green_pom();
}

void go_to_fourth_green_pom()
{
	lego_spin_degrees(120, 30, LEFT);
	lego_drive_distance(20, 40, FORWARDS);
	pick_up_green_pom();
}

void go_to_pom(int servo_position, int color, int x, int y, int delta, int speed)
{
	move_servo_gently(LIFT_SERVO, servo_position);
	int i;
	for (i = 0; i < 2; i++)
	{
		move_so_blob_is_at(color, x, delta, MINIMUM_POM_SIZE, CENTER_X, LEFT_RIGHT, speed);
		//press_A_to_continue();
		sleep(1);
		//break;
		move_so_blob_is_at(color, y, delta, MINIMUM_POM_SIZE, CENTER_Y, BACKWARDS_FORWARDS, speed);
		//press_A_to_continue();
	}
}

void pick_up_green_pom()
{
	go_to_pom(LIFT_SERVO_HIGH_POSITION, GREEN, 77, 91, 10, 45);
	go_to_pom(LIFT_SERVO_MIDDLE_POSITION, GREEN, 77, 90, 6, 45);
	go_to_pom(LIFT_SERVO_LOW_POSITION, GREEN, 77, 43, 2, 30);
	move_servo_gently(LIFT_SERVO, LIFT_SERVO_DOWN_POSITION);
	motor(SUCKER_MOTOR, 100);
	sleep(3);
	off(SUCKER_MOTOR);
	move_servo_gently(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
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

void move_servo_gently(int servo, int desired_position)
{
	int current_position, k;
	int delta = 5;
	int sleeptime = 10;

	current_position = get_servo_position(LIFT_SERVO);
	if (desired_position < current_position)
	{
		while (current_position > desired_position + delta) {
			current_position = current_position - delta;
			set_servo_position(LIFT_SERVO, current_position);
			msleep(sleeptime);
		}
		
	} else {
		while (current_position < desired_position - delta) {
			current_position = current_position + delta;
			set_servo_position(LIFT_SERVO, current_position);
			msleep(sleeptime);
		}
	}
	set_servo_position(LIFT_SERVO, desired_position);
	msleep(sleeptime);
}

void spin_left_for_camera_search(int speed) { lego_pwm_spin(speed, LEFT); }
void spin_right_for_camera_search(int speed) { lego_pwm_spin(speed, RIGHT); }
void move_backwards_for_camera_search(int speed) { lego_pwm_drive(speed, BACKWARDS); }
void move_forwards_for_camera_search(int speed) { lego_pwm_drive(speed, FORWARDS); }
void stop_camera_search() { lego_pwm_stop(); }
