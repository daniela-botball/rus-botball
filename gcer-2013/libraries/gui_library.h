 /*********************************************************************
 * Library for enhancing the KISS GUI.
 *
 * Enumerations:
 *   Buttton (A_BUTTON, B_BUTTON, C_BUTTON, X_BUTTON, Y_BUTTON, Z_BUTTON, NO_BUTTON)
 *
 * Functions:
 *   void show_message(char* message)
 *   void show_another_message(char* message)
 *   void show_message_on_line(char* message, int line)
 *
 *   void press_A_to_continue()
 *   void always_press_A_to_continue()
 *
 *   Button which_button_is_pressed()
 *   Button wait_for_button_press()
 *   void hands_off(Button button)
 *
 *   skip_press_A_to_continue(Boolean true_or_false)
 *   use_display_printf(Boolean true_or_false)
 *   set_first_message_line(int line)
 *   set_second_message_line(int line)
 *
 * Constants:
 *   BLANK_LINE (for display_printf)
 *   HANDS_OFF  (for display_printf)
 *   DEFAULT_FIRST_MESSAGE_LINE, DEFAULT_SECOND_MESSAGE_LINE
 *   DEFAULT_MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF
 *
 * Global variables (used for dynamic control of the functions above)
 *   Boolean _SKIP_PRESS_A_TO_CONTINUE
 *   Boolean _USE_DISPLAY_PRINTF
 *   int _FIRST_MESSAGE_LINE, _SECOND_MESSAGE_LINE
 *
 * Authors: Aaron Mutchler and team, based on code written
 *          by Seth Mutchler and others.  Summer 2013.
 ********************************************************************/

#ifndef _RUS_GUI_LIBRARY_H_
#define _RUS_GUI_LIBRARY_H_

#include "../libraries/universal_library.h"

typedef enum {NO_BUTTON, A_BUTTON, B_BUTTON, C_BUTTON, X_BUTTON, Y_BUTTON, Z_BUTTON} Button;

#define DEFAULT_FIRST_MESSAGE_LINE  6
#define DEFAULT_SECOND_MESSAGE_LINE 7
#define BLANK_LINE "                                          "
#define HANDS_OFF  "Hands off!                                "
#define DEFAULT_MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF 200

Boolean _SKIP_PRESS_A_TO_CONTINUE = FALSE;
Boolean _USE_DISPLAY_PRINTF = FALSE;
int _FIRST_MESSAGE_LINE = DEFAULT_FIRST_MESSAGE_LINE;
int _SECOND_MESSAGE_LINE = DEFAULT_SECOND_MESSAGE_LINE;
int _MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF = DEFAULT_MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF;

/*********************************************************************
 * press_A_to_continue()
 *   Shows a message telling the user to "Press A to continue"
 *   Then waits for the user to press the A button,
 *   then does "Hands off!" as described below.
 *   BUT: if  _SKIP_PRESS_A_TO_CONTINUE  is TRUE, does NOTHING.
 ********************************************************************/

/*********************************************************************
 * always_press_A_to_continue()
 *   Same as  press_A_to_continue  above, but ALWAYS waits for A
 *   (even if  _SKIP_PRESS_A_TO_CONTINUE  is TRUE).
 ********************************************************************/
 
/*********************************************************************
 * which_button_is_pressed()
 *   Returns which button is currently pressed (A_BUTTON, B_BUTTON, ...),
 *   or NO_BUTTON if no button is currently pressed.
 *   Also does the "Hands off!" message to the user as described below
 *   if a button is pressed.
 ********************************************************************/

 /********************************************************************
 * show_message(char* message)
 *   Displays the given message using  display_printf  or   printf,
 *   depending on the status of global variable _USE_DISPLAY_PRINTF.
 *   If it uses display_printf, puts the message onto the line
 *   specified by global variable _FIRST_MESSAGE_LINE.
 ********************************************************************/
 
 /********************************************************************
 * show_another_message(char* message)
 *   Same as show_message, but uses _SECOND_MESSAGE_LINE
 *   when using display_printf.
 ********************************************************************/
 
 /********************************************************************
 * show_message_on_line(char* message, int line)
 *   Same as show_message, but uses the given line
 *   when using display_printf.
 ********************************************************************/
 
/*********************************************************************
 * wait_for_button_press()
 *   Waits for the user to press a button and returns which button
 *   was pressed (A_BUTTON, B_BUTTON, ...).  Also does the
 *   "Hands off!" message to the user as described below.
 ********************************************************************/

/*********************************************************************
 * hands_off(Button button)
 *   Tells the user she can take her hand off of the button.
 *   Then waits for the user to take her hand off of the given button.
 *   Then waits a bit more for the user to get her hand away from the Link.
 ********************************************************************/

/*********************************************************************
 * skip_press_A_to_continue(Boolean b)
 *   Sets the global constant  _SKIP_PRESS_A_TO_CONTINUE  to the
 *   given value (TRUE or FALSE).
 ********************************************************************/

 /*********************************************************************
 * use_display_printf(Boolean b)
 *   Sets the global constant  _USE_DISPLAY_PRINTF  to the given value
 *   (TRUE or FALSE).
 ********************************************************************/
 
 /*********************************************************************
 * set_first_message_line(Boolean b)
 *   Sets the global constant  _FIRST_MESSAGE_LINE  to the given value
 *   (an integer that should be between 0 and 8 or so).
 ********************************************************************/
 
 /*********************************************************************
 * set_second_message_line(Boolean b)
 *   Sets the global constant  _SECOND_MESSAGE_LINE  to the given value
 *   (an integer that should be between 0 and 8 or so).
 ********************************************************************/
 
void show_message(char* message);
void show_another_message(char* message);
void show_message_on_line(char* message, int line);

void press_A_to_continue();
void always_press_A_to_continue();

Button which_button_is_pressed();
Button wait_for_button_press();
void hands_off(Button button);

void skip_press_A_to_continue(Boolean b);
void use_display_printf(Boolean b);
void set_first_message_line(int line);
void set_second_message_line(int line);
 
/* Function definitions start here. */

void show_message(char* message) {
	show_message_on_line(message, _FIRST_MESSAGE_LINE);
}

void show_another_message(char* message) {
	show_message_on_line(message, _SECOND_MESSAGE_LINE);
}

void show_message_on_line(char* message, int line) {
    if (_USE_DISPLAY_PRINTF) {
	    display_printf(0, line, BLANK_LINE);
		display_printf(0, line, message);
	} else {
		printf(message);
		printf("\n");
	}

}

void press_A_to_continue() {
	if (! _SKIP_PRESS_A_TO_CONTINUE) {
		show_message("Press the A button to continue.");
		while (! a_button()) ; // Wait for A button to be pressed
		hands_off(A_BUTTON);
	}
}

void always_press_A_to_continue() {
    int skip_state = _SKIP_PRESS_A_TO_CONTINUE;  // Save state
	_SKIP_PRESS_A_TO_CONTINUE = FALSE;
	press_A_to_continue();
	_SKIP_PRESS_A_TO_CONTINUE = skip_state;      // Restore state
}

Button which_button_is_pressed() {
	if (a_button()) { hands_off(A_BUTTON); return A_BUTTON; }
	if (b_button()) { hands_off(B_BUTTON); return B_BUTTON; }
	if (c_button()) { hands_off(C_BUTTON); return C_BUTTON; }
	if (x_button()) { hands_off(X_BUTTON); return X_BUTTON; }
	if (y_button()) { hands_off(Y_BUTTON); return Y_BUTTON; }
	if (z_button()) { hands_off(Z_BUTTON); return Z_BUTTON; }
	
	return NO_BUTTON;
}

Button wait_for_button_press() {
    Button button;
	
    while (TRUE) {
		button = which_button_is_pressed();
		if (button != NO_BUTTON) {
		    return button;
		}
	}
}

void hands_off(Button button) {
	show_message(HANDS_OFF);
	
	// Wait for the user to release the button.
	switch (button) {
		case A_BUTTON: while (a_button()); break;
		case B_BUTTON: while (b_button()); break;
		case C_BUTTON: while (c_button()); break;
		case X_BUTTON: while (x_button()); break;
		case Y_BUTTON: while (y_button()); break;
		case Z_BUTTON: while (z_button()); break;
	}
	
	show_message(BLANK_LINE);
	msleep(_MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF);
}

void skip_press_A_to_continue(Boolean b) {
    _SKIP_PRESS_A_TO_CONTINUE = b;
}

void use_display_printf(Boolean b) {
    _USE_DISPLAY_PRINTF = b;
}

void set_first_message_line(int line) {
    _FIRST_MESSAGE_LINE = line;
}

void set_second_message_line(int line) {
    _SECOND_MESSAGE_LINE = line;
}

#endif
