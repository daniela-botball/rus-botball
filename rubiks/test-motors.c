// Created on Mon July 1 2013

#include "universal_library.h"
#define BLUE_GRIPPER 0
#define BLUE_SPINNER 2
#define GREEN_GRIPPER 1
#define GREEN_SPINNER 3

#define BLUE_GRIPPER_CLOSED_POSITION 610
#define BLUE_GRIPPER_OPEN_POSITION 1400
#define BLUE_GRIPPER_START_POSITION 1400

#define GREEN_GRIPPER_CLOSED_POSITION 530
#define GREEN_GRIPPER_OPEN_POSITION 1555
#define GREEN_GRIPPER_START_POSITION 1400

int main()
{
	printf("Starting test of Blue and Green gripper.\n");
	set_servo_position(BLUE_GRIPPER, BLUE_GRIPPER_START_POSITION);
	set_servo_position(GREEN_GRIPPER, GREEN_GRIPPER_START_POSITION);
	enable_servos();
	press_A_to_continue();
	
	set_servo_position(BLUE_GRIPPER, BLUE_GRIPPER_CLOSED_POSITION);
	set_servo_position(GREEN_GRIPPER, GREEN_GRIPPER_CLOSED_POSITION);
	press_A_to_continue();
	
	printf("Starting test of spinner.\n");
	
	clear_motor_position_counter(BLUE_SPINNER);
	motor(BLUE_SPINNER, 100);
	while (get_motor_position_counter(BLUE_SPINNER) < 225) ;
	off(BLUE_SPINNER);
	press_A_to_continue();
	
	clear_motor_position_counter(BLUE_SPINNER);
	motor(BLUE_SPINNER, 100);
	while (get_motor_position_counter(BLUE_SPINNER) < 225) ;
	off(BLUE_SPINNER);
	press_A_to_continue();
	
	clear_motor_position_counter(BLUE_SPINNER);
	motor(BLUE_SPINNER, 100);
	while (get_motor_position_counter(BLUE_SPINNER) < 225) ;
	off(BLUE_SPINNER);
	press_A_to_continue();
	
	return 0;
}

