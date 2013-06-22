// Created on Sat June 8 2013
#include "create_library.h"

#define ROTATIONAL_POT 0
#define SLIDE_POT 1
int main()
{
	create_connect();
	test_movement();
	return 0;
}

void test_movement()
{
	float speed, distance;
	int direction = 1;
	set_a_button_text("GO");
	while (1)
	{
		speed = ((float) analog10(SLIDE_POT) / 2043.0) * 1000.0;
		distance = ((float) analog10(ROTATIONAL_POT) / 2043.0) * 1000.0;
		display_printf(0, 0, "SPEED --- DISTANCE");
		display_printf(0, 1, "%5i --- %8i", (int) speed, (int) (distance / 10));
		if (a_button())
		{
			if (direction == -1)
			{
				create_drive_distance(speed, distance, FORWARDS);
			}
			else
			{
				create_spin_degrees(speed, distance, LEFT);
			}
		}
		if (b_button())
		{
			direction *= -1;
		}
	}
	
}
