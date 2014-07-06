#include "utilities.h"
#include "tests.h"
#include <string.h>

// FIXME: Talk with Aaron re why these are VARIABLEs and why EXTERN.
//        And why defined in utilities.h.  And how this file is robot-neutral.

extern int _ROBOT;
extern int _MODE;
extern char _STRATEGY[];

int main() {
	_ROBOT = LEGO;
	_MODE = PRACTICE;
	strcpy(_STRATEGY, "score_8_plus_8_poms_in_upper_storage");
	
	test(); 
	return 1;
	
	setup();
	run();
	teardown();
	
	return 0;
}





