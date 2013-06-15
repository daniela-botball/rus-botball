// Created on Sun April 14 2013
#include "universal_library.h"
#include "create_library.h"
#include "lego_library.h"
#include "move_calibration.h"
#include "camera_library.h"
#include "timer.h"

#define DUMP_SERVO 2
#define DUMP_DOWN_POSITION 1523
#define DUMP_UP_POSITION 0
int main()
{
	_MODE = TOURNAMENT_MODE;
	_ROBOT = LEGO;
	camera_open(LOW_RES);
	point2 xy = get_camera_reading();
	DESIRED_X = xy.x;
	DESIRED_Y = xy.y;	
	set_servo_position(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
	set_servo_position(DUMP_SERVO, DUMP_UP_POSITION);
	enable_servos();
	wait_for_light(3);
	shut_down_in(119);
	line_follow(STOPPING_TOPHAT, 0);
	turn_calibration(90, 50, RIGHT);
	move_calibration(16, 50, FORWARDS);
	suck_up_pom();
	turn_calibration(50, 50, RIGHT);
	suck_up_pom();
	

	lego_spin(70, LEFT);
	while (analog10(LREFLECTANCE) < 400);
	while (analog10(RREFLECTANCE) < 400);
	lego_stop();
	line_follow(STOPPING_TIME, 3);
	move_calibration(2, 100, FORWARDS);
	move_calibration(2, 100, BACKWARDS);
	turn_calibration(40, 90, LEFT);
	suck_up_pom();
	turn_calibration(80, 90, RIGHT);
	suck_up_pom();
	
	lego_spin(40, RIGHT);
	sleep(2);
	while (analog10(RREFLECTANCE) < 100);
	while (analog10(LREFLECTANCE) < 100);
	lego_stop();
	line_follow(STOPPING_TOPHAT, 0);
	turn_calibration(90, 50, LEFT);
	lego_spin(70, RIGHT);
	while (analog10(RREFLECTANCE) < 400);
	while (analog10(LREFLECTANCE) < 400);
	lego_stop();
	
	sleep(20);
	line_follow(STOPPING_TIME, 3);
	move_calibration(7, 70,FORWARDS);
	turn_calibration(100, 50, RIGHT);
	move_calibration(10, 100, BACKWARDS);
	set_servo_position(DUMP_SERVO, DUMP_DOWN_POSITION);
	sleep(1);
	set_servo_position(DUMP_SERVO, DUMP_UP_POSITION);
	set_servo_position(DUMP_SERVO, DUMP_DOWN_POSITION);
	
	return 0;
}
