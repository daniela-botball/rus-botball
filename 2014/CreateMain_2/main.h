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
#define DOUBLER_POSITION -2050
#define THRESHOLD 700
#define DOUBLER_PICK_UP_POSITION 400
#define CUBE_POSITION -2000 							// FIXME
#define GYRO_CUBE_POSITION 320
#define GYRO_SETTING_POSITION 2000
#define GYRO_START_POSITION 1000
#define CLAW_CLOSED_POSITION 300
#define CLAW_OPEN_POSITION 1200
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1050

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
	operate_winch(WINCH_START_POSITION);
	press_a_to_continue();
	operate_winch(WINCH_SCORING_POSITION);
	create_drive_distance(10, 15, FORWARDS);
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
	create_drive_distance(20, 10, BACKWARDS);			// FIXME
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);					// FIXME
	press_a_to_continue();
	create_drive_distance(50, 20, FORWARDS);			// FIXME
	press_a_to_continue();
	operate_winch(CUBE_POSITION);
	press_a_to_continue();
	set_servo_position(GYRO_SERVO, GYRO_CUBE_POSITION);
	press_a_to_continue();
	set_servo_position(CLAW_SERVO, CLAW_CLOSED_POSITION);
	press_a_to_continue();
	
	
}

	
/*
void operate_winch(int position) {
	if (position == WINCH_SCORING_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 50);
		while (get_motor_position_counter(WINCH_MOTOR) < 200) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	else if (position == WINCH_START_POSITION) {
		raise_winch();
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -50);
		while (get_motor_position_counter(WINCH_MOTOR) > -1550) ;
		off(WINCH_MOTOR);
		freeze(WINCH_MOTOR);
	else if (position == WINCH_RELEASING_POSITION) {
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

void press_a_to_continue_old() {
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

#define SLEEP_MSECONDS_IN_TOURNAMENT_MODE 1000
#define SLOW_CREATE_LINEAR_SPEED 20
#define SLOW_CREATE_ANGULAR_SPEED 20
#define SPEED_FOR_ADJUSTING_WINCH 50
#define GYRO_SERVO_ADJUSTMENT_AMOUNT 10
#define GYRO_SERVO_ADJUSTMENT_MSECONDS 500
#define CLAW_SERVO_ADJUSTMENT_AMOUNT 10
#define CLAW_SERVO_ADJUSTMENT_MSECONDS 250
#define BAR_SERVO_ADJUSTMENT_AMOUNT 10
#define BAR_SERVO_ADJUSTMENT_MSECONDS 250

void adjust();
void adjust_winch_or_gyro();
void adjust_movement();
int adjust_claw_or_bar();
void set_buttons_for_winch_and_gyro();
void set_buttons_for_movement();
void set_buttons_for_claw_and_bar();
void set_buttons_to_abc();

void press_a_to_continue() {
	if (_mode == PRACTICE) {
		printf("Press 'a' to continue, 'c' to adjust.\n");
		while (1) {
			if (a_button()) {
				while (a_button());
				msleep(500);
				break;
			}
			if (c_button()) {
				while (c_button());
				msleep(500);
				adjust();
				break;
			}
		}
	} else {
		msleep(SLEEP_MSECONDS_IN_TOURNAMENT_MODE);
	}
}

void adjust() {
	extra_buttons_show();
	adjust_winch_or_gyro();
	extra_buttons_hide();
	set_buttons_to_abc();
}

void adjust_movement() {
	int exit_to_winch_gyro;
	
	set_buttons_for_movement();
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(500);
			return;
		}
		if (b_button()) {
			set_create_distance(0);
			create_drive_straight(SLOW_CREATE_LINEAR_SPEED);
			while (b_button());
			create_stop();
			printf("%4i mm (forward)\n", get_create_distance());
		}
		if (c_button()) {
			set_create_distance(0);
			create_drive_straight(-SLOW_CREATE_LINEAR_SPEED);
			while (c_button());
			create_stop();
			printf("%4i mm (backwards)\n", get_create_distance());
		}
		if (y_button()) {
			set_create_total_angle(0);
			create_spin_CCW(SLOW_CREATE_ANGULAR_SPEED);
			while (y_button());
			create_stop();
			printf("%4i degrees (spin left - CCW)\n",
			    get_create_total_angle());
		}
		if (z_button()) {
			set_create_total_angle(0);
			create_spin_CW(SLOW_CREATE_ANGULAR_SPEED);
			while (z_button());
			create_stop();
			printf("%4i degrees (spin right - CW)\n",
			    get_create_total_angle());
		}
		if (x_button()) {
			while (x_button());
			exit_to_winch_gyro = adjust_claw_or_bar();
			if (exit_to_winch_gyro) {
				return;
			}
			set_buttons_for_movement();
		}
	}
}

void adjust_winch_or_gyro() {	
	set_buttons_for_winch_and_gyro();
	
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(500);
			return;
		}
		if (b_button()) {
			clear_motor_position_counter(WINCH_MOTOR);
			motor(WINCH_MOTOR, SPEED_FOR_ADJUSTING_WINCH);
			while(b_button());
			freeze(WINCH_MOTOR);
			printf("%4i winch ticks (tightening)\n", get_motor_position_counter(WINCH_MOTOR));	
		}
		if (c_button()) {
			clear_motor_position_counter(WINCH_MOTOR);
			motor(WINCH_MOTOR, -SPEED_FOR_ADJUSTING_WINCH);
			while(c_button());
			freeze(WINCH_MOTOR);
			printf("%4i winch ticks (releasing)\n", get_motor_position_counter(WINCH_MOTOR));	
		}
		if (y_button()) {
			while (y_button()) {
				set_servo_position(GYRO_SERVO, get_servo_position(GYRO_SERVO) - GYRO_SERVO_ADJUSTMENT_AMOUNT);
				msleep(GYRO_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position GYRO tightened to\n", get_servo_position(GYRO_SERVO));
		}
		if (z_button()) {
			while (z_button()) {
				set_servo_position(GYRO_SERVO, get_servo_position(GYRO_SERVO) + GYRO_SERVO_ADJUSTMENT_AMOUNT);
				msleep(GYRO_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position GYRO released to\n", get_servo_position(GYRO_SERVO));
		}
		if (x_button()) {
			while (x_button());
			msleep(500);
			adjust_movement();
			set_buttons_for_winch_and_gyro();
		}
	}
}

int adjust_claw_or_bar() {	
	set_buttons_for_claw_and_bar();
	
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(500);
			return 0;
		}
		if (b_button()) {
			while (b_button()) {
				set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO) - CLAW_SERVO_ADJUSTMENT_AMOUNT);
				msleep(CLAW_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position CLAW closed to\n", get_servo_position(CLAW_SERVO));
		}
		if (c_button()) {
			while (c_button()) {
				set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO) + CLAW_SERVO_ADJUSTMENT_AMOUNT);
				msleep(CLAW_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position CLAW opened to\n", get_servo_position(CLAW_SERVO));	
		}
		if (y_button()) {
			while (y_button()) {
				set_servo_position(BAR_SERVO, get_servo_position(BAR_SERVO) + BAR_SERVO_ADJUSTMENT_AMOUNT);
				msleep(BAR_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position BAR closed to\n", get_servo_position(BAR_SERVO));
		}
		if (z_button()) {
			while (z_button()) {
				set_servo_position(BAR_SERVO, get_servo_position(BAR_SERVO) - BAR_SERVO_ADJUSTMENT_AMOUNT);
				msleep(BAR_SERVO_ADJUSTMENT_MSECONDS);
			}
			printf("%4i = position BAR opened to\n", get_servo_position(BAR_SERVO));
		}
		if (x_button()) {
			while (x_button());
			msleep(500);
			return 1;
		}
	}
}

void set_buttons_for_movement() {
	set_a_button_text("Back to winch/gyro menu");
	set_b_button_text("Go forward until released");
	set_c_button_text("Go backward until released");
	set_x_button_text("Additional choices");
	set_y_button_text("Spin left until released");
	set_z_button_text("Spin right until released");
}

void set_buttons_for_winch_and_gyro() {
	set_a_button_text("Press to exit (and continue run)");
	set_b_button_text("Tighten winch");
	set_c_button_text("Release winch");
	set_x_button_text("Additional choices");
	set_y_button_text("Move gyro up");
	set_z_button_text("Move gyro down");
}

void set_buttons_for_claw_and_bar() {
	set_a_button_text("Back to movement menu");
	set_b_button_text("Close claw");
	set_c_button_text("Open claw");
	set_x_button_text("Back to gyro/winch menu");
	set_y_button_text("Close bar");
	set_z_button_text("Open bar");
}

void set_buttons_to_abc() {
	set_a_button_text("A");
	set_b_button_text("B");
	set_c_button_text("C");
}


#endif
