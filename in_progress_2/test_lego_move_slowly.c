// Created on Sat June 22 2013

#include "lego_library.h"
#include "universal_library.h"
#include "timer.h"
#include "camera_library.h"
#define PWM_SLEEP_ON 10
#define PWM_SLEEP_OFF 10

int CYCLE_LENGTH = 100;
float ON_LENGTH = .3;
int LEFT_BASE_SPEED = 30;
int RIGHT_BASE_SPEED = 30;
thread ID;

void drive_slowly_thread();
void turn_slowly_thread();
void move_slowly(int cycle_length, float on_length, int left_base_speed, int right_base_speed);
thread thread_move();
void stop_thread();

int main()
{
	/*while (1) {
		printf("Starting\n");
		//LEFT-RIGHT 100, .3, 20, (-)20
		//FORWARDS-BACKWARDS 100, .3, 30, 30
		move_slowly(100, .3, -30, -30);
	}*/
	camera_open(LOW_RES);
	while(!b_button())
	{
		ID = thread_move();
		while (!c_button())
		{
			camera_update();
			display_blob_numbers(0, 0, 0, 1);
		}
		stop_thread();
		press_A_to_continue();
	}
	//turn_slowly_thread();
	return 0;
}

void stop_thread()
{
	thread_destroy(ID);
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void move_slowly(int cycle_length, float on_length, int left_base_speed, int right_base_speed) {
	while (TRUE) {
		motor(LEFT_MOTOR, left_base_speed);
		motor(RIGHT_MOTOR, right_base_speed);
		msleep((int) (on_length * cycle_length));
		
		motor(LEFT_MOTOR, 0);
		motor(RIGHT_MOTOR, 0);
		msleep(cycle_length - (int) (on_length * cycle_length));
	}
}

thread thread_move()
{
	thread id = thread_create(drive_slowly_thread);
	thread_start(id);
	return id;
}

void turn_slowly_thread()
{
	move_slowly(CYCLE_LENGTH, ON_LENGTH, LEFT_BASE_SPEED, RIGHT_BASE_SPEED);
}

void drive_slowly_thread()
{
	move_slowly(CYCLE_LENGTH, ON_LENGTH, LEFT_BASE_SPEED, RIGHT_BASE_SPEED);
}

void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backwards_for_camera_search() {}
void move_forwards_for_camera_search() {}
void stop_camera_search() {}
