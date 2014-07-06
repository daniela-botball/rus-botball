#include "ui.h"
#include "utilities.h"

extern int _MODE;

int confirm_selection(int message_line_number) {
	set_a_button_text("Yes");
	set_b_button_text("No");
	display_printf(0, message_line_number, "Please confirm your selection");
	while (1) {
		if (a_button()) {
			while (a_button());
			display_printf(0, message_line_number + 1, "Selection confirmed");
			msleep(100);
			return 1;
		}
		if (b_button()) {
			while (b_button());
			display_printf(0, message_line_number + 1, "Selection canceled");
			msleep(100);
			return 0;
		}
	}
}

void get_mode() {
	display_clear();
	display_printf(0, 0, "Select mode");
	set_a_button_text("PRACTICE");
	set_b_button_text("TOURNAMENT");
	while (1) {
		if (a_button()) {
			msleep(200);
			set_mode(PRACTICE);
			if (confirm_selection(1)) {
				break;
			} else {
				display_clear();
				display_printf(0, 0, "Select mode");
				set_a_button_text("PRACTICE");
				set_b_button_text("TOURNAMENT");
				#undef _MODE
				continue;
			}
		}
		if (b_button()) {
			msleep(200);
			set_mode(TOURNAMENT);
			if (confirm_selection(1)) {
				break;
			} else {
				display_clear();
				display_printf(0, 0, "Select mode");
				set_a_button_text("PRACTICE");
				set_b_button_text("TOURNAMENT");
				#undef _MODE
				continue;
			}
		}
	}
}

void get_robot() {
	display_clear();
	display_printf(0, 0, "Select robot running");
	set_a_button_text("LEGO");
	set_b_button_text("CREATE");
	while (1) {
		if (a_button()) {
			while(a_button());
			msleep(200);
			#define _ROBOT LEGO
			display_printf(0, 0, "The LEGO robot has been selected");
			if (confirm_selection(1)) {
				break;
			} else {
				display_clear();
				display_printf(0, 0, "Select robot running");
				set_a_button_text("LEGO");
				set_b_button_text("CREATE");
				#undef _ROBOT
				continue;
			}
			break;
		}
		if (b_button()) {
			while(b_button());
			msleep(200);
			#define _ROBOT CREATE
			display_printf(0, 0, "The CREATE robot has been selected");
			if (confirm_selection(1)) {
				break;
			} else {
				display_clear();
				display_printf(0, 0, "Select robot running");
				set_a_button_text("LEGO");
				set_b_button_text("CREATE");
				#undef _ROBOT
				continue;
			}
			break;
		}
	}
	msleep(2000);
}

void press_a_to_continue() {
	if (_MODE == PRACTICE) {
		printf("Press 'a' to continue, 'c' to adjust.\n");
		while (1) {
			if (a_button()) {
				while (a_button());
				msleep(500);
				break;
			}
			if (c_button()) {
				while (c_button());
				msleep(500);
				//adjust();
				break;
			}
		}
	} else {
		msleep(SLEEP_MSECONDS_IN_TOURNAMENT_MODE);
	}
}

void set_mode(int mode) {
	#ifdef __MODE
	#undef __MODE
	#define __MODE mode
	#else
	#define __MODE mode
	#endif
}
