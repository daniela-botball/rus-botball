 /*
 * Library for movement that is shared by Lego and Create robots.
 *
 * Functions:
 *   int direction_multiplier(Direction direction)
 
 * Prerequisite:  the user must have set the robot 
 all these functions work for both
 *
 * Global variables:
 *   Robot   _ROBOT;
 *   RunMode _MODE;
 *
 * Enumerations:
 *   Boolean (TRUE, FALSE)
 *   Direction (FORWARDS, BACKWARDS, LEFT, RIGHT)
 *   RunMode (TOURNAMENT_MODE, PRACTICE_MODE)
 *   Robot (LEGO, CREATE)
 *   Status (SUCCESS, FAILURE)
 *
 * Macros:
 *   sleep(seconds) // argument can be a float
 *
 * Authors: Aaron Mutchler and team, based on code written
 *          by Seth Mutchler and others.  Summer 2013.
 */
#ifndef _RUS_MOVEMENT_LIBRARY_H_
#define _RUS_MOVEMENT_LIBRARY_H_

#define RAMP_BEGIN_SPEED 20 // 100 is full power
#define RAMP_END_SPEED   80 //
#define RAMP_TIME 2 // seconds

int direction_multiplier(Direction direction);
int ramp(int speed, Direction direction);
int ramp_distance(float distance, int speed, Direction direction);

/*********************************************************************
 * int direction_multiplier(Direction direction)
 *   Returns FORWARDS_LEFT (1) if the direction is forwards or left,
 *   else returns BACKWARDS_RIGHT (-1).
 ********************************************************************/
int direction_multiplier(Direction direction) {
    return (direction == FORWARDS || direction == LEFT) ?
		FORWARDS_LEFT : BACKWARDS_RIGHT;
}

int ramp(int speed, Direction direction) {
    
}

int ramp_distance(float distance, int speed, Direction direction) {
}

#endif
