#include "timing.h"

void start_timer(int timer) {
	if (timers[timer] == -1) {
		timers[timer] = seconds();
	}
}

float check_timer(int timer) {
	if (timers[timer] == -1) {
		printf("TIMER %i HAS NOT BEEN STARTED\n", timer);
		return -1.0;
	}
	return seconds() - timers[timer];
}

void reset_timer(int timer) {
	timers[timer] = seconds();
}

void end_timer(int timer) {
	timers[timer] = -1;
}
