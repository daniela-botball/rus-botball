// Created on Sun April 13 2014

#ifndef _TIMING_H_
#define _TIMING_H_

float check_timer(int timer);
void start_timer(int timer);
void end_timer(int timer);
void reset_timer(int timer);

float timers[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

#endif
