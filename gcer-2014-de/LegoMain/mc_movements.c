// FIXME: Add description.
// Authors:  Aaron, Seth and David Mutchler.
//           July 2014 (with earliest versions dating from 2006).
// FIXME: Add Creative Commons license.

#include "mc_movements.h"
#include "legoMovement.h"
#include "movement.h"

char MC_DIRECTION_STRINGS[4][20] = {"forward", "backward", "left", "right"};

float real_move(MC_DIRECTION direction_to_move, float amount_to_move, float speed_at_which_to_move) {
	printf("Moving %s for %f at speed %f.\n", MC_DIRECTION_STRINGS[direction_to_move], amount_to_move, speed_at_which_to_move); // FIXME: Remove after testing is done.
	if (direction_to_move == MC_FORWARD) {
		robot_drive_distance(amount_to_move, speed_at_which_to_move, FORWARDS);
	} else if (direction_to_move == MC_BACKWARD) {
		robot_drive_distance(amount_to_move, speed_at_which_to_move, BACKWARDS);
	} else if (direction_to_move == MC_LEFT) {
		robot_spin_degrees(amount_to_move, speed_at_which_to_move, LEFT);
	} else if (direction_to_move == MC_RIGHT) {
		robot_spin_degrees(amount_to_move, speed_at_which_to_move, RIGHT);
	} else {
		printf("Unknown direction\n"); // FIXME to be better
	}
	
	return 0.0; // Stub, to be replaced with your own code.
}

/*
// Empty implementations.
// The user of this framework must replace the ones she intends to use
// with implementations that work as she wants.

float forward(float distance, float speed)  { return -1; } // DO NOTHING 
float backward(float distance, float speed)  { return -1; } // DO NOTHING 
float left(float distance, float speed)  { return -1; } // DO NOTHING 
float right(float distance, float speed)  { return -1; } // DO NOTHING 

float forward_seconds(float seconds, float speed)  { return -1; } // DO NOTHING 
float backward_seconds(float seconds, float speed)  { return -1; } // DO NOTHING 
float left_seconds(float seconds, float speed)  { return -1; } // DO NOTHING 
float right_seconds(float seconds, float speed)  { return -1; } // DO NOTHING 

float curve(float left_motor_distance, float left_motor_speed, float right_motor_distance, float right_motor_speed)  { return -1; } // DO NOTHING 
float curve_seconds(float seconds, float left_motor_speed, float right_motor_speed)  { return -1; } // DO NOTHING
*/
