/*
 * RUN the Camera numbers utility (that shows all the numbers
 * for the biggest blobs of the selected color_model).
 *
 * Written by Aaron and David Mutchler, June 2013.
 */

// CONSIDER: Change the following when the libraries move.
#include "in_progress_2/camera_library.h"
#include "in_progress_2/universal_library.h"

#define CLAW_SERVO_START_POSITION 1240
#define JOINT_SERVO_START_POSITION 1900
#define ARM_SERVO_START_POSITION 761
#define CAMERA_PICKUP_BOOSTER_POSITION 1110

#define CLAW_SERVO 0
#define ARM_SERVO 1
#define JOINT_SERVO 2
#define CAMERA_SERVO 3
#define BOOSTER_MOTOR 1
#define GATE_MOTOR 2

int main() {
	int status;
	set_servo_position(CLAW_SERVO, CLAW_SERVO_START_POSITION);
	set_servo_position(JOINT_SERVO, JOINT_SERVO_START_POSITION);
	set_servo_position(ARM_SERVO, ARM_SERVO_START_POSITION);
	set_servo_position(CAMERA_SERVO, CAMERA_PICKUP_BOOSTER_POSITION);
	enable_servos();
	
	status = initialize_camera(LOW_RES);
	if (status == FAILURE) return 1;
	
	app_to_display_blob_numbers();
	
	return 0;
}

void spin_left_for_camera_search(int speed) {}
void spin_right_for_camera_search(int speed) {}
void move_backwards_for_camera_search(int speed) {}
void move_forwards_for_camera_search(int speed) {}
void stop_camera_search() {}
