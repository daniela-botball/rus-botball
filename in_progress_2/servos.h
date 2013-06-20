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

#define DISABLED 0
#define ENABLED 1

#define GRABBING_PAUSE_TIME 150

int _SERVO_STATE = DISABLED;

void open_claw();
void close_claw();
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
void grab_booster();
void unrelax_servos();
void lift_booster();
void motor_push_down();
void fold_in_joint();
void close_gate();
void start_gate();
void half_close_claw();

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

void fold_joint_down()
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

void gate_start()
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
	gate_start();
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

void grab_booster()
{
	//function assumes all servos begin in the relax position
	lower_arm();
	msleep(GRABBING_PAUSE_TIME);
	motor_push_down();
	msleep(GRABBING_PAUSE_TIME);
	open_claw();
	msleep(GRABBING_PAUSE_TIME);
	fold_joint_down();
	msleep(GRABBING_PAUSE_TIME);
	half_close_claw();
	msleep(GRABBING_PAUSE_TIME);
	create_drive_distance(1, 2, BACKWARDS);
	msleep(GRABBING_PAUSE_TIME);
	close_claw();
}

void lift_booster()
{
	fold_joint_in();
	sleep(2); // have each function have parameter - msleep amount
	//press_a_to_continue();
	raise_arm();
	sleep(2);
	close_gate();
	sleep(2);
	fold_joint_out();
	sleep(1);
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
	sleep(.2);
	off(BOOSTER_PORT);
	sleep(1);
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

void half_close_claw()
{
	if (_SERVO_STATE == ENABLED)
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
		sleep(1); // fix time
	}
	else
	{
		set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
	}
}


#endif
