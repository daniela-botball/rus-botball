#include "movement.h"
#include "legoMovement.h"

void robot_drive_distance(float distance, float speed, int direction) {
	#if _ROBOT == CREATE
	//create_drive_distance(distance, speed, direction);
	#elif _ROBOT == LEGO
	lego_drive_distance(distance, speed, direction);
	#endif
}

void robot_spin_degrees(int degrees, int speed, int direction) {
	#if _ROBOT == CREATE
	//create_spin_degrees(degrees, speed, direction);
	#elif _ROBOT == LEGO
	//lego_spin_degrees(degrees, speed, direction);
	#endif
}

void drive_to_poms(int speed) {
	lego_drive(speed, FORWARDS);
	while (analog10(POM_S_TOPHAT) > SEEING_POMS_THRESHOLD);
	lego_stop();
}
