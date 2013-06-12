// Created on Sun March 31 2013

#define sleep(seconds) msleep(seconds * 1000)

#define CLAW_SERVO 

void servo_booster(int servo_port, int motor_port, int servo_position, int motor_position);

int main()
{
	set_servo_position(1, 442);
	set_servo_position(3, 233);
	set_servo_position(0, 186);
	enable_servos();
	sleep(5);
	servo_booster(1, 0, 1500 , 250);
	sleep(5);
	return 0;
}

void servo_booster(int servo_port, int motor_port, int servo_position, int motor_position)
{
	clear_motor_position_counter(motor_port);
	motor(motor_port, 100);
	set_servo_position(servo_port, servo_position);
	while (get_motor_position_counter(motor_port) < motor_position);
	off(motor_port);
}

void close_claw()
{
	set_servo_position(CLAW_SERVO, 0);
}

void ()
{
	set_servo_position(CLAW_SERVO, 1271);
}
