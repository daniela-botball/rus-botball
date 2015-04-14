#include "utilities.h"
#include "tests.h"
#include <string.h>

extern int _ROBOT;
extern int _MODE;
extern char _STRATEGY[];

int main() {
	_ROBOT = LEGO;
	_MODE = PRACTICE;
	strcpy(_STRATEGY, "score_8_plus_8_poms_in_upper_storage");
	
	setup();
	run();
	teardown();
	
	return 0;
}





