/*
 * Demonstrates use of the Move-Calibration library.
 *
 * Authors: Aaron, Seth and David Mutchler.
 * July 2014.
*/

#include "mc_interface.h"
#include "movement.h"
#include "lego_movement.h"

//#include "create_movement.h"

int _ROBOT; // FIXME: This and next several items belong in utilities.
#define LEGO 0
#define CREATE 1

/*
typedef struct {
	int color;
	int index; // refered to as object by KIPR camera code
} BLOB;
*/

int biggest_blob(int colors[], int number_of_colors_to_check);
void point_to_x(int desired_x, int delta, int min);

// Spin appropriately until center of biggest PINK or GREEN blob is within delta of desired_x.
void point_to_x(int desired_x, int delta, int min) {
	int color;
	int colors[] = {0, 1}; // TODO: Change 0, 1 to PINK, GREEN
	int x;
	
	printf("Trying to point to x = %i, delta %i, min %x.\n", desired_x, delta, min);
	
	while (1) {
		camera_update();
		color = biggest_blob(colors, 2);
		x = get_object_center(color, 0).x;
		
		if (color < 0) {
			printf("No blobs seen.\n");
			// Move xxx.
		} else if (get_object_area(color, 0) < min) {
			printf("Biggest blob is %i, want %i.\n", get_object_area(color, 0), min);
		} else if (x < desired_x - delta) {
			// Move xxx.
		} else if (x > desired_x + delta) {
			// Move yyy.
		} else {
			printf("Stopping point_to_x at %i.\n", x);
			break;
		}
		msleep(20);
	}
}

int biggest_blob(int colors[], int number_of_colors_to_check) {
	// Returns the biggest blob among all the given colors. Color of -1 means no blob
	int k;
	int biggest_area = -1;
	int biggest_blob_color = -1;
	
	for (k = 0; k < number_of_colors_to_check; ++k) {
		if (get_object_count(colors[k]) > 0 && get_object_area(colors[k], 0) > biggest_area) {
			biggest_area = get_object_area(colors[k], 0);
			biggest_blob_color = k;
		}
	}
	
	return biggest_blob_color;
}

int main() {	
	//int normal_speed;
	
	_ROBOT = LEGO;
	mc_init();
	turn_mc_on();
	
	mc_move(MC_FORWARD, 10.0, 80);
	mc_move(MC_NO_MOVE, 0, 0);
	mc_move(MC_RIGHT, 30, 70);
	
	// FIXME: I am unsure whether the create speeds for spinning are degrees per second.
	// normal_speed = LEGO_NORMAL_LINEAR_SPEED;

	//printf("Connecting ...");
	//create_connect();
	
	//printf(" Connected!\n");
	//create_full();
	
	// Out of starting box.
	/*
	motor(3, -20);
	msleep(1000);
	ao();
	mc_move(MC_FORWARD, 45, normal_speed);
	
	// To center rack.
	mc_move(MC_LEFT, 90, normal_speed);
	mc_move(MC_FORWARD, 30, normal_speed);
	mc_move(MC_RIGHT, 90, normal_speed);
	mc_move(MC_FORWARD, 45, normal_speed);
	*/
/*	
	
	move(FORWARD, 10, 50);
	move(LEFT, 15, 80);
	move(FORWARD, 5, 50);
	move(LEFT, 5, 80);
	move(FORWARD, 30, 50);
	move(LEFT, 110, 80);
	move(FORWARD, 140, 50);
	move(RIGHT, 5, 80);
	move(FORWARD, 30, 50);
	move(RIGHT, 180, 80);
	move(FORWARD, 140, 50);
	move(RIGHT, 180, 80);
	move(BACKWARD, 20, 50);
	*/
	return 0;
}
