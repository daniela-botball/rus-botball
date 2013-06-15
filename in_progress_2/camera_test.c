#include "camera_library.h"
#include "lego_library.h"
#include "universal_library.h"
int main()
{
	camera_open(LOW_RES);
	set_servo_position(1, 2047);
	enable_servos();
	suck_up_pom();
	arm_down();
	sleep(2);
	arm_up();
	//move_to_y(DESIRED_Y);
}
