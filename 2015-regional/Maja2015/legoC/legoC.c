// Created on Sat March 21 2015
// last updated 4/16/15
//test for going in a square
#define OPEN 700
#define CLAW 1 // servo port 1
#define CLOSED 1100
#define RM 0 // Right motor port 0
#define LM 2
#define RM_PWR 1.00 
#define LM_PWR 0.71
#define RT 0// tape sensors 0,2
#define LT 2
#define BLACKTAPE 300
//#define PRACTICE 0 //1 for pause, 0 for no practice
#define START_LIGHT 4 // lightsensor port 4

void reverse(int time, int speed);
void forwardToLine(int maxTime, int speed);
void turnToLine(int maxTime, int speed);
void followLine(int maxTime, int turnTime, int speed);
void turn(int time, int speed);
void forward(int time, int speed);

int PRACTICE;

void main()
{
	enable_servos();
	msleep(500);
	set_a_button_text("Practice");
	set_b_button_text("Tournament");
	set_c_button_text("");
	
	// Close claws
	set_servo_position(CLAW, CLOSED);
	//msleep(1000);
	printf("closed claw\n");
	
	while(1==1)
	{
		if(a_button()==1){
			PRACTICE = 1;
			break;
		}
		
		if(b_button()==1){
			PRACTICE = 0;
			break;
		}
		
		msleep(50);
	}
	
	//wait_for_light(START_LIGHT);
	//shut_down_in(119);	
	//msleep(11000);
    
	//motor forward
	forward(900, 100);
	printf("end 1st foward\n");
	
	//motor turn
	turn(50, -100);
	printf("end 1st turn\n");
	
	//Open Claw
	set_servo_position(CLAW, OPEN);
	msleep(200);
	printf("opened claw 1st time\n");
		
	//motor forward
	forward(1000, 100);
	printf("end 2nd foward\n");
	
	//motor forward
	forward(4500, 100);
	printf("end 3rd forward\n");
	
	//motor turn
	turn(230, 50);
	printf("end 2rd turn\n");
	
	//motor forward
	forward(1750, 100);
	printf("end 3rd forward\n");
	
	//motor reverse
	reverse(1020, 100);
	printf("end 1st reverse\n");
	
	// Close claws
	set_servo_position(CLAW, CLOSED);
	//msleep(1000);
	printf("closed claw\n");
	
	//turn 180
    turn(800, 100);
	printf("end 1st 180\n");
	
	//forward to middle line
	forward(2150, 100);
	printf("end 4th forward (middle line)\n");
	
	//turn left 90
	turn(400, -100);
	printf("end turn left 90\n");
	
	//forward
	forward(3000, 100);
	printf("going into cave\n");
	
	// Inside cave
	
	//turn right 45
	turn(220, 100);
	printf("end turn right 90\n");
	
	//forward
	forward(100, 100);
	printf("forward into turn\n");
	
	//turn right 45
	turn(200, 100);
	printf("end turn right 90\n");
	
	//Open Claw
	set_servo_position(CLAW, OPEN);
	msleep(200);
	printf("opened claw 2nd time\n");
	
	//forward to end of cave 1
	forward(3400, 100);
	printf("end 5th forward (cave1)\n");
	
	// Close claws
	set_servo_position(CLAW, CLOSED);
	//msleep(1000);
	printf("closed claw\n");
	
	// Reverse out of cave1
	reverse(4000, 100);
	printf("end 2nd reverse (cave1)\n");
	
	//turn right 45
	turn(255, 100);
	printf("end first 45\n");
	
	//forward
	forward(3600, 100);
	printf("going out of cave\n");
	
	//turn left 45
	turn(206, -100);
	printf("end turn left 45\n");
	
	//motor forward
	forward(1600, 100);
	printf("end last foward\n");
	
	
	//turn everything off
	disable_servo(CLAW);
	ao();
	printf("done\n");
}


void reverse(int time, int speed)
{
	//reverse
	motor(RM, -speed * RM_PWR);
	motor(LM, -speed * LM_PWR);
	msleep(time* 1.8 );
	ao(); // Stop moors
	msleep(50);
	if(PRACTICE == 1){
		//look for button press a
		while(a_button()==0){
			msleep(50);
			}
	}
}	

void forward(int time, int speed){
	// Move forward
    motor(RM, speed*RM_PWR);
    motor(LM, speed*LM_PWR);
	msleep(time* 1.8 );
	ao(); // Stop motors
	msleep(50);
	if(PRACTICE == 1){
		//look for button press a
		while(a_button()==0){
			msleep(50);
			}
	}
}

void turn(int time, int speed){
	// Turn Left
    motor(RM, speed*RM_PWR);
    motor(LM, -speed*LM_PWR);
	msleep(time* 2 );
	ao(); // Stop motors
	msleep(50);
}
