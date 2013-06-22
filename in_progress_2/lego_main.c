// Created on Sun April 14 2013
#include "universal_library.h"
//#include "create_library.h"
#include "lego_library.h"
#include "camera_library.h"
#include "timer.h"
#include "pid.h"

#define LIFT_SERVO 0
#define LIFT_SERVO_UP_POSITION 100

#define DUMP_SERVO 2
#define DUMP_DOWN_POSITION 1523
#define DUMP_UP_POSITION 0

void suck_up_pom();

int main()
{
	_MODE = PRACTICE_MODE;
	_ROBOT = LEGO;
	initialize_camera(LOW_RES);
	//point2 xy = get_camera_reading();
	//DESIRED_X = xy.x;
	//DESIRED_Y = xy.y;	
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	set_servo_position(DUMP_SERVO, DUMP_UP_POSITION);
	enable_servos();
	//wait_for_light(3);
	//shut_down_in(119);
	pd_follow(STOPPING_TOPHAT, 0);
	lego_spin_degrees(90, 50, RIGHT);
	lego_drive_distance(16, 50, FORWARDS);
	//suck_up_pom();
	lego_spin_degrees(50, 50, RIGHT);
	//suck_up_pom();
	

	lego_spin(70, LEFT);
	while (analog10(LREFLECTANCE) < 400);
	while (analog10(RREFLECTANCE) < 400);
	lego_stop();
	line_follow(STOPPING_TIME, 3);
	lego_drive_distance(2, 100, FORWARDS);
	lego_drive_distance(2, 100, BACKWARDS);
	lego_spin_degrees(40, 90, LEFT);
	suck_up_pom();
	lego_spin_degrees(80, 90, RIGHT);
	suck_up_pom();
	
	lego_spin(40, RIGHT);
	sleep(2);
	while (analog10(RREFLECTANCE) < 100);
	while (analog10(LREFLECTANCE) < 100);
	lego_stop();
	line_follow(STOPPING_TOPHAT, 0);
	lego_spin_degrees(90, 50, LEFT);
	lego_spin(70, RIGHT);
	while (analog10(RREFLECTANCE) < 400);
	while (analog10(LREFLECTANCE) < 400);
	lego_stop();
	
	sleep(20);
	line_follow(STOPPING_TIME, 3);
	lego_drive_distance(7, 70,FORWARDS);
	lego_spin_degrees(100, 50, RIGHT);
	lego_drive_distance(10, 100, BACKWARDS);
	set_servo_position(DUMP_SERVO, DUMP_DOWN_POSITION);
	sleep(1);
	set_servo_position(DUMP_SERVO, DUMP_UP_POSITION);
	set_servo_position(DUMP_SERVO, DUMP_DOWN_POSITION);
	
	return 0;
}

void suck_up_pom(){}
void spin_left_for_camera_search() { lego_spin(5, LEFT); }
void spin_right_for_camera_search() { lego_spin(5, RIGHT); }
void move_backwards_for_camera_search() { lego_drive(8, BACKWARDS); }
void move_forwards_for_camera_search() { lego_drive(8, FORWARDS); }
void stop_camera_search() { lego_stop(); }
