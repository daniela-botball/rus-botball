#include "utilities.h"
#include "ui.h"
#include "score_8_plus_8.h"
#include "mc_interface.h"
// FIXME: Talk with Aaron re why these are VARIABLEs and use of EXTERN elsewhere.
//        And why they are defined here and not in a .h file.

/*
run diagnostic
choose strategy from menu - 2 main strategies, 1 quickstart strategy, up to 2 extra strategies, menu with more strategies
	button press returns a pair of functions - one for setup and one for main
asks for tournament mode or practice mode or variations on said modes (i.e. with/without lights, with/without timelimit, etc.)
runs setup
lights (if in tournament mode)
*/

int _ROBOT;
int _MODE;
char _STRATEGY[100]; // WARNING: If the strategy string exceeds this size, bad things happen!
int _OUR_COLOR;
int _THEIR_COLOR;

void setup() {
	// FIXME: Work with Aaron to make this use _STRATEGY and hence be robot-neutral.
	setup_score_8_plus_8_poms_in_upper_storage();
	press_a_to_continue();
}

void run() {
	// FIXME: Work with Aaron to make this use _STRATEGY and hence be robot-neutral.
	score_8_plus_8_poms_in_upper_storage();
}

void teardown() {
	// FIXME: Work with Aaron to make this use _STRATEGY and hence be robot-neutral.
}



int map(int n, int old_min, int old_max, int new_min, int new_max) {
	float old_range = (float) (old_max - old_min);
	float new_range = (float) (new_max - new_min);
	return ((int) (((float) n / old_range) * new_range)) + new_min;
}

int compare(int n_one, int n_two, int comparator) {
	int larger;
	int smaller;
	if (n_one > n_two) {
		larger = n_one;
		smaller = n_two;
	} else if (n_one == n_two) {
		smaller = n_one;
		larger = n_one;
	} else {
		larger = n_two;
		smaller = n_one;
	}
	switch (comparator) {
		case LARGER: 
			return larger;
		case SMALLER:
			return smaller;
		default:
			return smaller;
	}
}
