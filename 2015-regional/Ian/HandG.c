// Created on March 30 2015
#define OPEN 230
#define CLOSE 840
void forward(int speed);

int main()
{
	printf("Hello, World!\n");
	set_servo_position(0,CLOSE);
	enable_servos();
	
	lego_drive_distance(FORWARDS, 2000, 50);
	msleep(2000);
  set_servo_position(0,CLOSE);
	motor(0, 100); //motor 0 was 80
	motor(2, -100);// motor 2 was 20
	msleep(1100);
	set_servo_position(0,OPEN);
	forward(100);
	msleep(1950);
	
	ao();
	
	return 0;
}

void forward(int speed)
{
	motor(0, speed);
	motor(2, speed);
}


