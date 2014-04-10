// Created on Thu March 13 2014
#ifndef _MAIN_H_
#define _MAIN_H_

#define WINCH_MOTOR 0

#define BAR_SERVO 0
#define CLAW_SERVO 1
#define GYRO_SERVO 3

#define HIGH_SENSOR 2
#define LOW_SENSOR 1
#define BLACK_LINE_SENSOR 0

#define UP 1
#define DOWN -1
#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

#define TOURNAMENT 0
#define PRACTICE 1

#define DOUBLER_POSITION -2050
#define DOUBLER_PICK_UP_POSITION 400

#define WINCH_START_POSITION -1440 //-1550
#define WINCH_DUMPING_POSITION -900 //1425
#define WINCH_RELEASING_POSITION -425
#define WINCH_SCORING_POSITION 25
#define WINCH_TRAVEL_POSITION -2250
#define WINCH_FIRST_CUBE_POSITION 500 // 550
#define WINCH_SECOND_CUBE_POSITION -601

#define GYRO_FIRST_CUBE_POSITION 1940
#define GYRO_SECOND_CUBE_POSITION 1777
#define GYRO_DROP_POSITION 575
#define GYRO_START_POSITION 0
#define CLAW_CLOSED_POSITION 100
#define CLAW_OPEN_POSITION 1550
#define CLAW_START_POSITION 260
#define CLAW_RELEASE_POSITION 165
#define BAR_START_POSITION 420
#define BAR_OPEN_POSITION 100
#define BAR_CLOSED_POSITION 1050

#define SERVO_INCREMENT 15

#define DESIRED_DISTANCE 450
#define DESIRED_X_POSITION 57
#define CENTER_OF_SCREEN_Y 60
#define CUBE_CHANNEL 0
#define THRESHOLD 770
#define CREATE_THRESHOLD 1000
#define CURRENT_THRESHOLD 64680

#define SLEEP_MSECONDS_IN_TOURNAMENT_MODE 100
#define SLOW_CREATE_LINEAR_SPEED 20
#define SLOW_CREATE_ANGULAR_SPEED 20

int _mode = TOURNAMENT;

void adjust();
void adjust_movement();
void set_buttons_for_movement();
int adjust_servos();
void set_buttons_for_movement();
void set_buttons_for_servos();

void create_virtual_bump(int speed, int direction) ;
void move_until_line();
void move_until_line_old();
void move_until_bump(int speed, int direction, int port);
void raise_winch();
void operate_winch(int position);
void press_a_to_continue_old();
void press_a_to_continue();
void pick_up_first_doubler();
void score_cubes();
void move_to_cubes();
void move_to_second_cube();
void pick_up_cube();
void drop_cube();
void get_mode();
void drop_three_hangers();
void center_on_cube(int port, int direction);
void center_on_cube_with_camera();
void move_servo_slowly(int port, int position);

void drop_three_hangers() {
	operate_winch(WINCH_SCORING_POSITION);
	create_drive_distance(4, 40, BACKWARDS); //15
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT); //30
	press_a_to_continue();
	create_drive_distance(42, 40, FORWARDS);// 15
	press_a_to_continue();
	create_spin_degrees(87, 30, LEFT);//30
	press_a_to_continue();
	create_drive_distance(86, 25, FORWARDS);//25
	press_a_to_continue();
	create_spin_degrees(87, 50, RIGHT);
	msleep(500);
	create_drive_distance(5, 30, BACKWARDS);
	press_a_to_continue();
	move_until_line();
	create_drive_distance(15.5, 20, FORWARDS);
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

void score_cubes() {
	move_to_cubes();
	pick_up_cube();
	drop_cube();
	_mode = PRACTICE;
	move_to_second_cube();
	pick_up_cube();
	drop_cube();
}

void move_to_cubes() {
	create_drive_distance(10, 40, BACKWARDS);			
	press_a_to_continue();
	create_spin_degrees(90, 90, RIGHT);				
	press_a_to_continue();
	operate_winch(WINCH_TRAVEL_POSITION);
	msleep(500);
	set_servo_position(BAR_SERVO, BAR_CLOSED_POSITION);
	msleep(200);
	set_servo_position(GYRO_SERVO, GYRO_SECOND_CUBE_POSITION);
	msleep(500);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	msleep(200);
	press_a_to_continue();
	create_drive_distance(5, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, RIGHT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	msleep(200);
	press_a_to_continue();
	create_drive_distance(2, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	msleep(500);
	press_a_to_continue();
	center_on_cube(LOW_SENSOR, FORWARDS);
	create_drive_distance(11, 20, FORWARDS);
}

void pick_up_cube() {
	//_mode = PRACTICE;
	press_a_to_continue();
	move_servo_slowly(GYRO_SERVO, GYRO_FIRST_CUBE_POSITION);
	msleep(500);
	operate_winch(WINCH_FIRST_CUBE_POSITION);
	press_a_to_continue();
	center_on_cube(HIGH_SENSOR, BACKWARDS);
	press_a_to_continue();
	move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
	operate_winch(WINCH_SECOND_CUBE_POSITION);
	move_servo_slowly(GYRO_SERVO, GYRO_SECOND_CUBE_POSITION);
	return;
	_mode = PRACTICE;
	center_on_cube(LOW_SENSOR, BACKWARDS);
	press_a_to_continue();
	move_servo_slowly(CLAW_SERVO, CLAW_OPEN_POSITION);
	press_a_to_continue();
	create_drive_distance(6, 20, FORWARDS);
	press_a_to_continue();
	move_servo_slowly(GYRO_SERVO, GYRO_FIRST_CUBE_POSITION);
	msleep(1000);
	operate_winch(WINCH_FIRST_CUBE_POSITION);
	press_a_to_continue();
	center_on_cube(HIGH_SENSOR, BACKWARDS);
	press_a_to_continue();
	move_servo_slowly(CLAW_SERVO, CLAW_CLOSED_POSITION);
	msleep(500);
	operate_winch(WINCH_SECOND_CUBE_POSITION);
}

void drop_cube() {
	create_virtual_bump(200, BACKWARDS);
	press_a_to_continue();
	create_drive_distance(4, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 40, RIGHT);
	press_a_to_continue();
	create_drive_distance(30, 20, FORWARDS);
	press_a_to_continue();
	operate_winch(WINCH_DUMPING_POSITION);
	press_a_to_continue();
	create_drive_distance(15, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(175, 40, LEFT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	create_drive(100, BACKWARDS);
	msleep(1000);
	create_stop();
	press_a_to_continue();
	create_spin_degrees(15, 40, LEFT);
	move_servo_slowly(GYRO_SERVO, GYRO_DROP_POSITION);
	msleep(200);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
}

void move_to_second_cube() {
	create_drive(200, BACKWARDS);
	msleep(500);
	create_stop();
	create_drive_distance(20, 30, FORWARDS);
	operate_winch(WINCH_TRAVEL_POSITION);
	msleep(500);
	set_servo_position(GYRO_SERVO, GYRO_SECOND_CUBE_POSITION);
	msleep(500);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	create_spin_degrees(180, 50, LEFT);
	press_a_to_continue();
	create_virtual_bump(400, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);
	press_a_to_continue();
	create_virtual_bump(400, BACKWARDS);
	press_a_to_continue();
	center_on_cube(LOW_SENSOR, FORWARDS);
	press_a_to_continue();
	create_drive_distance(11, 20, FORWARDS);
	press_a_to_continue();
}

void operate_winch(int position) {
	int direction;
	if (position == DOUBLER_PICK_UP_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 60);
		while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(DOUBLER_PICK_UP_POSITION));
		freeze(WINCH_MOTOR);
		return;
	} else if (position == WINCH_FIRST_CUBE_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 60);
		while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(WINCH_FIRST_CUBE_POSITION));
		freeze(WINCH_MOTOR);
		return;
	} else if (position == WINCH_SECOND_CUBE_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -60);
		while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(WINCH_SECOND_CUBE_POSITION));
		freeze(WINCH_MOTOR);
		return;
	}
	if (position > 0) {
		direction = 1;
		} else {
		direction = -1;
	}
	raise_winch();
	msleep(200);
	clear_motor_position_counter(WINCH_MOTOR);
	printf("Motor position after clearing: %i\n", get_motor_position_counter(WINCH_MOTOR));
	printf("Given position: %i\n", position);
	motor(WINCH_MOTOR, 60 * direction);
	while(abs(get_motor_position_counter(WINCH_MOTOR)) < abs(position)) {
		printf("%i\n", get_motor_position_counter(WINCH_MOTOR));
	}
	freeze(WINCH_MOTOR);
	printf("Motor position - %i\n", get_motor_position_counter(WINCH_MOTOR));
}

void raise_winch() {
	motor(WINCH_MOTOR, 100);
	while (!digital(15) && !digital(14));
	freeze(WINCH_MOTOR);
}

void press_a_to_continue_old() {
	if (_mode == PRACTICE) {
		printf("Press 'a' to continue\n");
		while (!a_button());
		while (a_button());
		msleep(500);
		} else {
		msleep(100);
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
	create_drive(100, FORWARDS);
	while (get_create_rfcliff_amt() > CREATE_THRESHOLD) {
		display_printf(0, 0, "%4i", get_create_rfcliff_amt());
	}
	create_stop();
}

void move_until_line_old() {
	create_drive(100, FORWARDS);
	while (analog10(BLACK_LINE_SENSOR) < THRESHOLD);
	create_stop();
}

void move_until_bump(int speed, int direction, int port) {
	create_drive(speed, direction);
	while (!digital(port));
	create_stop();
}

void move_servo_slowly(int port, int position) {
	int i;
	if (get_servo_position(port) < position) {
		for (i = get_servo_position(port); i < position; i += SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(20);
		}
		} else if (get_servo_position(port) > position) {
		for (i = get_servo_position(port); i > position; i -= SERVO_INCREMENT) {
			set_servo_position(port, i);
			msleep(20);
		}
	} else {return;}
	msleep(500);
	set_servo_position(port, position);
}

// PRECONDITION: Camera must already be open
void center_on_cube_with_camera() {
	int cube_left_edge = 0;
	int flag = 1;
	create_drive(10, BACKWARDS);
	while (1) {
		camera_update();
		if (get_object_count(CUBE_CHANNEL) > 0) {
			if (get_object_area(CUBE_CHANNEL, 0) > 100) {
				cube_left_edge = get_object_bbox_ulx(CUBE_CHANNEL, 0);
				flag = 1;
				printf("Left edge at %i\n", cube_left_edge);
				if (cube_left_edge > DESIRED_X_POSITION - 3 && cube_left_edge < DESIRED_X_POSITION + 3) {
					create_stop();
					return;
				}
			}
		} else if (flag == 1) {
			printf("no blob in sight\n");
			flag = 0;
		}
	}
}

void center_on_cube(int port, int direction) {
	int actual_distance;
	display_clear();
	create_drive(100, direction);
	while (!a_button()) {
		actual_distance = analog_et(port);
		display_printf(0, 0, "%4i", actual_distance);
		if (actual_distance > DESIRED_DISTANCE) {
			display_printf(0, 1, "Centered");
			break;
		}
	}
	create_stop();
	press_a_to_continue();
	//create_drive_distance(4, 20, direction);
}

void create_virtual_bump(int speed, int direction) {
	create_drive(speed, direction);
	while (create_get_sensor(CURRENT) > CURRENT_THRESHOLD) {
		//msleep(20);
	}
	create_stop();
}

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
	adjust_movement();
	extra_buttons_hide();
}

void adjust_movement() {
	int is_exit_time;
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
			printf("%4i (spin left - CCW)\n",
			    get_create_total_angle());
		}
		if (z_button()) {
			set_create_total_angle(0);
			create_spin_CW(SLOW_CREATE_ANGULAR_SPEED);
			while (z_button());
			create_stop();
			printf("%4i (spin right - CW)\n",
			    get_create_total_angle());
		}
		if (x_button()) {
			while (x_button());
			is_exit_time = adjust_servos();
			if (is_exit_time) return;
			set_buttons_for_servos();
		}
	}
}

int adjust_servos() {
	int is_exit_time;
	
	set_buttons_for_movement();
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(500);
			return 1;
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
			printf("%4i (spin left - CCW)\n",
			    get_create_total_angle());
		}
		if (z_button()) {
			set_create_total_angle(0);
			create_spin_CW(SLOW_CREATE_ANGULAR_SPEED);
			while (z_button());
			create_stop();
			printf("%4i (spin right - CW)\n",
			    get_create_total_angle());
		}
		if (x_button()) {
			while (x_button());
			is_exit_time = adjust_servos();
			if (is_exit_time) return 1;
			set_buttons_for_servos();
		}
	}
}

void set_buttons_for_movement() {
	set_a_button_text("Press to exit (and continue run)");
	set_b_button_text("Go forward until released");
	set_c_button_text("Go backward until released");
	set_x_button_text("Switch to motor/servo menu");
	set_y_button_text("Spin left until released");
	set_z_button_text("Spin right until released");
}

void set_buttons_for_servos() {
	set_a_button_text("Press to exit (and continue run)");
	set_b_button_text("Go forward until released");
	set_c_button_text("Go backward until released");
	set_x_button_text("Switch back to movement menu");
	set_y_button_text("Spin left until released");
	set_z_button_text("Spin right until released");
}

#endif

