// Created on Sat April 11 2015

// Replace FILE with your file's name
#ifndef _TOURNAMENTFUNCTIONS_H_
#define _TOURNAMENTFUNCTIONS_H_


#define WINCH_MOTOR 3

#define CLAW_SERVO 0

#define WINCH_LEVER 8

#define CLAW_CLOSE_POSITION 1000
#define CLAW_OPEN_POSITION 2000

#define WINCH_GROUND_POSITION 2600 //was 530, then 930, was 1130
#define WINCH_MIDDLE_POSITION 1700 //was 330, then 630, then 930
#define WINCH_DROP_POSITION 0

void operate_winch(int position);
void open_claw();
void close_claw();
void raise_winch();

#endif
