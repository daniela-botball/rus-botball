// Created on Tue June 4 2013

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

int main()
{
	start_servos();
	enable_servos();
	//press_a_to_continue();
	msleep(1000);
	relax_servos();
	msleep(1000);
	//press_a_to_continue();
	unrelax_servos();
	msleep(1000);
	//press_a_to_continue();
	grab_booster();
	msleep(1000);
	//press_a_to_continue();
	lift_booster();
	press_a_to_continue();
	
}

void open_claw()
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_OPEN_POSITION);
	msleep(1000); // fix time

}

void close_claw()
{
	set_servo_position(CLAW_SERVO, CLAW_SERVO_CLOSE_POSITION);
	msleep(1000); // fix time

}

void fold_in_joint()
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_IN_POSITION);
	msleep(1000); // fix time
}

void fold_out_joint()
{
	set_servo_position(JOINT_SERVO, JOINT_SERVO_OUT_POSITION);
	msleep(1000); //fix time
}

void raise_arm()
{
	set_servo_position(ARM_SERVO, ARM_SERVO_UP_POSITION);
	msleep(1000); // fix time
}

void lower_arm()
{
	set_servo_position(ARM_SERVO, ARM_SERVO_DOWN_POSITION);
	msleep(1000); // fix time
}

void arm_start()
{
	set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
	msleep(1000); // fix time
}

void joint_start()
{
	// don't sleep if servo is not enabled *
	set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
	msleep(1000); // fix time
}

void start_servos()
{
	close_claw();
	joint_start();
	arm_start();
	msleep(1000);
}

void relax_servos()
{
	//investigate disabling single servo
	fold_in_joint();
	//should other servos move as well?
	disable_servos();
	//start servos should 
}

void unrelax_servos()
{
	fold_in_joint();
	arm_start();
	open_claw();
	enable_servos();
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
	msleep(2000); // have each function have parameter - msleep amount
	//press_a_to_continue();
	raise_arm();
	msleep(3000);
}

void press_a_to_continue()
{
	while (1)
	{
		if (a_button() == 1)
		{
			printf("hands off\n");
			while (a_button() == 1);
			msleep(500);
			return;
		}
	}
}
