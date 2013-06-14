// Created on Tue June 11 2013
#include "lego_library.h"
#include "universal_library.h"
#include "timer.h"
#include "camera_library_modified.h"

void test_find_center();
void test_get_pile_bbox();
void test_face_green_pom();
void test_set_speeds();

int main()
{
	set_servo_position(0, 1100);
	enable_servos();
	camera_open(LOW_RES);
	//test_find_center();
	int i;
	//test_get_pile_bbox();
	for (i = 0; i < 3; i++)
	{
		//GOOD_ENOUGH_Y -= 1;
		GOOD_ENOUGH -= 6;
		test_face_green_pom();
		turn_to_green();
	}
	//proportional_move_to_grab();
	//PID();
	sleep(2);
	//test_set_speeds();
	//move_to_grab_green();
}

void test_find_center()
{
	set_servo_position(0, 1100);
	enable_servos();
	camera_open(LOW_RES);
	point2 test_center;
	while (1)
	{
		test_center = find_center(GREEN, LARGEST_BLOB, 200);
		display_printf(0, 0, "%3i, %3i", test_center.x, test_center.y);
		msleep(100);
	}
}

void test_get_pile_bbox()
{
	camera_open(LOW_RES);
	bbox pile;
	while (1)
	{
		pile = get_pile_bbox(ORANGE);
		display_printf(0, 0, "  l,   r,   f,   b,   c");
		display_printf(0, 1, "%3i, %3i, %3i, %3i,(%3i, %3i)", pile.left, pile.right, pile.front, pile.back, pile.center.x, pile.center.y);
		msleep(100);	
	}
}

void test_face_green_pom()
{
	camera_open(LOW_RES);
	face_green_pom();
}

void test_set_speeds()
{
	point2 robot_center = {80, 40};
	point2 green_center;
	camera_open(LOW_RES);
	float proportional_speed;
	while (1)
	{
		camera_update();
		//robot_center = get_object_center(ROBOT_MARKER, LARGEST_BLOB);
		green_center = get_object_center(GREEN, LARGEST_BLOB);
		proportional_speed = set_speeds(robot_center, green_center);
		display_printf(0, 0, "%8.2f, (%3i, %3i), (%3i, %3i)", proportional_speed, robot_center.x, robot_center.y, green_center.x, green_center.y);
	}
}
