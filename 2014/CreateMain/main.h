// Created on Thu March 13 2014
#ifndef _MAIN_H_
#define _MAIN_H_

#define WINCH_MOTOR 0

#define BAR_SERVO 0
#define CLAW_SERVO 1
#define GYRO_SERVO 3

#define HIGH_SENSOR 1
#define LOW_SENSOR 0

#define BLACK_LINE_SENSOR 0 //UNUSED

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
#define WINCH_DUMPING_POSITION -1295 // DCM was -1050
#define WINCH_RELEASING_POSITION -434 // -425
#define WINCH_SCORING_POSITION -115 // DCM was 25
#define WINCH_TRAVEL_POSITION -2250
#define WINCH_FIRST_CUBE_POSITION 527 // DCM was 500
#define WINCH_SECOND_CUBE_POSITION -600 //DCM was -570

// DONE: 68 less, 10 degrees less, 9 more foearward, 3 degrees more
// DONE: small amount less forward off wall, 27 higher when going for cube
// DONE: claw start at 130.  eliminate backward.  15 degrees less after backup
// DONE:  still less out from wall, spin less, little farther after seeing cube
// DONE: press_a_to_continue in dropping
// DONE: adjust drop numbers, turn a bit more
// press_a_to_continue has to repeat message.
// message saying that create not connected
// checklists
// fix all wires

#define GYRO_FIRST_CUBE_POSITION 1940
#define GYRO_SECOND_CUBE_POSITION 1777
#define GYRO_DROP_POSITION 245 // DCM was 325
#define GYRO_START_POSITION 0
#define CLAW_CLOSED_POSITION 100
#define CLAW_OPEN_POSITION 1550
#define CLAW_START_POSITION 130 // was 260
#define CLAW_RELEASE_POSITION 1000
#define BAR_START_POSITION 620 // DCM was 420
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
#define SLOW_CREATE_LINEAR_SPEED 30
#define SLOW_CREATE_ANGULAR_SPEED 20
#define SPEED_FOR_TIGHTENING_WINCH 75
#define SPEED_FOR_RELEASING_WINCH 20
#define GYRO_SERVO_ADJUSTMENT_AMOUNT 10
#define GYRO_SERVO_ADJUSTMENT_MSECONDS 200
#define CLAW_SERVO_ADJUSTMENT_AMOUNT 10
#define CLAW_SERVO_ADJUSTMENT_MSECONDS 200
#define BAR_SERVO_ADJUSTMENT_AMOUNT 10
#define BAR_SERVO_ADJUSTMENT_MSECONDS 200

#define NUMBER_ERRORS_ALLOWED 3 // DCM
#define AMOUNT_ERROR_ALLOWED 100 // DCM

int _mode = TOURNAMENT;

void adjust();
void adjust_winch_or_gyro();
void adjust_movement();
int adjust_claw_or_bar();
void set_buttons_for_winch_and_gyro();
void set_buttons_for_movement();
void set_buttons_for_claw_and_bar();
void set_buttons_to_abc();

int int_abs(int x);

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
	// create_drive_distance(4, 40, BACKWARDS); //15  DCM removed this
	//press_a_to_continue();
	create_spin_degrees(90, 40, RIGHT); //30
	press_a_to_continue();
	create_drive_distance(42, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(87, 30, LEFT);//30
	press_a_to_continue();
	create_drive_distance(75, 25, FORWARDS);//DCM was 86
	press_a_to_continue();
	create_spin_degrees(77, 40, RIGHT); // DCM was 87
	msleep(500);
	create_drive_distance(5, 30, BACKWARDS);
	press_a_to_continue();
	move_until_line();
	create_drive_distance(16.5, 20, FORWARDS); // DCM was 1.5.
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
	create_spin_degrees(90, 40, LEFT);
	press_a_to_continue();
	create_drive_distance(26, 40, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 40, RIGHT);
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
	move_to_second_cube();
	pick_up_cube();
	drop_cube();
}

void move_to_cubes() {
	create_drive_distance(10, 20, BACKWARDS); 		
	press_a_to_continue();
	create_spin_degrees(95, 40, RIGHT);	// DCM was 90		
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
	create_drive_distance(2, 20, FORWARDS); // DCM was 5
	press_a_to_continue();
	create_spin_degrees(84, 40, RIGHT); // DCM was 90
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	msleep(200);
	press_a_to_continue();
	//create_drive_distance(2, 20, FORWARDS);
	//press_a_to_continue();
	create_spin_degrees(90, 40, LEFT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	msleep(500);
	press_a_to_continue();
	center_on_cube(LOW_SENSOR, FORWARDS);
	create_drive_distance(11, 40, FORWARDS); // DCM was 10
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
	
	// REST OF THIS FUNCTION IS HISTORY.
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
	create_drive(500, BACKWARDS);
	msleep(700);
	create_stop();
	press_a_to_continue();
	create_spin_degrees(15, 40, LEFT); // DCM was 20
	press_a_to_continue();
	move_servo_slowly(GYRO_SERVO, GYRO_DROP_POSITION);
	msleep(200);
	press_a_to_continue();
	set_servo_position(CLAW_SERVO, CLAW_RELEASE_POSITION);
	press_a_to_continue();
}

void move_to_second_cube() {
	create_drive(500, BACKWARDS);  // DCM FIX ME
	msleep(500);
	create_stop();
	create_drive_distance(25, 50, FORWARDS);  // DCM was 20
	operate_winch(WINCH_TRAVEL_POSITION);
	msleep(500);
	set_servo_position(GYRO_SERVO, GYRO_SECOND_CUBE_POSITION);
	msleep(500);
	set_servo_position(CLAW_SERVO, CLAW_OPEN_POSITION);
	create_spin_degrees(185, 50, RIGHT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 50, LEFT);
	press_a_to_continue();
	create_virtual_bump(200, BACKWARDS);
	press_a_to_continue();
	center_on_cube(LOW_SENSOR, FORWARDS);
	press_a_to_continue();
	create_drive_distance(11, 35, FORWARDS);
	press_a_to_continue();
}

void operate_winch(int position) {
	int direction;
	int k;
	
	if (position == DOUBLER_PICK_UP_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 60);
		while(int_abs(get_motor_position_counter(WINCH_MOTOR)) < int_abs(DOUBLER_PICK_UP_POSITION));
		freeze(WINCH_MOTOR);
		return;
	} else if (position == WINCH_FIRST_CUBE_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, 60);
		while(int_abs(get_motor_position_counter(WINCH_MOTOR)) < int_abs(WINCH_FIRST_CUBE_POSITION));
		freeze(WINCH_MOTOR);
		return;
	} else if (position == WINCH_SECOND_CUBE_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -60);
		while(int_abs(get_motor_position_counter(WINCH_MOTOR)) < int_abs(WINCH_SECOND_CUBE_POSITION));
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
	printf("Given position: %i, start wind\n", position);
	for (k = 0; k < NUMBER_ERRORS_ALLOWED; ++k) {
		motor(WINCH_MOTOR, 60 * direction);
		while(int_abs(get_motor_position_counter(WINCH_MOTOR)) < int_abs(position)) {
			printf("%i\n", get_motor_position_counter(WINCH_MOTOR));
		}
		freeze(WINCH_MOTOR);
		printf("Motor position is %i, wants %i\n",
		       get_motor_position_counter(WINCH_MOTOR), position);
		if (int_abs(get_motor_position_counter(WINCH_MOTOR)) < int_abs(position) + AMOUNT_ERROR_ALLOWED) {
			break;
		}
		sleep(2000); // WINCH DID NOT GO CORRECTLY, SLEEP SO CAN SEE IT.
		printf("ERROR - WINCH FAILED\n");
	}
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
	adjust_winch_or_gyro();
	extra_buttons_hide();
	set_buttons_to_abc();
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
			motor(WINCH_MOTOR, SPEED_FOR_TIGHTENING_WINCH);
			while(b_button());
			freeze(WINCH_MOTOR);
			printf("%4i winch ticks (tightening)\n", get_motor_position_counter(WINCH_MOTOR));	
		}
		if (c_button()) {
			clear_motor_position_counter(WINCH_MOTOR);
			motor(WINCH_MOTOR, -SPEED_FOR_RELEASING_WINCH);
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

void set_buttons_for_winch_and_gyro() {
	set_a_button_text("Exit, continue run");
	set_b_button_text("Tighten winch");
	set_c_button_text("Release winch");
	set_x_button_text("More choices");
	set_y_button_text("Gyro up");
	set_z_button_text("Gyro down");
}

void set_buttons_for_movement() {
	set_a_button_text("Winch/gyro menu");
	set_b_button_text("Go forward");
	set_c_button_text("Go backward");
	set_x_button_text("Claw/bar menu");
	set_y_button_text("Spin left");
	set_z_button_text("Spin right");
}

void set_buttons_for_claw_and_bar() {
	set_a_button_text("Movement menu");
	set_b_button_text("Close claw");
	set_c_button_text("Open claw");
	set_x_button_text("Winch/gyro menu");
	set_y_button_text("Close bar");
	set_z_button_text("Open bar");
}

void set_buttons_to_abc() {
	set_a_button_text("A");
	set_b_button_text("B");
	set_c_button_text("C");
}

int int_abs(int x) {
	if (x < 0) x = -x;
	return x;
}

#endif

