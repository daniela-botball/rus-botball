// Created on Tue June 18 2013

#include "camera_library.h"
#include "universal_library.h"
#include "timer.h"

int main()
{
	int successes, failures, no_blobs, trials, k, time, time2;

	k = 0;
	/*
	start_timer();
	shut_down_in(10);
	
	while (1) {
		++k;
		printf("%5i %5i\n", k, check_timer());
		msleep(100);
	}
	
	msleep(10000);
	*/
	trials = 100;
	successes = failures = no_blobs = 0;
	
	start_timer();
	initialize_camera(LOW_RES);
	printf("INIT time, time2 = %4i %4i.\n", check_timer(), check_timer2());
	
	for (k = 0; k < trials; ++k) {
		if (_take_a_picture() == FAILURE) {
			++ failures;
		} else {
			++ successes;
		}
		printf("k, time, time2 = %4i %4i %4i.\n", k, check_timer(), check_timer2());
		if (get_object_count(0) < 1) {
			++ no_blobs;
		}
		//msleep(100);
	}
	time = check_timer();
	time2 = check_timer2();
	printf("Failures, successes, no_blobs, time, time2 = %4i %4i %4i %4i %4i.\n", failures, successes, no_blobs, time, time2);

	return 0;
}

void spin_left_for_camera_search() {}
void spin_right_for_camera_search() {}
void move_backwards_for_camera_search() {}
void move_forwards_for_camera_search() {}
void stop_camera_search() {}
