#ifndef _MC_PRIVATE_UI_GRAPHICAL_H_
#define _MC_PRIVATE_UI_GRAPHICAL_H_

#include "mc_private_adjust.h"
#include "mc_interface.h"

#define HANDS_OFF_MSECONDS 200

typedef enum {A_BUTTON, B_BUTTON, C_BUTTON, X_BUTTON, Y_BUTTON, Z_BUTTON} BUTTON;

void _mc_show_robot_state_on_gui();
_MC_COMMAND _mc_ask_what_to_do_from_gui(MC_DIRECTION direction);
void linear_movement_buttons();
void spin_movement_buttons();
void reset_buttons();
_MC_COMMAND get_menu_1_action();
_MC_COMMAND get_menu_2_action();
BUTTON get_button();

#endif
