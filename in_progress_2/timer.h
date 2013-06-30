// Created on Tue May 7 2013

#ifndef _RUS_TIMER_H_
#define _RUS_TIMER_H_

float TIME;
int TIME2;

void timer();
void start_timer();
float check_timer();
void reset_timer();
int check_timer2();


void start_timer()
{
	reset_timer();
	thread timer_thread;
	TIME = seconds();
	//timer_thread = thread_create(timer);
	//thread_start(timer_thread);
}

float check_timer()
{
	double current_time;
	current_time = seconds() - TIME;
	return current_time;
}

int check_timer2()
{
	return TIME2;
}

void reset_timer()
{
	TIME = 0.0;
}

void timer() {
	while (1) {
		msleep(100);
		++TIME2;
	}
}

#endif
