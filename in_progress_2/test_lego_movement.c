#define RUS // or LOVELACE

#include "universal_library.h"

#ifdef RUS
#include "lego_library.h"
#include "timer.h"
#endif

#ifdef LOVELACE
// #include "LegoSubroutines.h"
#endif

typedef enum {GO_FORWARDS, GO_BACKWARDS, GO_LEFT, GO_RIGHT} Direction;

void ramp(int direction);

Button which_button_is_pressed();
Button which_button_is_pressed() {
	if (a_button()) { hands_off(A_BUTTON); return A_BUTTON; }
	if (b_button()) { hands_off(B_BUTTON); return B_BUTTON; }
	if (c_button()) { hands_off(C_BUTTON); return C_BUTTON; }
	if (x_button()) { hands_off(X_BUTTON); return X_BUTTON; }
	if (y_button()) { hands_off(Y_BUTTON); return Y_BUTTON; }
	if (z_button()) { hands_off(Z_BUTTON); return Z_BUTTON; }
	
	return NO_BUTTON;
}

Button wait_for_button_press();
Button wait_for_button_press() {
    Button button;
	
    while (TRUE) {
		button = which_button_is_pressed();
		if (button != NO_BUTTON) {
		    return button;
		}
	}
}

void test_movement();
void show_movement(int distance, int speed, Direction direction);
void go(int distance, int speed, Direction direction);

int main() {
	test_movement();
	
	return 0;
}

void test_movement() {
	int distances[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20, 25, 30, 35, 40, 50, 60, 90, 120, 180};
	int number_of_distances = sizeof(distances) / sizeof(int);
	
	int speeds[] = {1, 2, 3, 4, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 95, 100};
	int number_of_speeds = sizeof(speeds) / sizeof(int);
	
	Direction directions[] = {GO_FORWARDS, GO_BACKWARDS, GO_LEFT, GO_RIGHT};
	int number_of_directions = sizeof(directions) / sizeof(Direction);
	
	int distance, speed, direction;
	
	distance = 2;//9;	// item in array
	speed = 1;//4;		// item in array
	direction = 0;  // 0th item in array (FWD)
	
	Button button;
	
	extra_buttons_show();
	set_a_button_text("+ distance");
	set_b_button_text("+ speed");
	set_c_button_text("Next dir");
	set_x_button_text("- distance");
	set_y_button_text("- speed");
	set_z_button_text("Go");

	_DISPLAY_PRINTF_MODE = TRUE;
	display_printf(0, 0, "Distance  Speed  Direction");
	
	while (TRUE) {
		show_movement(speeds[speed], distances[distance], directions[direction]);
		
	    button = wait_for_button_press();
		switch (button) {
		    case A_BUTTON: { distance = (distance + 1) % number_of_distances; break; }
			case B_BUTTON: { speed = (speed + 1) % number_of_speeds; break; }
			case C_BUTTON: { direction = (direction + 1) % number_of_directions; break; }
			case X_BUTTON: { distance = (distance - 1) % number_of_distances; break; }
			case Y_BUTTON: { speed = (speed - 1) % number_of_speeds; break; }
			case Z_BUTTON: { go(distances[distance], speeds[speed], directions[direction]); break; }
		}
	}
}

void show_movement(int distance, int speed, Direction direction) {
	display_printf(0, 1, "%4i     %4i", speed, distance);
	switch (direction) {
		case GO_FORWARDS:	{ display_printf(17, 1, " FORWARDS"); break; }
		case GO_BACKWARDS:	{ display_printf(17, 1, "BACKWARDS"); break; }
		case GO_LEFT:		{ display_printf(17, 1, "   LEFT  "); break; }
		case GO_RIGHT:		{ display_printf(17, 1, "  RIGHT  "); break; }
	}
}

#ifdef LOVELACE
void go(int distance, int speed, Direction direction) {
	switch (direction) {
		case GO_FORWARDS: { lego_forward(distance, speed); break; }
		case GO_BACKWARDS: { lego_backward(distance, speed); break; }
		case GO_LEFT: { lego_left(distance, speed); break; }
		case GO_RIGHT: { lego_right(distance, speed); break; }
	}
}
#endif

#ifdef RUS
void go(int distance, int speed, Direction direction) {
	switch (direction) {
		case GO_FORWARDS:	{ ramp(FORWARDS); lego_drive_distance(distance, speed, FORWARDS); break; }
		case GO_BACKWARDS:	{ ramp(BACKWARDS); lego_drive_distance(distance, speed, BACKWARDS); break; }
		case GO_LEFT:		{ lego_spin_degrees(distance, speed, LEFT); break; }
		case GO_RIGHT:		{ lego_spin_degrees(distance, speed, RIGHT); break; }
	}
}

void ramp(int direction) {
	lego_drive_distance(1, 30, direction);
	lego_drive_distance(2, 50, direction);
}
#endif
