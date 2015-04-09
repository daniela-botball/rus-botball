// Created on Sun March 22 2015
#include "movement.h"
#include "universal.h"
int main()
{
	printf("Hello World!\n");
	set_robot(LEGO_ROBOT);
	drive_distance(FORWARDS, 1000, 40, 10);
	return 0;
}
