// Created on Sun June 16 2013

#include "universal_library.h"
#include "servos.h"
#include "create_library.h"
#include "camera_library.h"
//#include "rus_opencv_library.h"

#define BOOSTER_COLOR 0
#define LIGHT_PORT 0
#define DRIVE_TO_FRONT_BUMP_SPEED 400 // mm per second

int start_robot();
int initialize_create_and_camera();
void initialize_servos();

void turn_to_pole();
void drive_to_booster(int distance, int direction);
void grab_booster_main(int distance);
void drop_booster_main(int distance, int booster);
void get_birdie();

void test_grab_booster();
void test_get_birdie();

int main()
{
	int status;
	
	// Choose from: TOURNAMENT_RUN, PRACTICE_RUN, PRACTICE_RUN_WITH_LIGHTS.
	_TYPE_OF_RUN = PRACTICE_RUN;
	status = start_robot();
	if (status == FAILURE) return FAILURE;
	
	while (1) {
		printf("Pole x: %i\n", pole_x());
		msleep(1000);
	}
		
	turn_to_pole();
	
	drive_to_booster(47, BACKWARDS);
	grab_booster_main(5);
	drop_booster_main(23, 1);
	
	drive_to_booster(22, FORWARDS);
	grab_booster_main(3);
	drop_booster_main(25, 2);
	
	drive_to_booster(12, FORWARDS);
	grab_booster_main(3);
	drop_booster_main(15, 3);
	
	drive_to_booster(2, FORWARDS);
	grab_booster_main(3);
	
	return SUCCESS;
}

int start_robot()
{
	int status;
	
	switch (_TYPE_OF_RUN)
	{
		case TOURNAMENT_RUN:
		{
			_SKIP_PRESS_A_TO_CONTINUE = TRUE;
			_WAIT_FOR_LIGHTS = TRUE;
			break;
		}
		case PRACTICE_RUN:
		{
			_SKIP_PRESS_A_TO_CONTINUE = FALSE;
			_WAIT_FOR_LIGHTS = FALSE;
			break;
		}
		case PRACTICE_RUN_WITH_LIGHTS:
		{
			_SKIP_PRESS_A_TO_CONTINUE = FALSE;
			_WAIT_FOR_LIGHTS = TRUE;
			break;
		}
	}
	
	status = initialize_create_and_camera();
	if (status == FAILURE) return FAILURE;
		
	//initialize_servos();
	
	if (_WAIT_FOR_LIGHTS) {
		wait_for_light(LIGHT_PORT);
	}
	else
	{
		printf("Ready to start run!\n");
	}
	
	return SUCCESS;
}

int initialize_create_and_camera()
{
	int status;
	
	printf("Program starts OK\n");
	printf("Trying to connect to the Create ... \n");
	create_connect();
	
	printf("Connected!  Putting into full mode.\n");
	create_full();
	
	printf("Trying to start the camera ... \n");
	status = camera_open(LOW_RES);
	if (status == 1)
	{
		printf("Camera is on!\n");
	}
	else
	{
		printf("Camera did NOT open.\n");
		printf("Stopping this run now!");
		return FAILURE;
	}
	
	CANNY_1 = 80;
	CANNY_2 = 120;
	
	HOUGH_1 = 180;
	HOUGH_2 = 20;
	HOUGH_3 = 1;
	HOUGH_4 = 30;
	
	return SUCCESS;
}

void initialize_servos() {
	printf("Have you manually place ALL servos\n");
	printf("in their START positions yet????\n");
	press_A_to_continue();
	
	start_servos();
}

void turn_to_pole()
{
	relax_servos();														// Turns the servos off to drive
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);									// Spins towards the pole
	press_A_to_continue();
}

void drive_to_booster(int distance, int direction)
{
	relax_servos();
	create_drive_distance(distance, 20, direction);						// Drives towards the pole, stopping at the booster
	press_A_to_continue();
	create_spin_degrees(87, 87, RIGHT);									// Turns towards the booster
	press_A_to_continue();
	
	unrelax_servos();
	move_so_blob_is_at(BOOSTER_COLOR, (116 + 144) / 2, 5, 100, BOOSTER_X, LEFT_RIGHT, 20); // was 159
	press_A_to_continue();
	move_so_blob_is_at(BOOSTER_COLOR, 51, 5, 100, BOOSTER_Y, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	
	move_so_blob_is_at(BOOSTER_COLOR, (116 + 144) / 2, 2, 100, BOOSTER_X, LEFT_RIGHT, 20);
	press_A_to_continue();
	move_so_blob_is_at(BOOSTER_COLOR, 51, 1, 100, BOOSTER_Y, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	/*move_so_blob_is_at_x(0, 91, 5, 0);									// Spins to the x of the booster
	press_A_to_continue();
	move_so_blob_is_at_y(0, 30, 1, 0, 0);								// Moves to the y of the booster
	press_A_to_continue();
	move_so_blob_is_at_x(0, 91, 2, 0);									// Fixes any inaccuracies in the previous x fix
	press_A_to_continue();
	move_so_blob_is_at_y(0, 30, 1, 0, 0);								// Fixes any inaccuracies caused by the second move to x
	press_A_to_continue();*/
}

void grab_booster_main(int distance)
{													
	//open_gate(600);														// Opens the gate so the arm can come down
	grab_booster(distance);												// Grabs the booster
	press_A_to_continue();
	lift_booster();														// Lifts the booster to drive
	press_A_to_continue();	
}

void drop_booster_main(int distance, int booster)
{
	create_spin_degrees(87, 87, LEFT);									// Spins towards the pole to drop the booster
	press_A_to_continue();
	
	if (booster == 1)
	{
		create_drive_distance(15, 20, BACKWARDS);						// Drives forward so the camera can see the pole
		press_A_to_continue();
	}
	move_so_blob_is_at(BOOSTER_COLOR, 64, 2, 100, CENTER_X, BACKWARDS_FORWARDS, 40);
	press_A_to_continue();
	
	if (booster == 1 || booster == 2)
	{
		move_so_blob_is_at(BOOSTER_COLOR, 102, 2, 100, CENTER_Y, BACKWARDS_FORWARDS, 40);
		press_A_to_continue();
	}	
	
	create_drive_distance(distance, 3, BACKWARDS);						// Drives against the wall of the poles to correct itsef and drop the booster
	press_A_to_continue();
	drop_booster(DROP_BOOSTER);											// Drops the booster
}

void get_birdie() {
	// Set servos for driving to birdie.
	set_servos_for_driving_to_birdie();
	press_A_to_continue();
	
	// Go forward until hits front bump sensor.
	create_drive(DRIVE_TO_FRONT_BUMP_SPEED, FORWARDS);
	while (TRUE)
	{
		if (get_create_lbump(0.05) == 1 || get_create_rbump(0.05) == 1)
		{
			break;
		}
	}
	create_stop();
	press_A_to_continue();
	
	// Go backward 19 cm.
	create_drive_distance(19, 20, BACKWARDS);
	press_A_to_continue();
	
	// Turn right 90 degrees.
	create_spin_degrees(87, 87, RIGHT);
	press_A_to_continue();
	
	// Go backwards 30 cm.
	create_drive_distance(30, 20, BACKWARDS);
	press_A_to_continue();
	
	// Lower arm so that claw is ready to go through hole.
	set_servos_and_gate_for_going_through_hole();
	press_A_to_continue();
}

void test_get_birdie() {
	get_birdie();
	press_A_to_continue();
}

void test_grab_booster() {
	grab_booster_main(5);
}

int pole_x() {
	int lines_as_4_ints[4000];
	Line lines[1000];
	int number_of_lines, k;
	
	camera_update();
	number_of_lines = cv_find_pole(lines_as_4_ints);
	for (k = 0; k < number_of_lines; ++k) {
		lines[k].endpoint1.x = lines_as_4_ints[(4 * k) + 0];
		lines[k].endpoint1.y = lines_as_4_ints[(4 * k) + 1];
		lines[k].endpoint2.x = lines_as_4_ints[(4 * k) + 2];
		lines[k].endpoint2.y = lines_as_4_ints[(4 * k) + 3];
	}
	
	return identify_pole_center(lines,number_of_lines);
}
	
void spin_left_for_camera_search(int speed) { create_spin_CCW(speed); } // was 20
void spin_right_for_camera_search(int speed) { create_spin_CW(speed); }
void move_backwards_for_camera_search(int speed) { create_drive_straight(-speed); }  // was -40
void move_forwards_for_camera_search(int speed) { create_drive_straight(speed); } // was 40
void stop_camera_search() { create_stop(); }
