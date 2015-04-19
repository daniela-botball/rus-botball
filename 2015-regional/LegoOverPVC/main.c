// Created on Tue April 14 2015

int main()
{
	printf("Please press A button\n");
	
	set_servo_position(1, 700);
	enable_servos();
	
	while (! a_button()) {}
	printf("Hands off!\n");
	while (a_button()) {}
	msleep(1000);
	
	motor(0, 100);
	motor(2, 100);
	
	/*while (1) {
		if (digital(8) == 1) {
			break;
		}
	}
	*/
	msleep(1000);
	set_servo_position(1, 1500);
	msleep(1500);
	set_servo_position(1, 1700);
	msleep(1000);
	set_servo_position(1, 700);
	msleep(2000);
	set_servo_position(1,1800);
	msleep(1000);
	set_servo_position(1,500);
	msleep(2000); 
	
	/*while (1)  {
		if (digital(8) == 0)  {
			break;
		}
	}
	
	set_servo_position(1, 500);
	msleep(2000);
	*/
	freeze(0);
	freeze(2);
	disable_servos();
	
	return 0;
}
