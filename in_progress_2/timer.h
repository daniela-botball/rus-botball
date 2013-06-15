// Created on Tue May 7 2013

// Replace FILE with your file's name
#ifndef _TIMER_H_
#define _TIMER_H_
int TIME;

void start_timer()
{
	TIME = seconds();
}

int check_timer()
{
	double current_time;
	current_time = seconds() - TIME;
	return (int) current_time;
}

void reset_timer()
{
	TIME = 0;
}


#endif
