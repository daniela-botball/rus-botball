/*
 * Tests that the libraries compile successfully.
 *
 */

#include "../libraries/all_libraries.h"
#include "../libraries/universal_library.h"
#include "../libraries/gui_library.h"

extern Robot _ROBOT;

int main()
{
    // Test each of the following, one at a time:
    _ROBOT = CREATE;
	_ROBOT = LEGO;
    _ROBOT = ANY;

	printf("Testing that all the libraries compile OK.\n");
	
	return 0;
}
