#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

#define TRUE 1
#define FALSE 0

#define CREATE_ROBOT 1
#define LEGO_ROBOT 0

#define TOURNAMENT_MODE 1
#define PRACTICE_MODE 0

#define TOURNAMENT_SLEEP 500

#define CHOICE_EXIT_ADJUST -1
#define CHOICE_BIG_FORWARDS 0
#define CHOICE_BIG_BACKWARD 1
#define CHOICE_BIG_RIGHT 2
#define CHOICE_BIG_LEFT 3
#define CHOICE_SMALL_FORWARDS 4
#define CHOICE_SMALL_BACKWARD 5
#define CHOICE_SMALL_RIGHT 6
#define CHOICE_SMALL_LEFT 7

#define BIG_DRIVE 10
#define SMALL_DRIVE 2
#define BIG_SPIN 30
#define SMALL_SPIN 5

extern int _ROBOT;
extern int _MODE;
extern int _ADJUST;

void set_robot(int robot);
void set_mode(int mode);
void press_a_to_continue();

void adjust(int direction, int amount);
int get_choice(int direction);
void set_buttons_text(int direction);

#endif
