#include "universal.h"
#include "createMovement.h"
#include <string.h>

int _ROBOT = -1;
int _MODE = TOURNAMENT_MODE;
int _ADJUST = TRUE;
int _TOURNAMENT_SLEEP = 0;

void set_robot(int robot) {
	_ROBOT = robot;
}

void set_mode(int mode) {
	_MODE = mode;
}

void press_a_to_continue() {
	if (_MODE == TOURNAMENT_MODE) {
		if (_TOURNAMENT_SLEEP > 0) {
			msleep(_TOURNAMENT_SLEEP);
		}
		return;
	}
	
	extra_buttons_hide();
	set_a_button_text("A");
	set_b_button_text("B");
	set_c_button_text("C");
	
	printf("Press 'A' to continue\n");
	while (!a_button()) {}
	printf("Hands off!\n");
	while (a_button()) {}
	
	display_clear();
	msleep(500);
}

void adjust_drive(int direction, int amount) {
	char labels [4][20] = {"FORWARDS", "BACKWARDS", "forwards", "backwards"};
	char direction_label[20];
	char opposite_direction_label[20];
	char new_direction_label[20];
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
		strcpy(direction_label, "FORWARDS");
		strcpy(opposite_direction_label, "BACKWARDS");
	} else {
		new_amount = amount - adjustment;
		strcpy(direction_label, "BACKWARDS");
		strcpy(opposite_direction_label, "FORWARDS");
	}
	
	if (new_amount > 0) {
		strcpy(new_direction_label, direction_label); // Same direction
	} else {
		strcpy(new_direction_label, opposite_direction_label); // Opposite direction
		new_amount = -new_amount;
	}
	
	printf("Was direction %9s, amount %4i.\n", direction_label, amount);
	printf("Now direction %9s, amount %4i.\n", new_direction_label, new_amount);
	
	_ADJUST = TRUE;
	
	press_a_to_continue();
}

void adjust_spin(int direction, int amount) {
	char labels [4][20] = {"RIGHT", "LEFT", "right", "left"};
	char direction_label[20];
	char opposite_direction_label[20];
	char new_direction_label[20];
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
			create_spin_degrees(RIGHT, BIG_SPIN_ADJUST, 10);
			adjustment += BIG_DRIVE_ADJUST;
		} else if (choice == C_BUTTON) {
			create_spin_degrees(LEFT, BIG_SPIN_ADJUST, 10);
			adjustment -= BIG_DRIVE_ADJUST;
		} else if (choice == Y_BUTTON) {
			create_spin_degrees(RIGHT, SMALL_SPIN_ADJUST, 10);
			adjustment += SMALL_DRIVE_ADJUST;
		} else if (choice == Z_BUTTON) {
			create_spin_degrees(LEFT, SMALL_SPIN_ADJUST, 10);
			adjustment -= SMALL_DRIVE_ADJUST;
		}
	}
	
	if (direction == RIGHT) {
		new_amount = amount + adjustment;
		strcpy(direction_label, "RIGHT");
		strcpy(opposite_direction_label, "LEFT");
	} else {
		new_amount = amount - adjustment;
		strcpy(direction_label, "LEFT");
		strcpy(opposite_direction_label, "RIGHT");
	}
	
	if (new_amount > 0) {
		strcpy(new_direction_label, direction_label); // Same direction
	} else {
		strcpy(new_direction_label, opposite_direction_label); // Opposite direction
		new_amount = -new_amount;
	}
	
	printf("Was direction %9s, amount %4i.\n", direction_label, amount);
	printf("Now direction %9s, amount %4i.\n", new_direction_label, new_amount);
	
	_ADJUST = TRUE;
	
	press_a_to_continue();
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
	
	printf("Motor position was:       %4i.\n", position);
	printf("Motor position should be: %4i.\n", position + adjustment);
	
	_ADJUST = TRUE;
	
	press_a_to_continue();
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
			set_servo_position(servo_port, get_servo_position(servo_port) + BIG_SERVO_ADJUST);
			adjustment += BIG_SERVO_ADJUST;
		} else if (choice == C_BUTTON) {
			set_servo_position(servo_port, get_servo_position(servo_port) - BIG_SERVO_ADJUST);
			adjustment -= BIG_SERVO_ADJUST;
		} else if (choice == X_BUTTON) {
			printf("More options is not yet implemented.\n");
		} else if (choice == Y_BUTTON) {
			set_servo_position(servo_port, get_servo_position(servo_port) + SMALL_SERVO_ADJUST);
			adjustment += SMALL_SERVO_ADJUST;
		} else if (choice == Z_BUTTON) {
			set_servo_position(servo_port, get_servo_position(servo_port) - SMALL_SERVO_ADJUST);
			adjustment -= SMALL_SERVO_ADJUST;
		}
	}
	
	printf("Servo position was:       %4i.\n", position);
	printf("Servo position should be: %4i.\n", position + adjustment);
	
	_ADJUST = TRUE;
	
	press_a_to_continue();
}

void set_buttons_for_adjust(char labels [4][20]) {
	extra_buttons_show();
	printf("Choose a button.\n");
	
	set_a_button_text("Show adjustment");
	set_x_button_text("More options");
	
	set_b_button_text(labels[0]);
	set_c_button_text(labels[1]);
	set_y_button_text(labels[2]);
	set_z_button_text(labels[3]);
}
