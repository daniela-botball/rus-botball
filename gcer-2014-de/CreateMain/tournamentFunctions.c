#include "tournamentFunctions.h"
#include "createMovement.h"
#include "movement.h"
#include "ui.h"

thread hold_thread;

void freeze_motor() {
	while (1) {
		if (!digital(15)) {
			motor(WINCH_MOTOR, 70);
		}
	}
}
void lock_winch_new() {
	hold_thread = thread_create(freeze_motor);
	thread_start(hold_thread);
}

void unlock_winch_new() {
	freeze(WINCH_MOTOR);
	thread_destroy(hold_thread);
}

void drop_three_hangers_on_third_rack() {
	drive_to_hanger_racks();
	drop_hangers();
	//get_first_doubler();
}

void drive_to_hanger_racks() {
	extend_arm();
	msleep(1000);
	raise_winch();
	lock_winch_new();
	create_spin_degrees(90, 20, RIGHT);
	press_a_to_continue();
	create_drive_distance(40, 10, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(87, 20, LEFT);
	press_a_to_continue();
	create_drive_distance(85, 10, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 20, LEFT);
	msleep(500);
	create_drive_distance(10, 10, FORWARDS);
	create_spin_degrees(180, 20, LEFT);
	move_until_line();
}

void drop_hangers() {
	create_drive_distance(14, 10, FORWARDS);
	unlock_winch_new();
	operate_winch(WINCH_DROP_DISTANCE);
	//msleep(8000);
	create_drive_distance(3, 10, BACKWARDS);
	press_a_to_continue();
	create_spin_degrees(10, 20, RIGHT);
	press_a_to_continue();
	create_drive_distance(20, 20, BACKWARDS);
	press_a_to_continue();
	press_a_to_continue();
}

void get_first_doubler() {
	create_drive_distance(10, 20, BACKWARDS);
	create_spin_degrees(10, 20, LEFT);
	create_virtual_bump(150, BACKWARDS);
	create_drive_distance(3, 20, FORWARDS);
	create_spin_degrees(90, 20, LEFT);
	create_virtual_bump(150, BACKWARDS);
	create_drive_distance(6, 20, FORWARDS);
	press_a_to_continue();
	create_spin_degrees(90, 20, RIGHT);
	create_virtual_bump(150, BACKWARDS);
	unlock_winch();
	operate_winch(DOUBLER_PICK_UP_POSITION);
	press_a_to_continue();
	create_drive_distance(20, 20, FORWARDS);	
}

void lock_winch() {
	set_servo_position(LOCK_SERVO, LOCKED_POSITION);
}
void unlock_winch() {
	set_servo_position(LOCK_SERVO, UNLOCKED_POSITION);
}

void extend_arm() {
	clear_motor_position_counter(EXTENDER_MOTOR);
	motor(EXTENDER_MOTOR, 100);
	while (get_motor_position_counter(EXTENDER_MOTOR) < EXTENSION_DISTANCE);
	freeze(EXTENDER_MOTOR);
}

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
	//set_mode(PRACTICE);
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
	set_mode(PRACTICE);
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
	create_spin_degrees(20, 40, LEFT);
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
	if (position == WINCH_DROP_DISTANCE) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -60);
		while (get_motor_position_counter(WINCH_MOTOR) > -WINCH_DROP_DISTANCE);
		freeze(WINCH_MOTOR);
		return;
	}
	if (position == DOUBLER_PICK_UP_POSITION) {
		clear_motor_position_counter(WINCH_MOTOR);
		motor(WINCH_MOTOR, -60);
		while (!digital(12));
		freeze(WINCH_MOTOR);
		return;
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

void raise_winch_old() {
	motor(WINCH_MOTOR, 100);
	while (!digital(15));// && !digital(14));
	freeze(WINCH_MOTOR);
}

void raise_winch() {
	motor(WINCH_MOTOR, 100);
	while (!digital(15));
	freeze(WINCH_MOTOR);
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
