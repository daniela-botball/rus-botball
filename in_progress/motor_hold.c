// Created on Sat June 8 2013

thread arm_thread;

void _arm_hold();
void arm_hold_position();
void relax_arm();

int main()
{
	//mav(1, 1000);
	//mav(3, 1000);
	//msleep(5000);
	//ao();
	//return;
	arm_hold_position();
	printf("helloworld\n");
	msleep(1000);
	printf("helloworld\n");
	msleep(1000);
	printf("helloworld\n");
	msleep(1000);
	printf("helloworld\n");
	msleep(1000);
	relax_arm();
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
