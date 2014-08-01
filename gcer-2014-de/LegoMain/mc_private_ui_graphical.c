#include "mc_private_ui_graphical.h"
#include "mc_interface.h"

void _mc_show_robot_state_on_gui() {
	// TODO
}

_MC_COMMAND _mc_ask_what_to_do_from_gui(MC_DIRECTION direction) {
	if (direction == MC_FORWARD || direction == MC_BACKWARD) {
		linear_movement_buttons();
		return get_menu_1_action();
	}
	else {
		spin_movement_buttons();
		return get_menu_2_action();
	}
}

void linear_movement_buttons() {
	extra_buttons_show();
	set_a_button_text("FWD");
	set_b_button_text("fwd");
	set_c_button_text("Continue");
	set_x_button_text("BWD");
	set_y_button_text("bwd");
	set_z_button_text("Switch");
}

void spin_movement_buttons() {
	extra_buttons_show();
	set_a_button_text("LEFT");
	set_b_button_text("RIGHT");
	set_c_button_text("Continue");
	set_x_button_text("left");
	set_y_button_text("right");
	set_z_button_text("Switch");
}

void reset_buttons() {
	extra_buttons_show();
	set_a_button_text("A");
	set_b_button_text("B");
	set_c_button_text("C");
	set_x_button_text("X");
	set_y_button_text("Y");
	set_z_button_text("Z");
	extra_buttons_hide();
}

_MC_COMMAND get_menu_1_action() {
	_MC_COMMAND command;
	BUTTON button = get_button();
	if (button == A_BUTTON) {
		command.action = _MC_FORWARD_ACTION;
		command.amount = _MC_BIG_LINEAR_AMOUNT;
		command.number = _MC_SLOW_LINEAR_SPEED;
	} else if (button == B_BUTTON) {
		command.action = _MC_FORWARD_ACTION;
		command.amount = _MC_SMALL_LINEAR_AMOUNT;
		command.number = _MC_VERY_SLOW_LINEAR_SPEED;
	} else if (button == C_BUTTON) {
		command.action = _MC_QUIT_ACTION;
	} else if (button == X_BUTTON) {
		command.action = _MC_BACKWARD_ACTION;
		command.amount = _MC_BIG_LINEAR_AMOUNT;
		command.number = _MC_SLOW_LINEAR_SPEED;
	} else if (button == Y_BUTTON) {
		command.action = _MC_BACKWARD_ACTION;
		command.amount = _MC_SMALL_LINEAR_AMOUNT;
		command.number = _MC_VERY_SLOW_LINEAR_SPEED;
	} else if (button == Z_BUTTON) {
		command.action = _MC_FORWARD_ACTION;
		command.amount = 0;
		command.number = 10; // FIXME
	}
	return command;
}

_MC_COMMAND get_menu_2_action() {
	_MC_COMMAND command;
	BUTTON button = get_button();
	if (button == A_BUTTON) {
		command.action = _MC_LEFT_ACTION;
		command.amount = _MC_BIG_SPIN_AMOUNT;
		command.number = _MC_SLOW_SPIN_SPEED;
	} else if (button == B_BUTTON) {
		command.action = _MC_RIGHT_ACTION;
		command.amount = _MC_BIG_SPIN_AMOUNT;
		command.number = _MC_SLOW_SPIN_SPEED;
	} else if (button == C_BUTTON) {
		command.action = _MC_QUIT_ACTION;
	} else if (button == X_BUTTON) {
		command.action = _MC_LEFT_ACTION;
		command.amount = _MC_SMALL_SPIN_AMOUNT;
		command.number = _MC_VERY_SLOW_SPIN_SPEED;
	} else if (button == Y_BUTTON) {
		command.action = _MC_RIGHT_ACTION;
		command.amount = _MC_SMALL_SPIN_AMOUNT;
		command.number = _MC_VERY_SLOW_SPIN_SPEED;
	} else if (button == Z_BUTTON) {
		command.action = _MC_FORWARD_ACTION;
		command.amount = 0;
		command.number = 10; // FIXME
	}
	return command;
}

BUTTON get_button() {
	while (1) {
		if (a_button()) {
			while (a_button());
			msleep(HANDS_OFF_MSECONDS);
			return A_BUTTON;
		} 
		if (b_button()) {
			while (b_button());
			msleep(HANDS_OFF_MSECONDS);
			return B_BUTTON;
		}
		if (c_button()) {
			while (c_button());
			msleep(HANDS_OFF_MSECONDS);
			return C_BUTTON;
		}
		if (x_button()) {
			while (x_button());
			msleep(HANDS_OFF_MSECONDS);
			return X_BUTTON;
		}
		if (y_button()) {
			while (y_button());
			msleep(HANDS_OFF_MSECONDS);
			return Y_BUTTON;
		}
		if (z_button()) {
			while (z_button());
			msleep(HANDS_OFF_MSECONDS);
			return Z_BUTTON;
		}
	}
	
}
