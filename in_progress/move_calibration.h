// Created on Mon April 8 2013
// Created by Aaron Mutchler
// Idea from Seth Mutchler

#ifndef _MOVE_CALIBRATION_H_
#define _MOVE_CALIBRATION_H_

#include "universal_library.h"
#include "lego_library.h"
#include "create_library.h"
#define CALIBRATION_SPEED 10
#define TURN_CALIBRATION_SPEED 30

int _MODE = TOURNAMENT_MODE;

typedef enum 
{
	A_BUTTON, B_BUTTON, C_BUTTON, X_BUTTON, Y_BUTTON, Z_BUTTON, NONE
} BUTTON;


BUTTON get_button();
float move_calibration(float centimeters, int speed, int direction);
void start_move_calibration_buttons();
void start_turn_calibration_buttons();
void move(float centimeters, int speed, int direction);
void turn(int degrees, int speed, int direction);

float move_calibration(float centimeters, int speed, int direction)
{
	float distance = 0; //Relative to forwards
	BUTTON button;
	
	move(centimeters, speed, direction);
	
	if (_MODE == TOURNAMENT_MODE)
	{
		return centimeters;
	}
	display_clear();
	start_move_calibration_buttons();
	display_printf(0, 0, "Move Calibration");
	if (direction == FORWARDS)
	{
		display_printf(0, 1, "Original - FORWARDS %4.1f", centimeters);
	}
	else
	{
		display_printf(0, 1, "Original - BACKWARDS %4.1f", centimeters);
	}
	while (1)
	{
		button = get_button();
		if (button == NONE)
		{
			continue;
		}
		else if (button == A_BUTTON)
		{
			move(1, CALIBRATION_SPEED, FORWARDS);
			distance++;
		}
		else if (button == B_BUTTON)
		{
			move(5, CALIBRATION_SPEED, FORWARDS);
			distance += 5;
		}
		else if (button == X_BUTTON)
		{
			move(1, CALIBRATION_SPEED, BACKWARDS);
			distance--;
		}
		else if (button == Y_BUTTON)
		{
			move(5, CALIBRATION_SPEED, BACKWARDS);
			distance -= 5;
		}
		else if (button == Z_BUTTON)
		{
			display_printf(0, 2,"New -            %5.1f", centimeters + (direction * distance));
			display_printf(0, 4, "         ");
			return centimeters + (direction * distance);
		}
		display_printf(0, 2,"New -            %5.1f", centimeters + (direction * distance));
		display_printf(0, 4, "         ");
	}	
}

int turn_calibration(int degrees, int speed, int direction)
{
	int distance = 0;
	BUTTON button;
	
	turn(degrees, speed, direction);
	
	if (_MODE == TOURNAMENT_MODE)
	{
		return degrees;
	}
	display_clear();
	start_turn_calibration_buttons();
	display_printf(0, 0, "Turn Calibration");
	if (direction == LEFT)
	{
		display_printf(0, 1, "Original - LEFT %i", degrees);
	}
	else
	{
		display_printf(0, 1, "Original - RIGHT %i", degrees);
	}
	while (1)
	{
		button = get_button();
		if (button == NONE)
		{
			continue;
		}
		else if (button == A_BUTTON)
		{
			turn(5, TURN_CALIBRATION_SPEED, LEFT);
			distance += 5;
		}
		else if (button == B_BUTTON)
		{
			turn(11, TURN_CALIBRATION_SPEED, LEFT);
			distance += 11;
		}
		else if (button == X_BUTTON)
		{
			turn(5, TURN_CALIBRATION_SPEED, RIGHT);
			distance -+ 5;
		}
		else if (button == Y_BUTTON)
		{
			turn(11, TURN_CALIBRATION_SPEED, RIGHT);
			distance -= 11;
		}
		else if (button == Z_BUTTON)
		{
			display_printf(0, 2,"New -            %i", degrees + (direction * distance));
			display_printf(0, 4, "         ");
			return degrees + (direction * distance);
		}
		display_printf(0, 2,"New -            %i", degrees + (direction * distance));
		display_printf(0, 4, "         ");
	}	
}
void move(float centimeters, int speed, int direction)
{
	if (_ROBOT == CREATE)
	{
		create_drive_distance(centimeters, speed, direction);
	}
	else
	{
		lego_drive_distance(centimeters, speed, direction);
	}
}
void turn(int degrees, int speed, int direction)
{
	if (_ROBOT == CREATE)
	{
		create_spin_degrees(degrees, speed, direction);
	}
	else
	{
		lego_spin_degrees(degrees, speed, direction);
	}
}

void start_move_calibration_buttons()
{
	extra_buttons_show();
	set_a_button_text("Forward 1 cm");
	set_b_button_text("Forward 5 cm");
	set_c_button_text("Use Potentio");
	set_x_button_text("Backward 1 cm");
	set_y_button_text("Backward 5 cm");
	set_z_button_text("Back to Prog");
}

void start_turn_calibration_buttons()
{
	extra_buttons_show();
	set_a_button_text("Left 5");
	set_b_button_text("Left 11 cm");
	set_c_button_text("Use Potentio");
	set_x_button_text("Right 5 cm");
	set_y_button_text("Right 11 cm");
	set_z_button_text("Back to Prog");
}

BUTTON get_button()
{
	if (a_button())
	{
		display_printf(0, 4, "Hands off");
		while (a_button());
		return A_BUTTON;
	}
	if (b_button())
	{
		display_printf(0, 4, "Hands off");
		while (b_button());
		return B_BUTTON;
	}
	if (c_button())
	{
		display_printf(0, 4, "Hands off");
		while (c_button());
		return C_BUTTON;
	}
	if (x_button())
	{
		display_printf(0, 4, "Hands off");
		while (x_button());
		return X_BUTTON;
	}
	if (y_button())
	{
		display_printf(0, 4, "Hands off");
		while (y_button());
		return Y_BUTTON;
	}
	if (z_button())
	{
		display_printf(0, 4, "Hands off");
		while (z_button());
		return Z_BUTTON;
	}
	return NONE;
}


#endif
