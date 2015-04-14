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
		if (TOURNAMENT_SLEEP > 0) {
			msleep(TOURNAMENT_SLEEP);
		}
		return;
	}
	
	display_clear();
	
	printf("Press 'A' to continue\n");
	while (!a_button()) {}
	printf("Hands off!\n");
	while (a_button()) {}
	msleep(500);
}

void adjust_drive(int direction, int amount) {
	char labels [4][20] = {"FORWARDS", "BACKWARDS", "forwards", "backwards"};
	int choice;
	int adjustment;
	int new_amount;
	
	if (! _ADJUST) {
		return;
	}
	_ADJUST = FALSE;
	
	set_buttons_for_adjust(labels);
	
	adjustment = 0;
	while (TRUE) {
		choice = get_choice();
		
		if (choice == A_BUTTON) {
			break;
		} else if (choice == B_BUTTON) {
			create_drive_distance(FORWARDS, BIG_DRIVE_ADJUST, 10);
			adjustment += BIG_DRIVE_ADJUST;
		} else if (choice == C_BUTTON) {
			create_drive_distance(BACKWARDS, BIG_DRIVE_ADJUST, 10);
			adjustment -= BIG_DRIVE_ADJUST;
		} else if (choice == Y_BUTTON) {
			create_drive_distance(FORWARDS, SMALL_DRIVE_ADJUST, 10);
			adjustment += SMALL_DRIVE_ADJUST;
		} else if (choice == Z_BUTTON) {
			create_drive_distance(BACKWARDS, SMALL_DRIVE_ADJUST, 10);
			adjustment -= SMALL_DRIVE_ADJUST;
		}
	}
	
	if (direction == FORWARDS) {
		new_amount = amount + adjustment;
	} else {
		new_amount = amount - adjustment;
	}
	
	printf("Was direction %i and amount %4i.\n", direction, amount);
	printf("Now direction %i and amount %4i.\n", direction, new_amount);
	
	_ADJUST = TRUE;
}

void adjust_spin(int direction, int amount) {
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

void adjust_motor(int motor_port, int position) {
	char labels [4][20] = {"MORE", "LESS", "more", "less"};
	int choice;
	int adjustment;
	
	if (! _ADJUST) {
		return;
	}
	_ADJUST = FALSE;
	
	set_buttons_for_adjust(labels);
	
	adjustment = 0;
	while (TRUE) {
		choice = get_choice();
		
		if (choice == A_BUTTON) {
			break;
		} else if (choice == B_BUTTON) {
			motor_to_position(motor_port, BIG_MOTOR_ADJUST);
			adjustment += BIG_MOTOR_ADJUST;
		} else if (choice == C_BUTTON) {
			motor_to_position(motor_port, -BIG_MOTOR_ADJUST);
			adjustment -= BIG_MOTOR_ADJUST;
		} else if (choice == X_BUTTON) {
			printf("More options is not yet implemented.\n");
		} else if (choice == Y_BUTTON) {
			motor_to_position(motor_port, SMALL_MOTOR_ADJUST);
			adjustment += SMALL_MOTOR_ADJUST;
		} else if (choice == Z_BUTTON) {
			motor_to_position(motor_port, -SMALL_MOTOR_ADJUST);
			adjustment -= SMALL_MOTOR_ADJUST;
		}
	}
	
	printf("Motor position was %4i.\n", position);
	printf("Motor position should be %4i.\n", position + adjustment);
	
	_ADJUST = TRUE;
}

void motor_to_position(int motor_port, int position) {
	clear_motor_position_counter(motor_port);
	
	if (position > 0) {
		motor(motor_port, 100);
		while (get_motor_position_counter(motor_port) < position) {}
	} else {
		motor(motor_port, -100);
		while (get_motor_position_counter(motor_port) > position) {}
	}
	freeze(motor_port);
}

void adjust_servo(int servo_port, int position) {
}

void set_buttons_for_adjust(char labels [4][20]) {
	extra_buttons_show();
	printf("Press a button.\n");
	
	set_a_button_text("Continue");
	set_x_button_text("More options");
	
	set_b_button_text(labels[0]);
	set_c_button_text(labels[1]);
	set_y_button_text(labels[2]);
	set_z_button_text(labels[3]);
}
