// Created on Wed June 12 2013

void turn();
void forwards();

int main()
{
	set_a_button_text("turn");
	set_b_button_text("forwards");
	while (1)
	{
		if (a_button())
		{
			while(a_button());
			msleep(50);
			turn();
		}
		if (b_button())
		{
			while(b_button());
			msleep(50);
			forwards();
		}
	}
	return 0;
}

void forwards()
{
	clear_motor_position_counter(0);
	motor(0, 100);
	motor(1, 100);
	while (get_motor_position_counter(0) < 3000);
	off(0);
	off(1);
}

void turn()
{
	clear_motor_position_counter(0);
	motor(0, 100);
	motor(1, -100);
	while (get_motor_position_counter(0) < 1000);
	off(0);
	off(1);
}
