// Created on Mon April 8 2013
#include "create_library.h"

#define CLIFF_LAG 0.015

void calibrate_cliffs();

int main()
{
	create_connect();
	create_full();
	//sleep(2);
	//create_get_sensor(CLIFF_FRONT_RIGHT);
	//create_get_sensor(CLIFF_FRONT_LEFT);
	//create_get_sensor(CLIFF_RIGHT);
	//create_get_sensor(CLIFF_LEFT);
	calibrate_cliffs();
	create_disconnect();
	return 0;
}

void calibrate_cliffs()
{
	while (1)
	{
		if (a_button())
		{
			while(a_button());
			break;
		}
		display_printf(0, 0, "fr cliff - %4i", create_get_sensor(CLIFF_FRONT_RIGHT));
		display_printf(0, 1, "fl cliff - %4i", create_get_sensor(CLIFF_FRONT_LEFT));
		display_printf(0, 2, " r cliff - %4i", create_get_sensor(CLIFF_RIGHT));
		display_printf(0, 3, " l cliff - %4i", create_get_sensor(CLIFF_LEFT));
		msleep(500);
	}
}




/*
void line_follow(int desired_left, int desired_right)
{
	int fl_cliff;
	int fr_cliff;
	int error;
	
	while (1)
	{
		fl_cliff = get_create_rfcliff_amt(0.015);
		error = desired_left - fl_cliff;
		
		
		if (a_button())
		{
			while(a_button());
			break;
		}
	}
	
}
*/
