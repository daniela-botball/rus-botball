// Created on Sun April 13 2014

#ifndef _TIMING_H_
#define _TIMING_H_

float check_timer(int timer);
void start_timer(int timer);
void end_timer(int timer);
void reset_timer(int timer);

float timers[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};



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

#endif
