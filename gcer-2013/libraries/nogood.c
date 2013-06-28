/*
 * Tests that the libraries compile successfully.
 *
 */

#include "universal_library.h"
#include "gui_library.h"

extern Robot _ROBOT;

//_ROBOT = CREATE;
//_ROBOT = ANY;

int main()
{
    // Test each of the following:
    _ROBOT = CREATE;
	_ROBOT = LEGO;
    //_ROBOT = ANY;

	printf("Testing that all the libraries compile OK.\n");
	
	return 0;
}
