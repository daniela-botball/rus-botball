// Created on Wed June 12 2013

int main()
{
	clear_motor_position_counter(0);
	motor(0, 30);
	while (get_motor_position_counter(0) < 700);
	off(0);
}
