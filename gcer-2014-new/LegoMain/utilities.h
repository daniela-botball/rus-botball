// Created on Sun June 22 2014
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#define TOURNAMENT 0
#define PRACTICE 1

#define LEGO 0
#define CREATE 1

#define TRUE 1
#define FALSE 0

#define LARGER 0
#define SMALLER 1
#define EQUAL 2

void setup();
void run();
void teardown();

// FIXME: Many of these belong elsewhere.
void move_servo_slowly(int port, int position);
void move_servo_very_slowly(int port, int position);
int map(int n, int old_min, int old_max, int new_min, int new_max);
int compare(int n_one, int n_two, int comparator);
void press_A_to_continue();

#endif
