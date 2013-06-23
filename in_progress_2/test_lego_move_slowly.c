// Created on Sat June 22 2013

#define PWM_SLEEP_ON 10
#define PWM_SLEEP_OFF 10

void move_slowly(int speed);

int main()
{
	printf("Starting\n");
	
	move_slowly(1);
	
	
	return 0;
}

void move_slowly(int speed) {
	while (1) {
		motor(LEFT, speed);
		motor(RIGHT, speed);
		msleep(PWM_SLEEP_ON);
		
		motor(LEFT, 0);
		motor(RIGHT, 0);
		msleep(PWM_SLEEP_OFF);
	}
}
