// Created on Sun April 12 2015

#include "legoMovement.h"

#define A_BUTTON 1
#define B_BUTTON 2
#define C_BUTTON 3
#define X_BUTTON 4
#define Y_BUTTON 5
#define Z_BUTTON 6

void test_motors();
void show_buttons();
int get_choice();

int main() {
	test_motors();
	
	return 0;
}

void test_motors() {
	int left_power, right_power, choice, current_wheel;
	char label[20];
	
	printf("Running a motor test!\n");
	
	show_buttons();
	
	left_power = right_power = 100;
	current_wheel = LEFT;
	
	while (TRUE) {
		
		choice = get_choice();
		
		switch (choice) {
			case A_BUTTON: lego_drive_distance(FORWARDS, 4000, left_power, right_power);
				break;
			case B_BUTTON: lego_drive_distance(BACKWARDS, 4000, left_power, right_power);
				break;
			case C_BUTTON:
				return;
			case X_BUTTON:
				if (current_wheel == LEFT) {
					sprintf(label, "Right = %i", right_power);
					current_wheel = RIGHT;
				} else {
					sprintf(label, "Left = %i", left_power);
					current_wheel = LEFT;
				}
				set_x_button_text(label);
				break;
			case Y_BUTTON:
				if (current_wheel == LEFT) {
					left_power += 5;
					if (left_power > 100) left_power = 100;
					sprintf(label, "Left = %i", left_power);
				} else {
					right_power += 5;
					if (right_power > 100) right_power = 100;
					sprintf(label, "Right = %i", right_power);
				}
				set_x_button_text(label);
				break;

			case Z_BUTTON:
				if (current_wheel == LEFT) {
					left_power -= 1;
					if (left_power < -100) left_power = -100;
					sprintf(label, "Left = %i", left_power);
				} else {
					right_power -= 1;
					if (right_power < -100) right_power = -100;
					sprintf(label, "Right = %i", right_power);
				}
				set_x_button_text(label);
				break;
		}
	}
}

void show_buttons() {
	extra_buttons_show();
	
	set_a_button_text("Forward");
	set_b_button_text("Backward");
	set_c_button_text("Exit");
	set_x_button_text("Left = 100");
	set_y_button_text("Increase");
	set_z_button_text("Decrease");
}


int get_choice() {
	while (TRUE) {
		if (a_button()) {
			printf("Hands off!\n");
			while (a_button()) {}
			return A_BUTTON;
			
		} else if (b_button()) {
			printf("Hands off!\n");
			while (b_button()) {}
			return B_BUTTON;
			
		} else if (c_button()) {
			printf("Hands off!\n");
			while (c_button()) {}
			return C_BUTTON;
			
		} else if (x_button()) {
			printf("Hands off!\n");
			while (x_button()) {}
			return X_BUTTON;
			
		} else if (y_button()) {
			printf("Hands off!\n");
			while (y_button()) {}
			return Y_BUTTON;
		} else if (z_button()) {
			printf("Hands off!\n");
			while (z_button()) {}
			return Z_BUTTON;
		}
	}
}
