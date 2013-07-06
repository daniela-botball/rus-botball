// Created on Sun April 14 2013

#ifndef _RUS_UNIVERSAL_LIBRARY_H_
#define _RUS_UNIVERSAL_LIBRARY_H_

#define LEFT 1
#define RIGHT -1
#define FORWARDS 1
#define BACKWARDS -1

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

#define sleep(seconds) msleep(seconds * 1000)

#define DEFAULT_ERROR_MESSAGE_LINE 6
#define BLANK_LINE "                                          "
#define HANDS_OFF  "Hands off!                                "
#define MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF 500

typedef enum {NO_BUTTON, A_BUTTON, B_BUTTON, C_BUTTON, X_BUTTON, Y_BUTTON, Z_BUTTON} Button;
typedef enum {TOURNAMENT_RUN, PRACTICE_RUN, PRACTICE_RUN_WITH_LIGHTS} TypeOfRun;
typedef enum {CREATE, LEGO} Robot;

Robot _ROBOT;
TypeOfRun _TYPE_OF_RUN = PRACTICE_RUN;
int _SKIP_PRESS_A_TO_CONTINUE = FALSE;
int _WAIT_FOR_LIGHTS = FALSE;
int _DISPLAY_PRINTF_MODE = FALSE;
int _ERROR_MESSAGE_LINE = DEFAULT_ERROR_MESSAGE_LINE;

void press_A_to_continue();
int button_pressed();
void hands_off(Button button);
void show_message(char* message);

void press_A_to_continue()
{
	if (! _SKIP_PRESS_A_TO_CONTINUE) {
		show_message("Press the A button to continue.");
		while (! a_button()) ; // Wait for A button to be pressed
		hands_off(A_BUTTON);
	}
}

// If a button is currently pressed:
//    -- Tells the user she can take her hand off of the button.
//    -- Waits for the user to take her hand off of the button.
//    -- Waits a bit more for the user to get her hand away from the Link.
//    -- Returns the button that was pressed.
// If no button is currently pressed, returns NO_BUTTON.
int button_pressed() {
	if (a_button()) { hands_off(A_BUTTON); return A_BUTTON; }
	if (b_button()) { hands_off(B_BUTTON); return B_BUTTON; }
	if (c_button()) { hands_off(C_BUTTON); return C_BUTTON; }
	if (x_button()) { hands_off(X_BUTTON); return X_BUTTON; }
	if (y_button()) { hands_off(Y_BUTTON); return Y_BUTTON; }
	if (z_button()) { hands_off(Z_BUTTON); return Z_BUTTON; }
	
	return NO_BUTTON;
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
	msleep(MILLISECONDS_TO_WAIT_AFTER_HANDS_OFF);
}

void show_message(char* message) {
	if (_DISPLAY_PRINTF_MODE) {
		display_printf(0, _ERROR_MESSAGE_LINE, message);
	} else {
		printf(message);
		printf("\n");
	}
}

#endif
