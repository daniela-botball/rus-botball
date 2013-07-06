// Created on Fri July 5 2013

#include "universal_library.h"

int main()
{
	printf("Hello, World!\n");
	camera_open(LOW_RES);
	press_A_to_continue();
	
	printf("Number of objects on channel 1: %i\n", get_object_count(1));
	printf("Object data length on channel 1: %i\n", get_object_data_length(1, 0));
	return 0;
}
