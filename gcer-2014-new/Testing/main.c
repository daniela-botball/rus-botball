// Created on Wed July 2 2014

void run_motor(int port, int power, float seconds_to_run);
void run_wheel_motors(int port1, int port2, int power1, int power2, float seconds_to_run);
void test_motor_speeds();
void press_a_to_continue();
void try_motor_speeds();

int main()
{
	try_motor_speeds();
	return 0;
	
	int k;
	
	for (k = 0; k < 5; ++k) {
		run_wheel_motors(0, 2, 100 - 20*k, 100 - 20*k, 8.0);
		press_a_to_continue();
	}
	
	for (k = 0; k < 5; ++k) {
		run_wheel_motors(0, 2, -(100 - 20*k), -(100 - 20*k), 8.0);
		press_a_to_continue();
	}
	
	//test_motor_speeds();
	return 0;
}

void try_motor_speeds() {
	int left_speed, right_speed;
	
	extra_buttons_show();
	
	left_speed = 80;
	right_speed = 80;
	
	
	printf("Set the motor speeds, as follows:\n");
	printf("A increases, B decreases the LEFT motor speed.\n");
	printf("X and Y do the same for the RIGHT motor speed.\n");
	printf("C to run an 8 second test.\n");
	printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
	
	while (1) {
		
		if (a_button()) {
			left_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (a_button()) ;
		}
		if (b_button()) {
			left_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (b_button()) ;
		}
		if (x_button()) {
			right_speed += 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (x_button()) ;
		}
		if (y_button()) {
			right_speed -= 5;
			printf("Current left, right are: %3i %3i\n", left_speed, right_speed);
			while (y_button()) ;
		}
		if (c_button()) {
			printf("Running at: %3i %3i\n", left_speed, right_speed);
			while (c_button()) ;
			msleep(500);
			run_wheel_motors(0, 2, left_speed, right_speed, 8.0);
			printf("Done, change speeds as desired.\n");
		}
	}
}

void test_motor_speeds() {
	int port;
	int powers[] = {100, 80, 50, 10, 5, -5, -10, -50, -80, -100};
	int number_of_powers = 10;
	int k;
	
	int seconds_to_run = 5.0;
	
	for (port = 2; port < 3; ++port) {
		for (k = 0; k < number_of_powers; ++k) {
			run_motor(port, powers[k], seconds_to_run);
		}
	}
}

/* Plug in the motor with green being "forward",
   with left ports to left wheel and right ports to right wheel.
*/
void run_motor(int port, int power, float seconds_to_run) {
	float s;
	
	motor(port, power);
	
	clear_motor_position_counter(port);
	
	s = seconds();
	while (1) {
		if (seconds() - s > seconds_to_run) {
			break;
		}
	}
	
	off(port);
	
	printf("Port, power, counter:  %1i %3i %5i \n", port, power, get_motor_position_counter(port));
	press_a_to_continue();
}


void run_wheel_motors(int port1, int port2, int power1, int power2, float seconds_to_run) {
	float s;
	
	motor(port1, power1);
	motor(port2, power2);
	
	clear_motor_position_counter(port1);
	clear_motor_position_counter(port2);
	
	s = seconds();
	while (1) {
		if (seconds() - s > seconds_to_run) {
			break;
		}
	}
	
	off(port1);
	off(port2);
	printf("Motor counters:  %5i %5i\n", get_motor_position_counter(port1), get_motor_position_counter(port2));
}

void press_a_to_continue() {
	while (! a_button());
	while (a_button());
	msleep(500);
}
