// Created on Sat June 8 2013
#include "in_progress_2/create_library.h"

#define ROTATIONAL_POT 0
#define SLIDE_POT 1
int main()
{
	test_movement();
	return 0;
}

void test_movement()
{
	int speed, distance;
	set_a_button_text("GO");
	while (1)
	{
		speed = (analog10(SLIDE_POT) / 2043) * 500;
		distance = (analog10(ROTATIONAL_POT) / 2043) * 1000;
		display_printf(0, 0, "SPEED ----- DISTANCE");
		display_printf(0, 1, "%4i ----- %8i", speed, distance / 10);
		if (a_button())
		{
			create_drive_distance(speed, distance, FORWARDS);
		}
	}
	
}
