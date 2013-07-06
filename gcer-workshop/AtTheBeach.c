/* Aaron visits the beach - an Aaron Robot Movie.
 * By Daniel, Sandy and David Mutchler.
 * July 5, 2013.  At GCER 2013 Workshop by Ross Mead.
 */

#define PI 3.14159
#define TRUE 1
#define FALSE 0

#define WAIST_SERVO_PORT 0
#define SPINE_SERVO_PORT 2
#define NECK_SERVO_PORT  1

#define WAIST_CENTER 990

#define WAIST_FOR_STANDING 990
#define SPINE_FOR_STANDING 627
#define NECK_FOR_STANDING 1158

#define WAIST_FOR_RELAX 990
#define SPINE_FOR_RELAX 0
#define NECK_FOR_RELAX 670

#define WAIST_FOR_SURPRISE1 990
#define SPINE_FOR_SURPRISE1 500
#define NECK_FOR_SURPRISE1 1300

#define NECK_LOOK_UP 0
#define WAIST_FOR_LOOK_RIGHT 500
#define WAIST_FOR_LOOK_LEFT 1560

#define SPINE_BACK 0
#define NECK_BACK 0

#define PRESS_A_ENABLED TRUE

// function prototypes
void actor_move_for(float time_duration, int l_vel, int r_vel, int waist_pos_end, int spine_pos_end, int neck_pos_end);
void press_A_to_continue();

void stand_up();
void relax();
void look_around(int speed);
void show_surprise_to_ball(int episode);
void move_to_umbrella();
void kiss_botgirl();
	
//void walk();
void react_to_storm();

// moves the "waist", "spine", and "neck" servos for the specified
// duration to the specified positions
void react_to_ball();

void go_to(point2 point_to_go_to, point2 point_currently_at, int speed_to_move_at);
void look(int speed);
	
int main() {
	point2 points[] = {{100, 100}, {200, 100}, {300, 200}, {400, 200}};
	int k, number_of_points;
	
	printf("Connecting to Create...");
	create_connect();
	create_full();
	
	printf("Connected!\n");
	press_A_to_continue();
	msleep(3000);
	
	stand_up();
	//press_A_to_continue();
	
	for (k = 1; k <= 2; ++k) {
		relax();
		//press_A_to_continue();
		
		// drop balls
		show_surprise_to_ball(k);
		//press_A_to_continue();
	}
	
	relax();
	
	stand_up();
	//press_A_to_continue();
	
	move_to_umbrella();
	kiss_botgirl();
	
	/*
	set_servo_position(0, 1024);
	set_servo_position(1, 1024);
	set_servo_position(2, 1024);
	enable_servos();
	
	number_of_points = sizeof(points) / sizeof(point2);
	
	// For points A, B, C ...:
	for (k = 0; k < number_of_points - 1; ++k) {
		// Aaron goes from current point to next point.
		//go_to(points[k + 1], points[k], 30);
		
		// Aaron encounters and reacts to rain.
		stand_upright();
		react_to_rain(k);
		msleep(5000);
	}
	
	// XXX goes to Botgirl.
	// XXX interacts with Botgirl.
	*/
	create_disconnect();
	
	return 0;
}

void move_to_umbrella() {
	int k;
	
	for (k = 0; k < 3; ++k) {
		create_drive(500, 200);
		msleep(1000);
		//create_stop();
		//press_A_to_continue();
		
		create_drive(500, -200);
		msleep(1000);
		//create_stop();
		//press_A_to_continue();
	}
	create_stop();
}

void kiss_botgirl() {
	create_spin_CCW(100);
	msleep(5000);
	create_stop();
	relax();
}

void stand_up() {
	set_servo_position(WAIST_SERVO_PORT, WAIST_FOR_STANDING);
	set_servo_position(SPINE_SERVO_PORT, SPINE_FOR_STANDING);
	set_servo_position(NECK_SERVO_PORT, NECK_FOR_STANDING);
	enable_servos();
}

void relax() {
	msleep(1000);
	actor_move_for(2.0, 0, 0, WAIST_FOR_RELAX, SPINE_FOR_RELAX, NECK_FOR_RELAX);
	msleep(5000);
}

void look_around(int speed) {
	actor_move_for(1.5, speed, speed, WAIST_FOR_LOOK_LEFT, get_servo_position(SPINE_SERVO_PORT), NECK_LOOK_UP);
	msleep(300);
	actor_move_for(1.5, -speed, -speed, WAIST_FOR_LOOK_RIGHT, get_servo_position(SPINE_SERVO_PORT), NECK_LOOK_UP);
	msleep(300);
	actor_move_for(1.5, 0, 0, WAIST_FOR_SURPRISE1, get_servo_position(SPINE_SERVO_PORT), NECK_FOR_SURPRISE1);
	msleep(300);
	
	actor_move_for(0.75, speed, speed, WAIST_FOR_LOOK_LEFT, get_servo_position(SPINE_SERVO_PORT), get_servo_position(NECK_SERVO_PORT));
	msleep(300);
	actor_move_for(1.5, -speed, -speed, WAIST_FOR_LOOK_RIGHT, get_servo_position(SPINE_SERVO_PORT), get_servo_position(NECK_SERVO_PORT));
	msleep(300);

	actor_move_for(1.5, 0, 0, WAIST_CENTER, get_servo_position(SPINE_SERVO_PORT), get_servo_position(NECK_SERVO_PORT));
	msleep(300);
}

void show_surprise_to_ball(int episode) {
	int speed;
	
	if (episode == 1) {
		speed = 0;
	} else if (episode == 2) {
		speed = 100;
	}
	actor_move_for(0.2, 0, 0, WAIST_FOR_SURPRISE1, SPINE_FOR_SURPRISE1, NECK_FOR_SURPRISE1);
	msleep(1000);
	look_around(speed);
}
/*
void show_surprise_to_ball2() {
	actor_move_for(0.2, 0, 0, WAIST_FOR_SURPRISE2, SPINE_FOR_SURPRISE2, NECK_FOR_SURPRISE2);
	msleep(1000);
	look_around();
}
*/
/*
void walk() {
	set_servo_position(WAIST_SERVO_PORT, WAIST_FOR_WALKING);
	set_servo_position(SPINE_SERVO_PORT, SPINE_FOR_WALKING);
	set_servo_position(NECK_SERVO_PORT, NECK_FOR_WALKING);
}
*/
void react_to_storm() {
	int k;
	
	for (k = 0; k < 1; ++k) {
		relax();
		msleep(2000);
		press_A_to_continue();
		
		//show_surprise_to_ball();
		msleep(2000);
		press_A_to_continue();
		//look_around(k);
		//show_disgust(k);
	}
}

void press_A_to_continue() {
	if (PRESS_A_ENABLED) {
		printf("Press A to continue.\n");
		while (! a_button()) {}
		printf("Hands off!\n");
		while (a_button()) {}
		msleep(0.5);
	}
}

void actor_move_for(float time_duration, int l_vel, int r_vel, int pos_end_waist, int pos_end_spine, int pos_end_neck)
{
	int pos_start_waist = get_servo_position(WAIST_SERVO_PORT);
	int pos_start_spine = get_servo_position(SPINE_SERVO_PORT);
	int pos_start_neck = get_servo_position(NECK_SERVO_PORT);
	int pos_current_waist = pos_start_waist;
	int pos_current_spine = pos_start_spine;
	int pos_current_neck = pos_start_neck;

	float time_start = seconds();
	float time_elapsed = seconds() - time_start;
	
	create_spin_CCW(l_vel);
	while (time_elapsed <= time_duration)
	{
		pos_current_waist = pos_start_waist + (pos_end_waist - pos_start_waist) *
		time_elapsed / time_duration;
		set_servo_position(WAIST_SERVO_PORT, pos_current_waist);
		printf("[%.2f] setting servo[%d] to pos. %d\n",
		time_elapsed, 0, pos_current_waist);
		time_elapsed = seconds() - time_start;
		
		pos_current_spine = pos_start_spine + (pos_end_spine - pos_start_spine) *
		time_elapsed / time_duration;
		set_servo_position(SPINE_SERVO_PORT, pos_current_spine);
		printf("[%.2f] setting servo[%d] to pos. %d\n",
		time_elapsed, 1, pos_current_spine);
		time_elapsed = seconds() - time_start;
		
		pos_current_neck = pos_start_neck + (pos_end_neck - pos_start_neck) *
		time_elapsed / time_duration;
		set_servo_position(NECK_SERVO_PORT, pos_current_neck);
		printf("[%.2f] setting servo[%d] to pos. %d\n",
		time_elapsed, 2, pos_current_neck);
		time_elapsed = seconds() - time_start;
	}
	set_servo_position(WAIST_SERVO_PORT, pos_end_waist);
	set_servo_position(SPINE_SERVO_PORT, pos_end_spine);
	set_servo_position(NECK_SERVO_PORT, pos_end_neck);
	
	create_stop();
}

/*
// Robot moves to the relaxed position.
// Precondition: Robot is upright.
void relax(int k) {
	actor_move_for(2.0, 0, 0, WAIST_CENTER, SPINE_BACK, NECK_BACK);
// Robot goes to point1 from point2 (in centimeters), at given speed (in centimeters per second).
// Precondition:  Robot is at point2, facing in the direction of the positive x-axis.
void go_to(point2 point_to_go_to, point2 point_currently_at, int speed_to_move_at) {
	int x_centimeters, y_centimeters;
	int x_milliseconds, y_milliseconds;
	float start_time, current_time;
	
	x_centimeters = point_to_go_to.x - point_currently_at.x;
	y_centimeters = point_to_go_to.y - point_currently_at.y;
	
	x_milliseconds = (1000.0 * x_centimeters) / speed_to_move_at;
	y_milliseconds = (1000.0 * y_centimeters) / speed_to_move_at;
	
	// Drive in x direction.
	start_time = seconds();
	create_drive_straight(10 * speed_to_move_at);
	while (TRUE) {
		if (seconds() - start_time >= x_milliseconds) {
			create_stop();
			break;
		}
		look(10);
	}
	
	// Spin 90 degrees CCW.
	create_spin_CCW(45);
	msleep(2000);
	create_stop();
	
	// Drive in y direction.
	start_time = seconds();
	create_drive_straight(speed_to_move_at);
	while (TRUE) {
		if (seconds() - start_time >= y_milliseconds) {
			create_stop();
			break;
		}
		look(10);
	}
	
	// Spin 90 degrees CW.
	create_spin_CW(45);
	msleep(2000);
	create_stop();
}

void look(int speed) {}

// moves the "waist" servo for the specified
// duration (time) to the specified end position
void servo_move_for(int servo, float time_duration, int pos_end)
{
	int pos_start = get_servo_position(0);
	int pos_current = pos_start;
	float time_start = seconds();
	float time_elapsed = seconds() - time_start;
	while (time_elapsed <= time_duration)
	{
		pos_current = pos_start + (pos_end - pos_start) *
		time_elapsed / time_duration;
		set_servo_position(servo, pos_current);
		printf("[%.2f] setting servo[%d] to pos. %d\n",
		time_elapsed, 0, pos_current);
		time_elapsed = seconds() - time_start;
	}
	set_servo_position(servo, pos_end);
} // end servo_move_for()



//void relaxing(speed)
//{
	//;
//}

//void drink_soda(speed)
//{
	//;
//}

void react_to_ball()
{
	servo_move_for(NECK_SERVO_PORT, 2.0, 1163);
	msleep(2.0);
	
	int k;
	
	for(k=0; k < 2; ++k)
	{
	servo_move_for(NECK_SERVO_PORT, 1.0, 1130);
	servo_move_for(WAIST_SERVO_PORT, 1.0, 727);
	}
	
	servo_move_for(NECK_SERVO_PORT, 1.0, 990);
}

	


//void disgust()
//{
	//;
//}

//void observe(speed)
//{
	//;
//}

*/
