// Created on Tue May 7 2013

#ifndef _RUS_TIMER_H_
#define _RUS_TIMER_H_

int TIME;
int TIME2;

void timer();

void start_timer()
{
	thread timer_thread;
	TIME = seconds();
	timer_thread = thread_create(timer);
	thread_start(timer_thread);
}

int check_timer()
{
	double current_time;
	current_time = seconds() - TIME;
	return (int) current_time;
}

int check_timer2()
{
	return TIME2;
}

void reset_timer()
{
	TIME = 0;
}

void timer() {
	while (1) {
		msleep(100);
		++TIME2;
	}
}

#endif
