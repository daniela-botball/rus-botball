#include "tournamentFunctions.h"
#include "legoMovement.h"
#include "movement.h"
#include "moveCalibration.h"
#include "timing.h"
#include "ui.h"
#include "tests.h"

int get_ticks_per_rotation(int motor) {
	clear_motor_position_counter(motor);
	display_printf(0, 0, "Spin the motor %d 360 degrees", motor);
	set_a_button_text("Done");
	int ticks;
	while (!a_button()) {
		ticks = get_motor_position_counter(motor);
		display_printf(0, 1, "ticks: %4d", ticks);
	}
	display_clear();
	display_printf(0, 0, "There are %d ticks per rotation", ticks);
	display_printf(0, 1, "on motor %d", motor);
	return ticks;
}

