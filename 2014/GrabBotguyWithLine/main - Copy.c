// Created on Thu March 27 2014
//plug micro servo into port one

#define  RIGHT(x) motor(3, x)
#define  LEFT(x) motor(1, x)
#define  RFREEZE() freeze(3)
#define  LFREEZE() freeze(1)
#define  LEFTSENSOR 1
#define  RIGHTSENSOR 3
#define  CENTERSENSOR 5
#define  LEFTLIGHT 700
#define  RIGHTLIGHT 650
#define  CENTERLIGHT 780
#define  LEFTDARK 950
#define  RIGHTDARK 930
#define  CENTERDARK 950
#define RED 0
#define SEEDING_SERVO_POSITION 613
#define PUSH_BOTGUY_SERVO_POSITION 2000
#define PUSH_BOTGUY_SERVO_DOWN 320
#define  WAIT_FOR_CREATE 30000


int center_on_blob(int desired_x, int color,float time );
void start(int servo_position);
void find_and_grab(int color);
void seeding();
void push_botguy();

int main()
{
	drone_connect();
	printf("Press A for SEEDING, B for PUSH_BOTGUY\n");
	while (1) {
		if (a_button())
		{
			while (a_button());
			msleep(500);
			printf("Running SEEDING program.\n");
			start(SEEDING_SERVO_POSITION);
			seeding();
		}
		else if (b_button())
		{
			while (b_button());
			msleep(500);
			printf("Running PUSH_BOTGUY program.\n");
			start(PUSH_BOTGUY_SERVO_POSITION);
			push_botguy();
		}
	}
		
	// Don't need the rest anymore.
	// start(SEEDING_SERVO_POSITION);
	// start(PUSH_BOTGUY_SERVO_POSITION);
	// seeding();
	// push_botguy();
	return 0;
}

void seeding(){
	
	msleep(WAIT_FOR_CREATE);
	
	//starts driving to the black line
	LEFT(100);
	RIGHT(100);
	while (1)
	{
		if (analog10(LEFTSENSOR) > LEFTDARK)
		{
			break;
		}
	}
	ao();
	//turns on the black line
	msleep(1500);
	RIGHT(50);
	LEFT(-50);
	msleep(880);
	LFREEZE();
	RFREEZE();
	msleep(1500);
	//starts driving to end of black line
	LEFT(100);
	RIGHT(100);
	while(1)
	{
		if (analog10(RIGHTSENSOR) < RIGHTLIGHT && analog10(CENTERSENSOR) < CENTERLIGHT)
		{
			break;
		}
	}
	LFREEZE();
	RFREEZE();
	
	RIGHT(100);
	LEFT(100);
	msleep(200);
	LFREEZE();
	RFREEZE();
	//opens servo to score position
	set_servo_position(1, 2047);
	msleep(500);
	
	// turns to botguy
	RIGHT(-50);
	LEFT(50);
	msleep(760);
	LFREEZE();
	RFREEZE();

	
	center_on_blob(90, RED, 1);

	//drives to botguy
	RIGHT(100);
	LEFT(100);
	msleep(800);
	LFREEZE();
	RFREEZE();
	/*while(1){
		RIGHT(100);
		LEFT(100);
		msleep(200);
		center_on_blob(90, RED, 0);
	}*/
	
	//close the claw around botguy
	set_servo_position(1, 853);
	msleep(500);
	//backs up with botguy
	RIGHT(-100);
	LEFT(-100);
	msleep(1200);
	LFREEZE();
	RFREEZE();
	//turns to FMT
	RIGHT(50);
	LEFT(-50);
	msleep(1750);
	LFREEZE();
	RFREEZE();
	//drives to FMT
	RIGHT(100);
	LEFT(100);
	msleep(3900);
	LFREEZE();
	RFREEZE();
	
	disable_servos();
	ao();
}

//Precondition: camera must already be open
int center_on_blob(int desired_x, int color,float time ) {
	int actual_x;
	while (1) {
		camera_update();
		actual_x = get_object_center(color, 0).x;
		printf("%i\n");
		if (actual_x  > desired_x) {
			RIGHT(-20);
			LEFT(20);
			msleep(40);
			LFREEZE();
			RFREEZE();
		}
		if (actual_x < desired_x) {
			RIGHT(20);
			LEFT(-20);
			msleep(40);
			LFREEZE();
			RFREEZE();
		}
		if (actual_x < desired_x+3 && actual_x > desired_x-3){
			LFREEZE();
			RFREEZE();
			break;
		}
		msleep(200);
	}
}

void start(int servo_position)
{
	int k;
	
	camera_open(); 
	for (k = 0; k < 10; k = k+1)
	{
		camera_update();
		msleep(200);
	}
	
	set_servo_position(1, servo_position);
	enable_servos();
	msleep(1000);
	
	wait_for_light(7);
	
	shut_down_in(115);
}

void push_botguy() {
	set_servo_position(1, PUSH_BOTGUY_SERVO_DOWN);
	msleep(2000);
	
	// Garrett:  Put the robot against the PVC.
	//   It may have to BACK up a little bit
	//   or maybe do a BIT of a turn before centering on Botguy.
	//drives to edge of starting box
	RIGHT(100);
	LEFT(100);
	msleep(400);
	LFREEZE();
	RFREEZE();
	
	// Garrett:  Try replacing the next step with:
	//   center_on_blob(80, RED, 1);
	// First get Aaron's help to make center_on_blob USE
	//   its time parameter to be a FASTER center.
	
	//turns to knock cube out of the way
	RIGHT(-50);
	LEFT(50);
	msleep(2500);
	
	// Garrett:  Add code to:
	
	// Drive to Botguy, knocking him down.
	// KEEP GOING, so that you are out of the way of the Create
	// and IN the way of their team's robots.
	// Talk to Aaron about moving, then recentering,
	// as the robot goes to Botguy and then through the gate.
	
	disable_servos();
}

void find_and_grab(int color) {
	int k;
	RIGHT(100);
	LEFT(100);
	msleep(2950);
	LFREEZE();
	RFREEZE();
	
	RIGHT(-50);
	LEFT(50);
	msleep(700);
	LFREEZE();
	RFREEZE();
	center_on_blob(90, RED, 0);
	
	for(k = 0; k <= 10; k + 1){
		RIGHT(100);
		LEFT(100);
		msleep(200);
	center_on_blob(90, RED, 0);
	}
	/*
	while(1){
		RIGHT(100);
		LEFT(100);
		msleep(200);
		center_on_blob(90, RED, 0);
		if(depth_y  > Camera_y){
			RIGHT(50);
			LEFT(-50);
			msleep(710);
			LFREEZE();
			RFREEZE();
			RIGHT(100);
			LEFT(100);
			msleep(800);
			LFREEZE();
			RFREEZE();
		}
		if(depth_y == OBJECT){
			RIGHT(50);
			LEFT(-50);
			msleep(710);
			LFREEZE();
			RFREEZE();
			RIGHT(100);
			LEFT(100);
			msleep(1600);
			LFREEZE();
			RFREEZE();
		}
		if(depth_y != OBEJECT){
			RIGHT(50);
			LEFT(-50);
			msleep(710);
		}
		
	}*/
	disable_servos();
}

	
//	use center_on_blob to try to find botguy in under so many seconds. if it doesnt it goes to the other side of the board and tries to find him with center_on_blob.if it does find botguy it will continue on and drag him to the FMT area.


