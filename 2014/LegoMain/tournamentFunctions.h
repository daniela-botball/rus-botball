// Created on Fri June 13 2014

#ifndef _TOURNAMENTFUNCTIONS_H_
#define _TOURNAMENTFUNCTIONS_H_

#define TRACK_MOTOR 0

#define ltrack_off() off(L_TRACK_MOTOR)
#define rtrack_off() off(R_TRACK_MOTOR)

#define TRUE 1

#define CLAW_OPEN_POSITION 104
#define CLAW_CLOSED_POSITION 1114
#define CLAW_SERVO 0

#define SERVO_INCREMENT 7

void track_on();
void move_servo_slowly(int port, int position);

#endif
