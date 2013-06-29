// Created on Fri June 21 2013

/*
Failures:
2) 
3) redo the start
4) the robot often bounces (use accelerometer to fix)
4) must secure the camera, and have a simple test that confirms that it is in the right place
4) must make the motor wires (especially left) stay in.  checklist!
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
#define DUMPER_SERVO 3

#define LIFT_SERVO_DOWN_POSITION 1000
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_START_POSITION LIFT_SERVO_UP_POSITION
#define LIFT_SERVO_RUN_POSITION 1880
#define LIFT_SERVO_HIGH_POSITION 1500
#define LIFT_SERVO_MIDDLE_POSITION 1400
#define LIFT_SERVO_LOW_POSITION 1280 // not used
#define LIFT_SERVO_DUMP_POSITION 1800

#define DUMPER_SERVO_START_POSITION 1200
#define DUMPER_SERVO_RUN_POSITION 1200
#define DUMPER_SERVO_COLLECT_POSITION 1200
#define DUMPER_SERVO_DUMP_POSITION 600

#define BLACK_THRESHOLD 700
#define MINIMUM_GREEN_SEARCH_SIZE 1500

void push_transport_and_turn();
void go_to_first_green_pom();
void go_to_second_green_pom();
void go_to_third_green_pom();
void go_to_fourth_green_pom();
void put_poms_into_transport();
void dump_poms();

void go_to_pom(int servo_position, int color, int x, int y, int delta, int xspeed, int yspeed);
void pick_up_green_pom();
void turn_onto_line(int direction);
int is_seeing_black(int sensor);
void move_servo_gently(int servo, int position);
void drive_until_line();

void test_pwm();

int main()
{
	
	// FIXME:  Move so that they don't crash into each other
	set_servo_position(LIFT_SERVO, LIFT_SERVO_START_POSITION);
	set_servo_position(DUMPER_SERVO, DUMPER_SERVO_START_POSITION);

	enable_servos();
	sleep(2);
	initialize_camera(LOW_RES);
	
	push_transport_and_turn();
	press_A_to_continue();
	
	go_to_first_green_pom();
	press_A_to_continue();
	
	go_to_second_green_pom();
	press_A_to_continue();
	
	go_to_third_green_pom();
	press_A_to_continue();
	
	go_to_fourth_green_pom();
	press_A_to_continue();
	
	put_poms_into_transport();
	press_A_to_continue();
	
	drive_until_line();
	
	return 0;
}

void test_pwm()
{
	lego_pwm_drive(15, FORWARDS);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_drive(15, BACKWARDS);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_spin(15, RIGHT);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
	lego_pwm_spin(15, LEFT);
	press_A_to_continue();
	lego_pwm_stop();
	sleep(1);
	press_A_to_continue();
}


void push_transport_and_turn()
{
	set_servo_position(LIFT_SERVO, LIFT_SERVO_DOWN_POSITION);
	msleep(1000);
	set_servo_position(LIFT_SERVO, LIFT_SERVO_RUN_POSITION);
	msleep(1000);
	press_A_to_continue();
	
	/* TODO: delete this after testing what follows
	lego_drive_distance(5, 30, FORWARDS);
	lego_drive_distance(5, 60, FORWARDS);
	lego_drive_distance(5, 80, FORWARDS);
	*/
	drive_until_line();
	lego_drive_distance(5, 30, FORWARDS);
	press_A_to_continue();
	
	turn_onto_line(LEFT);
}
	
void go_to_first_green_pom()
{
	lego_drive_distance(1, 40, FORWARDS);
	
	pd_follow(STOPPING_TOPHAT, 0);
	press_A_to_continue();
	turn_onto_line(RIGHT);
	
	sleep(0.2);
	lego_drive_distance(1, 30, FORWARDS);
	lego_drive_distance(1, 60, FORWARDS);
	pd_follow(STOPPING_TIME, 1.5);
	lego_spin_degrees(35, 35, RIGHT);
	pick_up_green_pom();
}

void go_to_second_green_pom()
{
	lego_drive_distance(40, 40, FORWARDS);
	lego_spin_degrees(5, 30, LEFT);
	lego_drive_distance(25, 40, FORWARDS);
	pick_up_green_pom();
}

void go_to_third_green_pom()
{
	lego_drive_distance(5, 20, FORWARDS);
	lego_spin_degrees(90, 40, LEFT);
	pick_up_green_pom();
}

void go_to_fourth_green_pom()
{
	lego_spin_degrees(90, 30, LEFT);
	lego_drive_distance(20, 40, FORWARDS);
	pick_up_green_pom();
}

void go_to_pom(int servo_position, int color, int x, int y, int delta, int xspeed, int yspeed)
{
	move_servo_gently(LIFT_SERVO, servo_position);
	int i;
	for (i = 0; i < 2; i++)
	{
		move_so_blob_is_at(color, x, delta, MINIMUM_POM_SIZE, CENTER_X, LEFT_RIGHT, xspeed);
		//press_A_to_continue();
		sleep(1); // TODO: Set this number appropriately
		//break;
		move_so_blob_is_at(color, y, delta, MINIMUM_POM_SIZE, CENTER_Y, BACKWARDS_FORWARDS, yspeed);
		//press_A_to_continue();
	}
}

void pick_up_green_pom()
{
	go_to_pom(LIFT_SERVO_HIGH_POSITION, GREEN, 84, 85, 10, 45, 60);
	go_to_pom(LIFT_SERVO_MIDDLE_POSITION, GREEN, 73, 84, 2, 15, 30); // was 6, 30, 45
	//go_to_pom(LIFT_SERVO_LOW_POSITION, GREEN, 77, 40, 2, 15, 30);
	move_servo_gently(LIFT_SERVO, LIFT_SERVO_DOWN_POSITION);
	motor(SUCKER_MOTOR, 100);
	sleep(2); // TODO: Set this number appropriately.
	off(SUCKER_MOTOR);
	move_servo_gently(LIFT_SERVO, LIFT_SERVO_UP_POSITION);
}

void turn_onto_line(int direction)
{
	lego_spin(20, direction);
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

	current_position = get_servo_position(servo);
	if (desired_position < current_position)
	{
		while (current_position > desired_position + delta) {
			current_position = current_position - delta;
			set_servo_position(servo, current_position);
			msleep(sleeptime);
		}
		
	} else {
		while (current_position < desired_position - delta) {
			current_position = current_position + delta;
			set_servo_position(servo, current_position);
			msleep(sleeptime);
		}
	}
	set_servo_position(servo, desired_position);
	msleep(sleeptime);
}

void put_poms_into_transport() {

	lego_spin_degrees(75, 40, LEFT);
	press_A_to_continue();
	drive_until_line();

    lego_spin_degrees(75, 40, LEFT); // FIXME, really 90
	press_A_to_continue();
	
	lego_drive_distance(5, 30, FORWARDS);
	lego_drive_distance(5, 60, FORWARDS);
	lego_drive_distance(15, 100, FORWARDS);
	press_A_to_continue();
	
	//lego_drive_distance(3, 30, BACKWARDS);
	//press_A_to_continue();
	
	lego_spin_degrees(75, 40, RIGHT);  // FIXME, really 90
	press_A_to_continue();
	
	dump_poms();
	press_A_to_continue();
}
	
void dump_poms() {
    set_servo_position(LIFT_SERVO, LIFT_SERVO_DUMP_POSITION);
	msleep(200);
    set_servo_position(DUMPER_SERVO, DUMPER_SERVO_DUMP_POSITION);
	msleep(1000);
}


void drive_until_line()
{
	lego_drive_distance(1, 40, FORWARDS);
	lego_drive(60, FORWARDS);
	while (analog10(STOPPING_SENSOR) < STOPPING_THRESHOLD) {}
	lego_stop();
}


void spin_left_for_camera_search(int speed) { lego_pwm_spin(speed, LEFT); }
void spin_right_for_camera_search(int speed) { lego_pwm_spin(speed, RIGHT); }
void move_backwards_for_camera_search(int speed) { lego_pwm_drive(speed, BACKWARDS); }
void move_forwards_for_camera_search(int speed) { lego_pwm_drive(speed, FORWARDS); }
void stop_camera_search() { lego_pwm_stop(); }
