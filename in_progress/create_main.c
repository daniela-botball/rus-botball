// Created on Sat June 8 2013
#include "universal_library.h"
#include "create_library.h"
#include "servos.h"

thread arm_thread;

void _arm_hold();
void arm_hold_position();
void relax_arm();

#define CLAW_SERVO 1
#define JOINT_SERVO 2
#define ARM_MOTOR_L 3
#define ARM_MOTOR_R 1

#define CLAW_SERVO_OPEN_POSITION 1012
#define CLAW_SERVO_CLOSE_POSITION 1900
#define JOINT_SERVO_IN_POSITION 117
#define JOINT_SERVO_OUT_POSITION 1477
#define JOINT_SERVO_START_POSITION 1900
#define ARM_SERVO_UP_POSITION 1500 //1765
#define ARM_SERVO_DOWN_POSITION 100
#define ARM_SERVO_START_POSITION 600

#define DISABLED 0
#define ENABLED 1

int _SERVO_STATE = DISABLED;

void open_claw();
void close_claw();
void joint_fold_in();
void joint_fold_out();
void joint_start();
void rasie_arm();
void lower_arm();
void arm_start();
void arm_travel();
void start_servos();
void press_a_to_continue();
void relax_servos();
void grab_booster();
void unrelax_servos();
void lift_booster();

void begin_servos();
void end_servos();

int main()
{
	start_servos();
	press_a_to_continue();
	thread_destroy(arm_thread);
	travel_servos();
	press_a_to_continue();
	grab_booster();
	press_a_to_continue();
	lift_booster();
	press_a_to_continue();
	return 0;
	
	/*
	create_connect();
	start_servos();
	press_a_to_continue();
	enable_servos();
	fold_in_joint();
	press_a_to_continue();
	relax_servos();
	press_a_to_continue();
	create_drive_distance(46, 20, BACKWARDS);
	create_spin_degrees(86, 20, RIGHT);
	create_drive_distance(22, 20, BACKWARDS);
	unrelax_servos();
	press_a_to_continue();
	grab_booster();
	press_a_to_continue();
	lift_booster();
	press_a_to_continue();
	create_spin_degrees(90, 20, LEFT);*/
}

void open_claw()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
	}
}

void close_claw()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	}
}

void fold_in_joint()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	}
}

void fold_out_joint()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_OUT_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_OUT_POSITION);
	}
}

void raise_arm()
{
	clear_motor_position_counter(ARM_MOTOR_L);
	mav(ARM_MOTOR_L, 300);
	mav(ARM_MOTOR_R, 300);
	while(get_motor_position_counter(ARM_MOTOR_L) < 412.5);
	off(ARM_MOTOR_L);
	off(ARM_MOTOR_R);
}

void lower_arm()
{
	clear_motor_position_counter(ARM_MOTOR_L);
	mav(ARM_MOTOR_L, -300);
	mav(ARM_MOTOR_R, -300);
	while(get_motor_position_counter(ARM_MOTOR_L) > -420);
	off(ARM_MOTOR_R);
	off(ARM_MOTOR_L);
}

void arm_start()
{
	arm_hold_position();
}

void arm_travel()
{
	lower_arm();
	off(ARM_MOTOR_L);
	off(ARM_MOTOR_R);
}

void joint_start()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
	}
}

void start_servos()
{
	open_claw();
	joint_start();
	arm_start();
	sleep(1);
}

void travel_servos()
{
	fold_in_joint();
	open_claw();
	arm_travel();
	end_servos(); 
}

void unrelax_servos()
{
	fold_in_joint();
	arm_start();
	open_claw();
	begin_servos();
}

void grab_booster()
{
	//function assumes all servos begin in the relax position
	//lower_arm();
	open_claw();
	fold_out_joint();
	close_claw();
}

void lift_booster()
{
	fold_in_joint();
	sleep(2); // have each function have parameter - msleep amount
	//press_a_to_continue();
	raise_arm();
	sleep(3);
}

void press_a_to_continue()
{
	while (1)
	{
		if (a_button() == 1)
		{
			printf("hands off\n");
			while (a_button() == 1);
			sleep(.5);
			return;
		}
	}
}

void begin_servos()
{
	enable_servos();
	_SERVO_STATE = ENABLED;
}

void end_servos()
{
	disable_servos();
	_SERVO_STATE = DISABLED;
}

void arm_hold_position()
{
	arm_thread = thread_create(_arm_hold);
	thread_start(arm_thread);
}

void _arm_hold()
{
	clear_motor_position_counter(1);
	clear_motor_position_counter(3);
	while (1)
	{
		mav(1, 100);
		mav(3, 100);
		msleep(1);
		mav(1, -100);
		mav(3, -100);
		msleep(1);
	}
}

void relax_arm()
{
	thread_destroy(arm_thread);
}
