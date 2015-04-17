// Created on Tue April 14 2015

int main()
{
	printf("Hello, World!\n");
	
	set_servo_position(1, 0);
	enable_servos();
	msleep(2000);
	
	motor(0,100);
	motor(2,100);
	
	while (1) {
		if (digital(8) == 1) {
			break;
		}
	}
	
	set_servo_position(1, 1310);
	
	/*while (1)  {
		if (digital(8) == 0)  {
			break;
		}
	}
	*/
	msleep(1500);
	set_servo_position(1, 0);
	msleep(1000);
	
	freeze(0);
	freeze(2);
	disable_servos();
	
	return 0;
}
