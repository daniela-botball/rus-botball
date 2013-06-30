// Created on Sat June 29 2013
#include "timer.h"

void test_timer();

int main()
{
	test_timer();
	return 0;
}

void test_timer()
{
	start_timer();
	msleep(1000);
	printf("%0.8f\n", check_timer());
	msleep(500);
	printf("%0.8f\n", check_timer());
	msleep(1250);
	printf("%0.8f\n", check_timer());
}
