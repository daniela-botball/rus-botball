#include "movement.h"
#include "createMovement.h"
#include "moveCalibration.h"
void move_until_line() {
	create_drive(100, FORWARDS);
	while (get_create_rfcliff_amt() > CREATE_THRESHOLD) {
		display_printf(0, 0, "%4i", get_create_rfcliff_amt());
	}
	create_stop();
}

void move_until_line_old() {
	create_drive(100, FORWARDS);
	while (analog10(BLACK_LINE_SENSOR) < THRESHOLD);
	create_stop();
}

void create_drive_until_bump(int speed) {
	create_drive(speed, FORWARDS);
	write_byte(158);
	write_byte(5);
	create_stop();
	while (get_create_mode(0.1) > 5) {
		msleep(1);
	}
}

void move_until_bump(int speed, int direction, int port) {
	create_drive(speed, direction);
	while (!digital(port));
	create_stop();
}

void create_virtual_bump(int speed, int direction) {
	create_drive(speed, direction);
	while (create_get_sensor(CURRENT) > CURRENT_THRESHOLD) {
		//msleep(20);
	}
	create_stop();
}

void robot_drive_distance(float distance, float speed, int direction) {
	#if _ROBOT == CREATE
	create_drive_distance(distance, speed, direction);
	#elif _ROBOT == LEGO
	//lego_drive_distance();
	#endif
}
