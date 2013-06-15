

#include "universal_library.h"

#define CLAW_SERVO 1
#define JOINT_SERVO 2
#define ARM_SERVO 3
#define BOOSTER_PORT 1

#define CLAW_SERVO_OPEN_POSITION 1012
#define CLAW_SERVO_CLOSE_POSITION 1900
#define JOINT_SERVO_IN_POSITION 117
#define JOINT_SERVO_OUT_POSITION 1838
#define JOINT_SERVO_DOWN_POSITION 1203 //1477
#define JOINT_SERVO_START_POSITION 1900
#define ARM_SERVO_UP_POSITION 1639 //1765
#define ARM_SERVO_DOWN_POSITION 0
#define ARM_SERVO_START_POSITION 761

#define DISABLED 0
#define ENABLED 1

int _SERVO_STATE = DISABLED;

void open_claw();
void close_claw();
void fold_joint_in();
void fold_joint_down();
void fold_joint_out();
void start_joint();
void rasie_arm();
void lower_arm();
void arm_start();
void start_servos();
void press_a_to_continue();
void relax_servos();
void grab_booster();
void unrelax_servos();
void lift_booster();
void motor_push_down();

int main()
{
	//motor_push_down();
	//press_a_to_continue();
	//return;
	start_servos();
	press_a_to_continue();
	sleep(1);
	fold_joint_in();
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
	fold_joint_out();
	press_a_to_continue();
	sleep(7);
	open_claw();
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

void start_servos()
{
	close_claw();
	start_joint();
	arm_start();
	unrelax_servos();
	sleep(1);
}

void relax_servos()
{
	disable_servos();
	_SERVO_STATE = DISABLED;
}

void unrelax_servos()
{
	set_servo_position(JOINT_SERVO, get_servo_position(JOINT_SERVO));
	set_servo_position(ARM_SERVO, get_servo_position(ARM_SERVO));
	set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO));
	enable_servos();
	_SERVO_STATE = ENABLED;
}

void grab_booster()
{
	//function assumes all servos begin in the relax position
	lower_arm();
	press_a_to_continue();
	motor_push_down();
	press_a_to_continue();
	open_claw();
	press_a_to_continue();
	fold_joint_down();
	press_a_to_continue();
	close_claw();
}

void lift_booster()
{
	fold_joint_in();
	sleep(2); // have each function have parameter - msleep amount
	//press_a_to_continue();
	raise_arm();
	sleep(3);
}

void press_a_to_continue()
{
	sleep(1);
	return;
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

void motor_push_down()
{
	relax_servos();
	motor(BOOSTER_PORT, 50);
	sleep(.2);
	off(BOOSTER_PORT);
	sleep(1);
	unrelax_servos();
}
