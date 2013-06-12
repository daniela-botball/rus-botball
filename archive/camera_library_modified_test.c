// Created on Tue June 11 2013
#include "lego_library.h"
#include "universal_library.h"
#include "timer.h"
#include "camera_library_modified.h"

void test_find_center();

int main()
{
	test_find_center();
}

void test_find_center()
{
	camera_open(LOW_RES);
	point2 test_center;
	while (1)
	{
		test_center = find_center(GREEN, LARGEST_BLOB, 200);
		display_printf(0, 0, "%3i, %3i", test_center.x, test_center.y);
		msleep(100);
	}
}
