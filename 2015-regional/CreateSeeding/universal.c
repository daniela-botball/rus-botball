#include "universal.h"
#include "createMovement.h"

int _ROBOT = -1;
int _MODE = TOURNAMENT_MODE;
int _ADJUST = TRUE;

void set_robot(int robot) {
	_ROBOT = robot;
}

void set_mode(int mode) {
	_MODE = mode;
}

void press_a_to_continue() {
	if (_MODE == TOURNAMENT_MODE) {
		msleep(TOURNAMENT_SLEEP);
		return;
	}
	display_clear();
	
	if (_ADJUST) {
		adjust(FORWARDS, 99);
	}
	
	printf("Press 'A' to continue\n");
	while (!a_button()) {}
	printf("Hands off!\n");
	while (a_button()) {}
	msleep(500);
}

void adjust(int direction, int amount) {
	int choice;
	int adjustment;
	int new_amount;
	
	_ADJUST = FALSE;
	extra_buttons_show();
	set_buttons_text(direction);
	
	adjustment = 0;
	
	while (TRUE) {
		choice = get_choice(direction);
		
		if (choice == CHOICE_EXIT_ADJUST) {
			break;
		} else if (choice == CHOICE_BIG_FORWARDS) {
			create_drive_distance(FORWARDS, BIG_DRIVE, 10);
			adjustment += BIG_DRIVE;
		} else if (choice == CHOICE_BIG_BACKWARD) {
			create_drive_distance(BACKWARDS, BIG_DRIVE, 10);
			adjustment -= BIG_DRIVE;
		} else if (choice == CHOICE_BIG_RIGHT) {
			create_spin_degrees(RIGHT, BIG_SPIN, 20);
			adjustment += BIG_SPIN;
		} else if (choice == CHOICE_BIG_LEFT) {
			create_drive_distance(LEFT, BIG_SPIN, 20);
			adjustment -= BIG_SPIN;
		} else if (choice == CHOICE_SMALL_FORWARDS) {
			create_drive_distance(FORWARDS, SMALL_DRIVE, 10);
			adjustment += SMALL_DRIVE;
		} else if (choice == CHOICE_SMALL_BACKWARD) {
			create_drive_distance(BACKWARDS, SMALL_DRIVE, 10);
			adjustment -= SMALL_DRIVE;
		} else if (choice == CHOICE_SMALL_RIGHT) {
			create_spin_degrees(RIGHT, SMALL_SPIN, 20);
			adjustment += SMALL_SPIN;
		} else if (choice == CHOICE_SMALL_LEFT) {
			create_drive_distance(LEFT, SMALL_SPIN, 20);
			adjustment -= SMALL_SPIN;
		}
	}
	
	if (direction == FORWARDS || direction == RIGHT) {
		new_amount = amount + adjustment;
	} else {
		new_amount = amount - adjustment;
	}
	
	printf("Was direction %i and amount %4i.\n", direction, amount);
	printf("Now direction %i and amount %4i.\n", direction, new_amount);
	
	_ADJUST = TRUE;
}

int get_choice(int direction) {
	while (TRUE) {
		if (a_button()) {
			printf("Hands off!\n");
			while (a_button()) {}
			return (direction == FORWARDS || direction == BACKWARDS) ? CHOICE_BIG_FORWARDS : CHOICE_BIG_RIGHT;
			
		} else if (b_button()) {
			printf("Hands off!\n");
			while (b_button()) {}
			return (direction == FORWARDS || direction == BACKWARDS) ? CHOICE_BIG_BACKWARD : CHOICE_BIG_LEFT;
			
		} else if (c_button()) {
			printf("Hands off!\n");
			while (c_button()) {}
			return CHOICE_EXIT_ADJUST;
			
		} else if (x_button()) {
			printf("Hands off!\n");
			while (x_button()) {}
			return (direction == FORWARDS || direction == BACKWARDS) ? CHOICE_SMALL_FORWARDS : CHOICE_SMALL_RIGHT;
			
		} else if (y_button()) {
			printf("Hands off!\n");
			while (y_button()) {}
			return (direction == FORWARDS || direction == BACKWARDS) ? CHOICE_SMALL_BACKWARD : CHOICE_SMALL_LEFT;
		}
	}
}
	
void set_buttons_text(int direction) {
	if (direction == FORWARDS || direction == BACKWARDS) {
		set_a_button_text("FORWARDS");
		set_b_button_text("BACKWARD");
		set_c_button_text("EXIT");
		set_x_button_text("forwards");
		set_y_button_text("backwards");
	} else {
		set_a_button_text("RIGHT");
		set_b_button_text("LEFT");
		set_c_button_text("EXIT");
		set_x_button_text("right");
		set_y_button_text("left");
	}
}
