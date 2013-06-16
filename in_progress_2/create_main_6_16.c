// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"


int main()
{
	printf("Program starts OK\n");
	create_connect();
	printf("Connected!");
	create_full();
	start_servos();
	press_a_to_continue();
	begin_servos();
	press_a_to_continue();
	sleep(1);
	relax_servos();	
	press_a_to_continue();
	create_drive_distance(10, 5, FORWARDS);
	
	return 0;
}
