// Created on Tue March 24 2015

// ZOE: Help the students ensure the following:
//   1. The motors from the wheels should be plugged
//        into ports 0 (left wheel) and 2 (right wheel).
//   2. For each wheel, turning the wheel by hand in the direction
//        that would cause the robot to move forward
//        should cause the little light on the Link for that port
//        to turn GREEN (not red).  [If the light turns RED,
//        simply reverse the pin that connects the motor's wire to the Link.]
//   3. The INCHES_PER_SECOND below will need to be tuned by experiment.
//        Run the robot with command:  forward(6, 100)
//        and measure how far the robot goes.  If way off from 6 inches,
//        adjust   INCHES_PER_SECOND  appropriately and try again.
//        Just get it roughly right -- exact is NOT important.
//   4. Likewise for the command:  left(90, 100)
//        and eyeball to see if the robot goes roughly 90 degrees.
//        Totally OK if turns are inconsistent and/or off by LOTS.
//
//   Do NOT spend time trying to get the INCHES_PER_SECOND or
//   DEGREES_PER_SECOND exactly right.  We will do that later.
/*
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
#define INCHES_PER_SECOND 8.0
#define DEGREES_PER_SECOND 50.0

void forward(float inches, int power);
void backward(float inches, int power);
void left(float degrees, int power);
void right(float degrees, int power);
void example();

int main()
{
	printf("Starting Lego run.\n");
	
	example();
	
	printf("Finished Lego run.\n");
	return 0;
}

void example() {
	forward(12.4, 80); // Example: forward 12.4 inches at 80% power
	msleep(2000);
	backward(12.4, 100);
	msleep(2000);
	left(90, 50);
	msleep(2000);
	right(45, 50);
}

// Move the specified direction for the given distance (in inches)
// at the given power (-100 to 100, where negative means backward).
void forward(float inches, int power) {
	motor(LEFT_MOTOR, power);
	motor(RIGHT_MOTOR, power);
	
	if (power < 0) power = -power;
	
	msleep((int) (1000 *  (100.0 / power) * (inches / INCHES_PER_SECOND)));
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void backward(float inches, int power) {
	forward(inches, -power);
}

void left(float degrees, int power) {
	motor(LEFT_MOTOR, -power);
	motor(RIGHT_MOTOR, power);
	
	if (power < 0) power = -power;

	msleep((int) (1000 *  (100.0 / power) * (degrees / DEGREES_PER_SECOND)));
	
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void right(float degrees, int power) {
	left(degrees, -power);
}
*/
