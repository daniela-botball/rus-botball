#ifndef _RUS_SERVOS_H_
#define _RUS_SERVOS_H_

#include "universal_library.h"
#include "create_library.h"

#define GATE_SERVO 0
#define CLAW_SERVO 1
#define JOINT_SERVO 2
#define ARM_SERVO 3
#define BOOSTER_PORT 1

#define GATE_SERVO_OPEN_POSITION 925
#define GATE_SERVO_CLOSED_POSITION 0
#define CLAW_SERVO_OPEN_POSITION 1012
#define CLAW_SERVO_CLOSE_POSITION 1900
#define CLAW_SERVO_HALF_CLOSED_POSITION 1650
#define JOINT_SERVO_IN_POSITION 117
#define JOINT_SERVO_OUT_POSITION 1838
#define JOINT_SERVO_DOWN_POSITION 1203 //1477
#define JOINT_SERVO_START_POSITION 1900
#define ARM_SERVO_UP_POSITION 1900 //1765, then 1639
#define ARM_SERVO_DOWN_POSITION 0
#define ARM_SERVO_START_POSITION 761
#define ARM_SERVO_DROP_POSITION 1480

#define DISABLED 0
#define ENABLED 1

#define GRABBING_PAUSE_TIME 150

int _SERVO_STATE = DISABLED;

void open_claw(int sleeptime);
void close_claw(int sleeptime);
void half_close_claw(int sleeptime);
void fold_joint_in();
void fold_joint_down();
void fold_joint_out();
void start_joint();
void raise_arm();
void lower_arm();
void arm_start();
void start_servos();
void press_a_to_continue(int off_or_on);
void relax_servos();
void grab_booster(int sleeptime);
void unrelax_servos();
void lift_booster(int sleeptime);
void motor_push_down();
void fold_in_joint();
void close_gate();
void start_gate();
void drop_booster(int sleeptime);
void arm_to_drop();

void open_claw(int sleeptime)
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
		msleep(sleeptime);
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
	}
}

void close_claw(int sleeptime)
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
		msleep(sleeptime);
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	}
}

void fold_joint_in()
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

void fold_joint_out()
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

void fold_joint_for_pickup()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_DOWN_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(JOINT_SERVO, JOINT_SERVO_DOWN_POSITION);
	}
}


void raise_arm()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
	}
}

void lower_arm()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_DOWN_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_DOWN_POSITION);
	}
}

void arm_start()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
	}
}

void start_joint()
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

void start_gate()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(GATE_SERVO, GATE_SERVO_OPEN_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(GATE_SERVO, GATE_SERVO_OPEN_POSITION);
	}
}

void start_servos()
{
	close_claw();
	start_joint();
	arm_start();
	start_gate();
	unrelax_servos();
	sleep(1);
}

void relax_servos()
{
	fold_in_joint();
	disable_servos();
	_SERVO_STATE = DISABLED;
}

void unrelax_servos()
{
	set_servo_position(JOINT_SERVO, get_servo_position(JOINT_SERVO));
	set_servo_position(ARM_SERVO, get_servo_position(ARM_SERVO));
	set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO));
	set_servo_position(GATE_SERVO, get_servo_position(GATE_SERVO));
	enable_servos();
	_SERVO_STATE = ENABLED;
}

void grab_booster(int sleeptime)
{
	//function assumes all servos begin in the relax position
	lower_arm();
	msleep(sleeptime);
	//motor_push_down();
	//msleep(sleeptime);
	open_claw();
	fold_joint_down();
	msleep(sleeptime);
	half_close_claw();
	msleep(sleeptime);
	create_drive_distance(1, 5, BACKWARDS);
	msleep(sleeptime);
	close_claw();
}

void lift_booster(int sleeptime)
{
	fold_joint_in();
	msleep(sleeptime);
	raise_arm();
	msleep(sleeptime);
	close_gate();
}

void press_a_to_continue(int off_or_on)
{
	if (off_or_on == 1)
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
	else
	{
		return;
	}
}


void motor_push_down()
{
	relax_servos();
	motor(BOOSTER_PORT, 50);
	msleep(200);
	off(BOOSTER_PORT);
	//sleep(1);
	unrelax_servos();
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

void close_gate()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(GATE_SERVO, GATE_SERVO_CLOSED_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(GATE_SERVO, GATE_SERVO_CLOSED_POSITION);
	}
}

void half_close_claw(int sleeptime)
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
		msleep(sleeptime);
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
	}
}

void drop_booster(int sleep_time, int drop_or_lower)
{
	if (drop_or_lower == 0)
	{
		msleep(sleep_time);
		fold_joint_out();
		msleep(sleep_time);
		sleep(1);
		open_claw();
	}
	else
	{
		msleep(sleep_time);
		create_drive_distance(1, 5, FORWARDS);
		msleep(sleep_time);
		fold_joint_out();
		msleep(sleep_time);
		start_gate();
		msleep(sleep_time);
		arm_to_drop();
		msleep(sleep_time);
		open_claw();
	}
}

void arm_to_drop()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_DROP_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(ARM_SERVO, ARM_SERVO_DROP_POSITION);
	}
}

#endif
