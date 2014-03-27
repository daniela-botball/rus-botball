// Created on Thu March 13 2014
#ifndef _MAIN_H_
#define _MAIN_H_

#define WINCH_MOTOR 1
#define BAR_SERVO 0
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1200
#define UP 1
#define DOWN -1
#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1
#define TOURNAMENT 0
#define PRACTICE 1
void operate_winch(int direction, int distance);
void press_a_to_continue();
void pick_up_first_doubler();
void get_mode();
void drop_three_hangers();
int _mode = TOURNAMENT;

void drop_three_hangers() {
	operate_winch(UP, 1400);
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	create_drive_distance(10, 10, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 30, RIGHT);
	press_a_to_continue();
	create_drive_distance(42, 10, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(87, 30, LEFT);
	press_a_to_continue();
	create_drive_distance(100, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 30, RIGHT);
	press_a_to_continue();
	create_drive_distance(31, 10, FORWARDS);
	press_a_to_continue();
	operate_winch(DOWN, 250);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_OPEN_POSITION);
	press_a_to_continue();
}

void pick_up_first_doubler() {
	create_drive_distance(35, 10, BACKWARDS);
	press_a_to_continue();
	operate_winch(DOWN, 1750);
	press_a_to_continue();
	create_drive_distance(20, 10, FORWARDS);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	press_a_to_continue();
	operate_winch(UP, 250);
	press_a_to_continue();
	create_drive_distance(20, 10, BACKWARDS);
	press_a_to_continue();	
}

void operate_winch(int direction, int distance) {
	clear_motor_position_counter(WINCH_MOTOR);
	motor(WINCH_MOTOR, 50 * direction);
	while (abs(get_motor_position_counter(WINCH_MOTOR)) < distance);
	motor(WINCH_MOTOR, 0);
}

void press_a_to_continue() {
	if (_mode == PRACTICE) {
		printf("Press 'a' to continue\n");
		while (!a_button());
		while (a_button());
		msleep(500);
	} else {
		msleep(1000);
	}
}

void get_mode() {
	printf("Press 'a' for practice mode\n");
	printf("Press 'b' for tournament mode\n");
	while (1) {
		if (a_button()) {
			while (a_button());
			_mode = PRACTICE;
			msleep(500);
			break;
		} else if (b_button()) {
			_mode = TOURNAMENT;
			msleep(500);
			break;
		}
	}
}

#endif
