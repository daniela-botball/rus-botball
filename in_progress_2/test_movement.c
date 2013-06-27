#define CREATE // or LEGO

/*
#include "universal_library"

#ifdef CREATE
#include "create_library.h"
#else
#include "lego_library.h"
#endif

#define ROTATIONAL_POT 0
#define SLIDE_POT 1
*/
typedef enum {GO_FORWARDS, GO_BACKWARDS, GO_LEFT, GO_RIGHT} Direction;

void test_movement();
void show_movement(int speed, int distance, Direction direction);

int main()
{
	//create_connect();
	test_movement();
	
	return 0;
}

void test_movement() {
	int distances[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 75, 90, 120, 180, 360};
	int speeds[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 75, 90, 120, 180, 360};
	char* directions[] = {"FWD", "BACK", "LEFT", "RIGHT"};
	int distance, speed, direction;
	
	distance = 11;	// item in array
	speed = 10;		// item in array
	direction = 0;  // 0th item in array (FWD)
	
	Button button;
	
	extra_buttons_show();
	set_a_button_text("+ distance");
	set_b_button_text("+ speed");
	set_c_button_text("Next dir");
	set_x_button_text("- distance");
	set_y_button_text("- speed");
	set_z_button_text("Go");

	display_printf(0, 0, "Speed  Distance  Direction");
	
	while (TRUE)
	{
		show_movement(speeds[speed], distances[distance], directions[direction]);
		
	    button = wait_for_button_press();
		switch button {
		    case A_BUTTON: { distance = (distance + 1) % sizeof(distances); break; }
			case B_BUTTON: { speed = (speed + 1) % sizeof(speeds); break; }
			case C_BUTTON: { direction = (direction + 1) % sizeof(directions); break; }
			case X_BUTTON: { distance = (distance - 1) % sizeof(distances); break; }
			case Y_BUTTON: { speed = (speed - 1) % sizeof(speeds); break; }
			case Z_BUTTON: { go(distances[distance], speeds[speed], directions[direction]) }
		}
	}
}

void go(int distance, int speed, char* 
    lego_forward(
		
				display_printf(0, 1, "%5i --- %8i", (int) speed, (int) (distance / 10));
	}
	
}

create_drive_distance(speed, distance, FORWARDS);
			}
			else
			{
				create_spin_degrees(speed, distance, LEFT);

void show_movement(int speed, int distance, Direction direction) {
	display_printf(0, 1, "%4i     %4i", speed, distance);
	switch direction {
		case GO_FORWARDS:	{ display_printf(14, 1, " FORWARDS"); break; }
		case GO_BACKWARDS:	{ display_printf(14, 1, "BACKWARDS"); break; }
		case GO_LEFT:		{ display_printf(14, 1, "   LEFT  "); break; }
		case GO_RIGHT:		{ display_printf(14, 1, "  RIGHT  "); break; }
	}
}
