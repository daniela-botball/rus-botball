// Created on Sun March 31 2013
#ifndef _CAMERA_LIBRARY_H_
#define _CAMERA_LIBRARY_H_

#include "lego_library.h"
//#define LEFT_MOTOR 3
//#define RIGHT_MOTOR 0

#define GREEN 0
#define BLUE_PEG //FIXME
#define SCREEN_SIZE //FIXME
#define LARGEST_BLOB 0
#define SECOND_LARGEST 1
#define GOOD_ENOUGH 2

#define MINIMUM_POM_SIZE 100

#define ADJUST_LSPEED 50
#define ADJUST_RSPEED 30
#define ADJUST_TIME 50
#define LOOP_DELAY 20

#define SUCKER_MOTOR 2
#define LIFT_SERVO 1
#define LIFT_SERVO_DOWN_POSITION 785
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_DROP_POSITION 1885

#define NO_OF_TIMES_CENTERING 10

int DESIRED_Y;
int DESIRED_X;

point2 NONE = {-1, -1};

typedef struct
{
	int left;
	int right;
	int front;
	int back;
	point2 center;
} bbox;

point2 find_center(int color, int object, int minimum_size);
point2 get_camera_reading();
void move_to_y(int y);
void arm_up();
void arm_down();
void suck_up_pom();
void move_to_x(int x);
void arm_drop();

point2 get_camera_reading()
{
	point2 new;
	point2 old;
	int x;
	old.x = -1;
	old.y = -1;
	set_a_button_text("Done");
	set_b_button_text("Pause");
	set_c_button_text("Resume");
	printf("Press 'Done' when the pom is centered\n");
	msleep(1000);
	camera_open(LOW_RES);
	while (!a_button_clicked())
	{
		camera_update();
		x = get_object_count(GREEN);
		if (x > 0)
		{
			new = get_object_center(GREEN, LARGEST_BLOB);
			if (new.x != old.x || new.y != old.y)
			{
				printf("Largest blob at (%i, %i)\n", new.x, new.y);				
			}
			old = new;
		}
		else
		{
			printf("NO VISIBLE BLOB\n");
		}
		if (b_button_clicked())
		{
			while (1)
			{
				if (c_button_clicked())
				{
					break;
				}
				if (a_button_clicked())
				{
					display_clear();
					printf("Final position is (%i, %i)\n", new.x, new.y);
					return new;
				}
			}
		}
	}
	display_clear();
	printf("Final position is (%i, %i)\n", new.x, new.y);
	return new;
}

void suck_up_pom()
{
	int i;
	motor(SUCKER_MOTOR, 100);
	extra_buttons_show();
	for (i = 0; i < 5; i++)
	{
		move_to_y(DESIRED_Y);
		msleep(500);
		move_to_x(DESIRED_X);
		msleep(500);
	}
	arm_down();
	sleep(1);
	arm_up();
	sleep(2);
	off(SUCKER_MOTOR);
}

void arm_down()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position > LIFT_SERVO_DOWN_POSITION; position -= 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
	off(1);
}

void arm_up()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position < LIFT_SERVO_UP_POSITION; position += 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
}

void arm_drop()
{
	int position;
	for (position = get_servo_position(LIFT_SERVO); position < LIFT_SERVO_DROP_POSITION; position += 20)
	{
		set_servo_position(LIFT_SERVO, position);
		msleep(20);
	}
}
// 0 - 159 x
// 0 - 119 y
void move_to_y(int y)
{
	int center_of_blob;
	while (1)
	{
		camera_update();
		center_of_blob = get_object_center(GREEN, LARGEST_BLOB).y;
		display_printf(0, 0, "y, center of blob; %i, %i", y, center_of_blob);
		if(center_of_blob > y - GOOD_ENOUGH && center_of_blob < y + GOOD_ENOUGH)
		{
			
			display_printf(0, 1, "Robot is centered on blob");
			break;
		}
		else if (center_of_blob < y - GOOD_ENOUGH)
		{
			motor(LEFT_MOTOR, ADJUST_LSPEED);
			motor(RIGHT_MOTOR, ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "FORWARDS ");
		}
		else
		{
			motor(LEFT_MOTOR, -ADJUST_LSPEED);
			motor(RIGHT_MOTOR, -ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "BACKWARDS");
		}
	}
}


void move_to_x(int x)
{
	int center_of_blob, flag;
	flag = 1;
	while (1)
	{
		camera_update();
		center_of_blob = get_object_center(GREEN, LARGEST_BLOB).x;
		display_printf(0, 0, "x, center of blob; %i, %i", x, center_of_blob);
		/*if (flag == 1)
		{
			if (center_of_blob < x - GOOD_ENOUGH)
			{
				motor(LEFT_MOTOR, -100);
				motor(RIGHT_MOTOR, 100);
				msleep(70);
				off(LEFT_MOTOR);
				off(RIGHT_MOTOR);
				display_printf(0, 1, "LEFT ");
			}
			else
			{
				motor(LEFT_MOTOR, 100);
				motor(RIGHT_MOTOR, -100);
				msleep(70);
				off(LEFT_MOTOR);
				off(RIGHT_MOTOR);
				display_printf(0, 1, "RIGHT");
			}
			flag = -1;
		}*/
		if(center_of_blob >= x - GOOD_ENOUGH && center_of_blob <= x + GOOD_ENOUGH)
		{
			
			display_printf(0, 1, "Robot is centered on blob");
			break;
		}
		else if (center_of_blob < x - GOOD_ENOUGH)
		{
			motor(LEFT_MOTOR, -ADJUST_LSPEED);
			motor(RIGHT_MOTOR, ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "LEFT ");
		}
		else
		{
			motor(LEFT_MOTOR, ADJUST_LSPEED);
			motor(RIGHT_MOTOR, -ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "RIGHT");
		}
		msleep(LOOP_DELAY);
	}
}

/*void center_green()
{
	int center_of_green, center_of_track;
	point2 blue_peg1, blue_peg2;
	// Precondition is that two blue pegs must be visible by the camera
	while (1)
	{
		camera_update();
		center_of_green = get_object_center(GREEN, LARGEST_BLOB).x;
		blue_peg1 = get_object_center(BLUE_PEG, LARGEST_BLOB);
		blue_peg2 = get_object_center(BLUE_PEG, SECOND_LARGEST_BLOB);
		center_of_track = (blue_peg1.x + bluepeg2.x) / 2;
		
		if(center_of_green >= center_of_track - GOOD_ENOUGH && center_of_green <= center_of_track + GOOD_ENOUGH)
		{
			display_printf(0, 1, "Robot is centered on blob");
			break;
		}
		else if (center_of_green < center_of_track - GOOD_ENOUGH)
		{
			motor(LEFT_MOTOR, -ADJUST_LSPEED);
			motor(RIGHT_MOTOR, ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "LEFT ");
		}
		else
		{
			motor(LEFT_MOTOR, ADJUST_LSPEED);
			motor(RIGHT_MOTOR, -ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 1, "RIGHT");
		}
		msleep(LOOP_DELAY);
	}
}*/

// Finds the center of a given blob size (object) in a given channel with a minimum size
point2 find_center(int color, int object, int minimum_size)
{
	point2 object_center;
	camera_update();
	if (get_object_count(color) < object + 1)
	{
		return NONE;
	}
	if (get_object_area(color, object) > minimum_size)
	{
		object_center = get_object_center(color, object);
		return object_center;
	}
	return NONE;
}

bbox get_pile_bbox()
{
	bbox pile;
	rectangle r;
	int number_of_blobs, i;
	
	camera_update();
	number_of_blobs = get_object_count(ORANGE);
	
	r = get_object_bbox(ORANGE, 0);
	pile.left = r.ulx;
	pile.right = r.ulx + r.width;
	pile.back = r.uly;
	pile.front = r.uly + r.height;
	
	for (i = 1; i < number_of_blobs; i++)
	{
		r = get_object_bbox(ORANGE, i);
		if (r.width * r.height < MINIMUM_POM_SIZE)
		{
			break;
		}
		
		if (r.ulx < pile.left)
		{
			pile.left = r.ulx;
		}
		if (r.ulx + r.width > pile.right)
		{
			pile.right = r.ulx + r.width;
		}
		if (r.uly < pile.back)
		{
			pile.back = r.uly;
		}
		if (r.uly + r.height > pile.front)
		{
			pile.front = r.uly + r.height;
		}
	}
	pile.center.x = (pile.left + pile.right) / 2;
	pile.center.y = (pile.front + pile.back) / 2;
	return pile;
}

int get_left_most_point(int color, int minimum_size)
{
	int number_of_blobs, i, biggest;
	camera_update();
	
	number_of_blobs = get_object_count(color);
	
	get_object_bbox(color, 0);
	biggest = blob_right_edge [0];
	for (i = 1; i < number_of_blobs; i++)
	{
		if (blob_right_edge [i] > biggest)
		{
			biggest = blob_right_edge [i];
		}
	}
	return biggest;
}

#endif
