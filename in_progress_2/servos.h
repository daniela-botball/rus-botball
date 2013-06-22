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

typedef enum {DROP_BOOSTER, LOWER_BOOSTER} Drop_or_lower_booster;


void open_claw(int sleeptime);
void close_claw(int sleeptime);
void half_close_claw(int sleeptime);
void fold_joint_for_lift(int sleeptime);
void fold_joint_for_pickup(int sleeptime);
void fold_joint_for_drop(int sleeptime);
void raise_arm(int sleeptime);
void lower_arm(int sleeptime);
void move_arm_to_drop_position(int sleeptime);
void close_gate(int sleeptime);
void open_gate(int sleeptime);
void motor_push_down(int sleeptime);



void start_claw();
void start_arm();
void start_joint();
void start_gate();
void start_servos();

void press_a_to_continue(int off_or_on);
void relax_servos();
void unrelax_servos();
void grab_booster(int distance);
void lift_booster();
void drop_booster(Drop_or_lower_booster drop_or_lower);


void open_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
	msleep(sleeptime);
}


void close_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_lift(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_drop(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_OUT_POSITION);
	msleep(sleeptime);
}

void fold_joint_for_pickup(int sleeptime)
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_DOWN_POSITION);
	msleep(sleeptime);
}

void raise_arm(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
	msleep(sleeptime);
}

void move_arm_to_drop_position(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_DROP_POSITION);
	msleep(sleeptime);
}

void lower_arm(int sleeptime)
{
	set_servo_position(ARM_SERVO, ARM_SERVO_DOWN_POSITION);
	msleep(sleeptime);
}

void close_gate(int sleeptime)
{
	set_servo_position(GATE_SERVO, GATE_SERVO_CLOSED_POSITION);
	msleep(sleeptime);
}

void open_gate(int sleeptime)
{
	set_servo_position(GATE_SERVO, GATE_SERVO_OPEN_POSITION);
	msleep(sleeptime);
}

void half_close_claw(int sleeptime)
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_HALF_CLOSED_POSITION);
	msleep(sleeptime);
}

void motor_push_down(int sleeptime)
{
	relax_servos();
	motor(BOOSTER_PORT, 50);
	msleep(sleeptime);
	off(BOOSTER_PORT);
	unrelax_servos();
}

void start_claw()
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
}

void start_arm()
{
	set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
}

void start_joint()
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
}

void start_gate()
{
	set_servo_position(GATE_SERVO, GATE_SERVO_OPEN_POSITION);
}

void start_servos()
{
	start_claw();
	start_joint();
	start_arm();
	start_gate();
	unrelax_servos();
	msleep(1000);
}

void relax_servos()
{
	fold_joint_for_lift(600);
	disable_servos();
}

void unrelax_servos()
{
	set_servo_position(JOINT_SERVO, get_servo_position(JOINT_SERVO));
	set_servo_position(ARM_SERVO, get_servo_position(ARM_SERVO));
	set_servo_position(CLAW_SERVO, get_servo_position(CLAW_SERVO));
	set_servo_position(GATE_SERVO, get_servo_position(GATE_SERVO));
	enable_servos();
}

void grab_booster(int distance)
{
	//function assumes all servos begin in the relax position
	lower_arm(200);
	//motor_push_down();
	open_claw(200);
	fold_joint_for_pickup(200);
	half_close_claw(200);
	press_A_to_continue();
	create_drive_distance(distance, 5, BACKWARDS);
	close_claw(1000);
	press_A_to_continue();
	create_drive_distance(2, 5, FORWARDS);
}

void lift_booster()
{
	fold_joint_for_lift(1500);
	press_A_to_continue();
	raise_arm(2000);
	close_gate(200);
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


void drop_booster(Drop_or_lower_booster drop_or_lower)
{
	if (drop_or_lower == DROP_BOOSTER)
	{
		fold_joint_for_drop(3000);
		open_claw(200);
	}
	else
	{
		//create_drive_distance(1, 5, FORWARDS);
		//fold_joint_for_drop(2000);
		//start_gate();
		//move_arm_to_drop_position(200);
		//open_claw(200);
		// Should probably go away.
	}
}

#endif
