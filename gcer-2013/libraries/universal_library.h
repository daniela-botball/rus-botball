 /*
 * Library with global variables, constants, enumerations and macros:
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
#ifndef _RUS_UNIVERSAL_LIBRARY_H_
#define _RUS_UNIVERSAL_LIBRARY_H_

typedef enum {TRUE = 1, FALSE = 0} Boolean;
typedef enum {FORWARDS, BACKWARDS, LEFT, RIGHT, FORWARDS_LEFT = 1, BACKWARDS_RIGHT = -1} Direction;
typedef enum {TOURNAMENT_MODE, PRACTICE_MODE} RunMode;
typedef enum {LEGO, CREATE, ANY} Robot;
typedef enum {SUCCESS = 1, FAILURE = 0, NORMAL_EXIT = 0, ABNORMAL_EXIT = 1} Status;

Robot _ROBOT;
RunMode _MODE;

#define sleep(seconds) msleep((int) ((seconds * 1000) + 0.5))

#endif

