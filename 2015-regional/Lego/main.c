// Created on Thu April 2 2015

#include "legoMovement.h"
#define OPEN 1250
#define CLOSE 460

#define TOPHAT_PORT 5 // Could be any of 0 to 7, your choice (simulator assumes 5 or 6)
#define BLACK_TAPE 400 // This number must be tuned for the actual lighting conditions

void sample_run();

int main()
{
	// sample_run();
	// return 0;
	
	printf("i was made by hannah gabriel and john\n");
	set_servo_position(0,OPEN);
	enable_servos();
	
	lego_drive_distance(FORWARDS, 2100, 150);
	//msleep(2000);
  
	set_servo_position(0,CLOSE);
	lego_spin_degrees(LEFT, 1150, 200);
	//msleep(3000);
	set_servo_position(0,OPEN);
	lego_drive_distance(FORWARDS, 2100, 150);
	//msleep(2000);
	lego_drive_distance(BACKWARDS, 2000, 150);
	lego_spin_degrees(LEFT, 1600, 200);
	lego_drive_distance(FORWARDS, 4000, 150);
	
	ao();
	
	return 0;
	return 0;
}

// Demonstrate the use of the Create movement library.
void sample_run() {
	// Wait briefly to allow user to take finger off the Link.
	msleep(1000);
	
	// Spin somewhat slowly right (clockwise) until the sensor
	// in analog port TOPHAT_PORT sees BLACK_TAPE.  (See #define
	// statements above for TOPHAT_PORT and BLACK_TAPE).
	// Assumes that the sensor is a little tophat (reflectance) sensor
	// placed the "right" distance (per the BLACK_TAPE number) from the surface.
	motor(LEFT_MOTOR, 10);
	motor(RIGHT_MOTOR, -10);
	
	while (TRUE) {
		if (analog(TOPHAT_PORT) >= BLACK_TAPE) {
			break;
		}
	}
	freeze(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
	
	return;
	
	// Lego movement commands start here.
	// Sleeps in between are just so that
	// the user can see the effects of each command.
	
	// Go forwards 2000 ticks at half (50) power.
	lego_drive_distance(FORWARDS, 2000, 50);
	msleep(2000);
	
	// Go backwards 1000 ticks at full (100) power.
	lego_drive_distance(BACKWARDS, 1000, 100);
	msleep(2000);
	
	// Spin left 300 ticks at slow (20) power.
	lego_spin_degrees(LEFT, 300, 20);
	msleep(2000);
	
	// Spin right 1000 ticks at full (100) power.
	lego_spin_degrees(RIGHT, 1000, 100);
	msleep(2000);
}
