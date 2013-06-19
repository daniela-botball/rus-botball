// Created on Tue June 18 2013

#include "../in_progress_2/camera_library.h"

int main()
{
	int count;
	initialize_camera(LOW_RES);
	
	count = 0;
	while (camera_update() == FAILURE) {
		++count;
	}
	printf("%i failures.\n");

	return 0;
}
