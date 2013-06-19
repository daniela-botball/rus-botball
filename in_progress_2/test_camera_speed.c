// Created on Tue June 18 2013

#include "camera_library.h"
#include "universal_library.h"

int main()
{
	int successes, failures, trials, k;
	initialize_camera(LOW_RES);
	
	trials = 10;
	successes = failures = 0;
	for (k = 0; k < trials; ++k) {
		if (camera_update() == FAILURE) {
			++failures;
		} else {
			++ successes;
		}
		//msleep(100);
	}
	printf("Failures, successes = %4i %4i.\n", failures, successes);

	return 0;
}

void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backwards_for_camera_search() {}
void move_forwards_for_camera_search() {}
void stop_camera_search() {}
