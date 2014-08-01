#include "movement.h"
#include "legoMovement.h"
#include "mc_interface.h"
#include "de.h"

void block_botguy() {
	int base_speed = 90;
	int lspeed = base_speed;
	int rspeed = base_speed;
	int center_of_botguy;
	clear_motor_position_counter(LEFT_MOTOR);
	while (get_motor_position_counter(LEFT_MOTOR) < DISTANCE_TO_BOTGUY) {
		camera_update();
		center_of_botguy = get_object_center(RED, 0).x;
		display_clear();
		if (center_of_botguy == -1) {
			display_printf(0, 0, "Botguy not visible!\n");
		} else if (center_of_botguy > 60 + CAMERA_DELTA) {
			lspeed += 2;
			display_printf(0, 0, "Turning right!     ");
		} else if (center_of_botguy < 60 - CAMERA_DELTA) {
			rspeed += 3;
			display_printf(0, 0, "Turning left!     ");
		} else if (center_of_botguy >= 60 - CAMERA_DELTA && center_of_botguy <= 60 + CAMERA_DELTA) {
			lspeed = base_speed;
			rspeed = base_speed;
			display_printf(0, 0, "Going straight!     ");
		}
		 
		if (rspeed == 100 || lspeed == 100) {
			rspeed -= 10;
			lspeed -= 10;
		}
		motor(LEFT_MOTOR, lspeed);
		motor(RIGHT_MOTOR, rspeed);
	}
	ao();
	set_servo_position(0, 1250);
}

void block_small_cubes() {}
void block_hangers() {
	block_botguy();
	lego_drive_distance(20, 80, FORWARDS);
	lego_spin_degrees(3600, 100, LEFT);
}

void block_poms() {
	block_botguy();
	lego_drive_distance(50, 80, FORWARDS);
	lego_spin_degrees(70, 80, LEFT);
	lego_drive_distance(80, 100, FORWARDS);
	lego_spin_degrees(3600, 100, LEFT);
}
