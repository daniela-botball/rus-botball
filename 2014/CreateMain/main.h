// Created on Thu March 13 2014
#ifndef _MAIN_H_
#define _MAIN_H_

#define WINCH_MOTOR 1
#define BAR_SERVO 0
#define CLAW_SERVO 1
#define GYRO_SERVO 3
#define BLACK_LINE_SENSOR 0

#define UP 1
#define DOWN -1
#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

#define TOURNAMENT 0
#define PRACTICE 1

#define WINCH_START_POSITION -1550
#define WINCH_RELEASING_POSITION -525
#define WINCH_SCORING_POSITION 25
#define WINCH_CUBE_POSITION -2650
#define DOUBLER_POSITION -2050
#define THRESHOLD 770
#define DOUBLER_PICK_UP_POSITION 400
#define GYRO_CUBE_POSITION 1850
#define GYRO_START_POSITION 0
#define CLAW_CLOSED_POSITION 300
#define CLAW_OPEN_POSITION 1200
#define BAR_START_POSITION 620
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1050

#define SERVO_INCREMENT 10
void move_until_line();
void raise_winch();
void operate_winch(int position);
void press_a_to_continue();
void pick_up_first_doubler();
void pick_up_cube();
void get_mode();
void drop_three_hangers();
int _mode = TOURNAMENT;

void drop_three_hangers() {
	operate_winch(WINCH_SCORING_POSITION);
	create_drive_distance(4, 15, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 30, RIGHT);
	press_a_to_continue();
	create_drive_distance(42, 15, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(87, 30, LEFT);
	press_a_to_continue();
	create_drive_distance(90, 25, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT);
	msleep(1000);
	press_a_to_continue();
	move_until_line();
	press_a_to_continue();
	operate_winch(WINCH_RELEASING_POSITION);
	press_a_to_continue();
	create_drive_distance(5, 15, BACKWARDS);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_OPEN_POSITION);
	press_a_to_continue();
}

void pick_up_first_doubler() {
	create_drive_distance(20, 10, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);
	press_a_to_continue();
	create_drive_distance(26, 40, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT);
	press_a_to_continue();
	operate_winch(DOUBLER_POSITION);
	press_a_to_continue();
	create_drive_distance(20, 20, FORWARDS);
	press_a_to_continue();
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	press_a_to_continue();
	operate_winch(DOUBLER_PICK_UP_POSITION);
	msleep(8000);
	create_drive_distance(20, 10, BACKWARDS);
}

void pick_up_cube() {
	create_drive_distance(20, 10, BACKWARDS);			
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT);				
	press_a_to_continue();
	operate_winch(WINCH_CUBE_POSITION);
	press_a_to_continue();
	set_servo_position(GYRO_SERVO, GYRO_CUBE_POSITION);
	press_a_to_continue();
	// winch all the way down and gyro to up or something position
	create_drive_distance(112, 20, BACKWARDS);			
	press_a_to_continue();
	create_drive_distance(3, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT);
	press_a_to_continue();
	create_drive_distance(45, 20, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);
	press_a_to_continue();
	create_drive_distance(5, 20, BACKWARDS);
	press_a_to_continue();
	create_drive_distance(70, 20, FORWARDS);
	press_a_to_continue();
	
	
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
	press_a_to_continue();


}

void operate_winch(int position) {
	int direction;
	if (position == DOUBLER_PICK_UP_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 10);
		while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(DOUBLER_PICK_UP_POSITION));
		freeze(WINCH_MOTOR);
		return;
	}
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
	while (analog10(BLACK_LINE_SENSOR) < THRESHOLD);
	create_stop();
}

void move_servo_slowly(int port, int position) {
	int i;
	if (get_servo_position(port) < position) {
		for (i = get_servo_position(port); i < position; i += SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(40);
		}
	} else if (get_servo_position(port) > position) {
		for (i = get_servo_position(port); i > position; i -= SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(40);
		}
	} else {return;}
	set_servo_position(port, position);
}

#endif
