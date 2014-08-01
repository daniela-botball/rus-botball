// Created on Tue May 20 2014

#include "movement.h"
#include "createMovement.h"
#include "teleoperation.h"

#define LEFT_KEY 129
#define UP_KEY 130
#define RIGHT_KEY 131
#define SPOT_KEY 132
#define MAX_KEY 133
#define P_KEY 138
#define CLEAN_KEY 136
#define PAUSE_KEY 137

#define REMOTE_SPEED 100

void teleoperate() {
	int ir_reading;
	while (1) {
		ir_reading = create_get_sensor(17);
		if (ir_reading == LEFT_KEY) {
			create_spin(REMOTE_SPEED, LEFT);
			while (ir_reading == LEFT_KEY) {
				ir_reading = create_get_sensor(17);
			}
			create_stop();
		} if (ir_reading == RIGHT_KEY) {
			create_spin(REMOTE_SPEED, RIGHT);
			while (ir_reading == RIGHT_KEY) {
				ir_reading = create_get_sensor(17);
			}
			create_stop();
		}
		if (ir_reading == UP_KEY) {
			create_drive(REMOTE_SPEED, FORWARDS);
			while (ir_reading == UP_KEY) {
				ir_reading = create_get_sensor(17);
			}
			create_stop();
		}
		if (ir_reading == PAUSE_KEY) {
			return;
		}
	}
}
