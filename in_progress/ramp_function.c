// Created on Sat June 8 2013

int main()
{
	printf("Hello, World!\n");
	return 0;
}

float ramp(float distance, int speed, int direction)
{
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	
	int c_speed;
	
	c_speed = 2;

	if ((speed - c_speed)/2 < speed)
	{
		BAD THINGS HAPPEN;
	}
	
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < distance)
	{
		mav(LEFT_MOTOR, c_speed * direction);
		mav(RIGHT_MOTOR, c_speed * direction);
		if (c_speed >= speed)
		{
			c_speed = speed;
		}
		else
		{
			c_speed *= c_speed;
		}
	}
}
