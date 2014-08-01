#include "mc_private_adjust.h"
#include "mc_private_ui_console.h"
#include "mc_private_ui_graphical.h"
#include "mc_movements.h"

// FIXME: Need to have public setters.
int _MC_INPUT_FROM_CONSOLE = 0;
int _MC_OUTPUT_TO_CONSOLE = 0;
int _MC_OUTPUT_TO_GUI = 1;

int _IS_MC_ON;
float _MC_BIG_LINEAR_AMOUNT;
float _MC_SMALL_LINEAR_AMOUNT;
float _MC_BIG_SPIN_AMOUNT;
float _MC_SMALL_SPIN_AMOUNT;

float _MC_SLOW_LINEAR_SPEED;
float _MC_VERY_SLOW_LINEAR_SPEED;
float _MC_SLOW_SPIN_SPEED;
float _MC_VERY_SLOW_SPIN_SPEED;

// FIXME: These parameters are not currently used.  Remove them if that remains the case.
float _mc_adjust(MC_DIRECTION direction_moved, float amount_moved, float speed_at_which_moved, float result_from_move) {
	_MC_COMMAND command;
	
	_mc_repeat_command(); // FIXME -- need the command!
		
	while (1) {
		_mc_show_robot_state();
		command = _mc_ask_what_to_do(direction_moved);
		if (command.action == _MC_QUIT_ACTION) {
			_mc_summarize();
			return 1.0;  // Stub.  FIXME.
		}
		_mc_do_it(command);
		_mc_summarize(); // CONSIDER: Maybe should be different from summary presented at the end.
	}
	return 1.0; // Stub.  FIXME.
}

void _mc_repeat_command() { // FIXME -- need the command!
	printf("\n");
	printf("*** Entering Move Calibration. ***\n");
}

void _mc_show_robot_state() {
	if (_MC_OUTPUT_TO_CONSOLE) {
		_mc_show_robot_state_on_console();
	}
	if (_MC_OUTPUT_TO_GUI) {
		_mc_show_robot_state_on_gui();
	}
	// CONSIDER: Should it be an ELSE above?
}

_MC_COMMAND _mc_ask_what_to_do(MC_DIRECTION direction) {
	if (_MC_INPUT_FROM_CONSOLE) {
		return _mc_ask_what_to_do_from_console();
	} else {
		return _mc_ask_what_to_do_from_gui(direction);
	}
}

void _mc_summarize() {
	// TODO
}

void _mc_do_it(_MC_COMMAND command) {
	printf("You asked to: %i with amount %i.\n", command.action, command.amount);
	real_move(command.action, command.amount, command.number);
}
