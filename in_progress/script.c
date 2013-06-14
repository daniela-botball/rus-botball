// Created on Tue Apr 16 2013

#include <stdio.h>
#include "script_library.h"

int main() 
{
	create_script_drive(100, FORWARDS);
	_wait_script_distance(10);
	create_script_drive(0, FORWARDS);
	play_script();
	return 0;
}

