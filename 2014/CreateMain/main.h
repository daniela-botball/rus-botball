// Created on Thu March 13 2014
#ifndef _MAIN_H_
#define _MAIN_H_

#define WINCH_MOTOR 1
#define BAR_SERVO 0
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1150
#define UP 1
#define DOWN -1
#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1
#define TOURNAMENT 0
#define PRACTICE 1
#define START_POSITION -1550
#define RELEASING_POSITION -525
#define SCORING_POSITION 75
#define DOUBLER_POSITION -2050
#define THRESHOLD 700

void move_until_line();
void raise_winch();
void operate_winch(int position);
void press_a_to_continue();
void pick_up_first_doubler();
void get_mode();
void drop_three_hangers();
int _mode = TOURNAMENT;

void drop_three_hangers() {
	operate_winch(START_POSITION);
	press_a_to_continue();
	operate_winch(SCORING_POSITION);
	create_drive_distance(10, 15, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 30, RIGHT);
	press_a_to_continue();
	create_drive_distance(42, 15, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(87, 30, LEFT);
	press_a_to_continue();
	create_drive_distance(103, 25, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 45, RIGHT);
	press_a_to_continue();
	//create_drive_distance(26, 15, FORWARDS);				// add black line sensor stop?
	move_until_line();
	press_a_to_continue();
	operate_winch(RELEASING_POSITION);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_OPEN_POSITION);
	press_a_to_continue();
}

void pick_up_first_doubler() {
	create_drive_distance(35, 10, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 30, LEFT);
	press_a_to_continue();
	create_drive_distance(8, 15, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 45, RIGHT);
	press_a_to_continue();
	operate_winch(DOUBLER_POSITION);
	press_a_to_continue();
	create_drive_distance(29, 20, FORWARDS);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
}

/*
void operate_winch(int position) {
	if (position == SCORING_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 50);
		while (get_motor_position_counter(WINCH_MOTOR) < 200) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	else if (position == START_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -50);
		while (get_motor_position_counter(WINCH_MOTOR) > -1550) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	else if (position == RELEASING_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -50);
		while (get_motor_position_counter(WINCH_MOTOR) > -550) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	else if (position == DOUBLER_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -50);
		while (get_motor_position_counter(WINCH_MOTOR) > -1725) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	}
}
*/

void operate_winch(int position) {
	int direction;
	if (position > 0) {
		direction = 1;
	} else {
		direction = -1;
	}
	raise_winch();
	clear_motor_position_counter(WINCH_MOTOR);
	motor(WINCH_MOTOR, 50 * direction);
	while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(position));
	//off(WINCH_MOTOR);
	freeze(WINCH_MOTOR);			
}

void raise_winch() {
	motor(WINCH_MOTOR, 50);
	while (!digital(15) && !digital(14));
	off(WINCH_MOTOR);
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

void move_until_line() {
	create_drive(60, FORWARDS);
	while (analog10(0) < THRESHOLD);
	create_stop();
}

#endif
