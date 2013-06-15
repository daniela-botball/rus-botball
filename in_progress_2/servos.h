#ifndef _SERVOS_H_
#define _SERVOS_H_

#include "universal_library.h"

#define CLAW_SERVO 1
#define JOINT_SERVO 2
#define ARM_SERVO 3

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
	begin_servos();
	press_a_to_continue();
	sleep(1);
	relax_servos();
	sleep(1);
	press_a_to_continue();
	unrelax_servos();
	sleep(1);
	press_a_to_continue();
	grab_booster();
	sleep(1);
	press_a_to_continue();
	lift_booster();
	press_a_to_continue();
	
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
	close_claw();
	joint_start();
	arm_start();
	sleep(1);
}

void relax_servos()
{
	fold_in_joint();
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
	lower_arm();
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

#endif
