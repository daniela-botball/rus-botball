#include "mc_private_ui_console.h"
#include "mc_interface.h"
#include <ctype.h>

_MC_ACTION action_from_letter[32] = {
	_MC_UNKNOWN_ACTION, // A
	_MC_BACKWARD_ACTION, // B
	_MC_UNKNOWN_ACTION, // C
	_MC_UNKNOWN_ACTION, // D
	_MC_UNKNOWN_ACTION, // E
	_MC_FORWARD_ACTION, // F
	_MC_UNKNOWN_ACTION, // G
	_MC_HELP_ACTION, // H
	_MC_UNKNOWN_ACTION, // I
	_MC_UNKNOWN_ACTION, // J
	_MC_UNKNOWN_ACTION, // K
	_MC_LEFT_ACTION, // L
	_MC_UNKNOWN_ACTION, // M
	_MC_UNKNOWN_ACTION, // N
	_MC_UNKNOWN_ACTION, // O
	_MC_UNKNOWN_ACTION, // P
	_MC_QUIT_ACTION, // Q
	_MC_RIGHT_ACTION, // R
	_MC_UNKNOWN_ACTION, // S
	_MC_UNKNOWN_ACTION, // T
	_MC_UNKNOWN_ACTION, // U
	_MC_UNKNOWN_ACTION, // V
	_MC_UNKNOWN_ACTION, // W
	_MC_UNKNOWN_ACTION, // X
	_MC_UNKNOWN_ACTION, // Y
	_MC_UNKNOWN_ACTION}; // Z

void _mc_show_robot_state_on_console() {
	// TODO
}

_MC_COMMAND _mc_ask_what_to_do_from_console() {
	_MC_COMMAND command;
	char c;
	char c_uppercase;
	int c_as_index;
	
	printf("\n");
	printf("Press a key for what you want to do:\n");
	_mc_do_help(); // FIXME: Make an abbreviated help for here?
	
	while (1) { // ignore whitespace before the command
		c = getchar();
		if (! isspace(c)) {
			break;
		}
	}
	
	c_uppercase = toupper(c);
	c_as_index = (int) (c_uppercase - 'A');
	
	printf("\n");
	
	if (c_uppercase < 'A' || c_uppercase > 'Z' || action_from_letter[c_as_index] == _MC_UNKNOWN_ACTION) {
		printf("ERROR: Bad key! Try again!\n");
		printf("Hint: Press  h  for Help.\n");
	
		return _mc_ask_what_to_do_from_console();
	}
	
	command.action = action_from_letter[c_as_index];
	if (c == 'F' || c == 'B') {
		command.amount = _MC_BIG_LINEAR_AMOUNT;
	} else if (c == 'L' || c == 'R') {
		command.amount = _MC_BIG_SPIN_AMOUNT;
	} else if (c == 'f' || c == 'b') {
		command.amount = _MC_SMALL_LINEAR_AMOUNT;
	} else if (c == 'l' || c == 'r') {
		command.amount = _MC_SMALL_SPIN_AMOUNT;
	} else {
		command.amount = 0;
	}
	
	return command;
}

void _mc_do_help() {
	printf("Your choices are:\n");
	printf("  h H (show this help)\n");
	printf("  q Q (quit move-calibration\n");
	printf("       and continue your program)\n");
	printf("  f F  b B (move forward, backward)\n");
	printf("  l L  r R (spin left, spin right)\n");
	// printf("  s (move servo)       m (turn motor on)\n");
	// FIXME:  Above also goes to servoS and motorS?? They make CURVE?
	// printf("  c (CAMERA SOMETHING?)\n"); // FIXME
}
