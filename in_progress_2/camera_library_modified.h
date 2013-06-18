// Created on Sun March 31 2013
#ifndef _RUS_CAMERA_LIBRARY_H_
#define _RUS_CAMERA_LIBRARY_H_

#include "lego_library.h"
#include "universal_library.h"
//#define LEFT_MOTOR 3
//#define RIGHT_MOTOR 0

#define WHEEL_BASE 17
#define GREEN 0
#define ORANGE 1
#define ROBOT_MARKER 2
#define SCREEN_SIZE //FIXME
#define LARGEST_BLOB 0
#define SECOND_LARGEST 1

#define GOOD_ENOUGH_TO_GRAB_Y 2
#define GOOD_ENOUGH_TO_GRAB_X 2

#define MINIMUM_POM_SIZE 100
#define MINIMUM_ROBOT_MARKER_SIZE 50

#define CENTIMETERS_PER_PIXEL_X 10.0 / 156.0 //Centimeters
#define CENTIMETERS_PER_PIXEL_Y 14.0 / 70 //Centimeters

#define CONSTANT 10

#define ADJUST_LSPEED 15
#define ADJUST_RSPEED 5
#define ADJUST_TIME 50
#define LOOP_DELAY 50

#define SUCKER_MOTOR 2
#define LIFT_SERVO 1
#define LIFT_SERVO_DOWN_POSITION 785
#define LIFT_SERVO_UP_POSITION 2047
#define LIFT_SERVO_DROP_POSITION 1885

#define NO_OF_TIMES_CENTERING 10

typedef struct
{
	int left;
	int right;
	int front;
	int back;
	point2 center;
} bbox;

typedef struct
{
	int r_speed;
	int l_speed;
} pair_speeds;

int GOOD_ENOUGH = 20;
int GOOD_ENOUGH_Y = 10;

int DESIRED_Y;
int DESIRED_X;

point2 NONE = {-1, -1};
bbox BBOX_NONE = {-1, -1, -1, -1, -1};

point2 find_center(int color, int object, int minimum_size);
point2 get_camera_reading();
void move_to_y(int y);
void arm_up();
void arm_down();
void suck_up_pom();
void move_to_x(int x);
void arm_drop();
void face_green_pom();
float set_speeds(point2 robot_center, point2 green_center);

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

bbox get_pile_bbox(int color)
{
	bbox pile;
	rectangle r;
	int number_of_blobs, i;
	
	camera_update();
	number_of_blobs = get_object_count(color);
	
	if (number_of_blobs == 0)
	{
		return BBOX_NONE;
	}
	
	r = get_object_bbox(color, 0);
	pile.left = r.ulx;
	pile.right = r.ulx + r.width;
	pile.back = r.uly;
	pile.front = r.uly + r.height;
	
	for (i = 1; i < number_of_blobs; i++)
	{
		r = get_object_bbox(color, i);
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

// Precondition: green must be visible
void move_to_grab_green()
{
	point2 robot_center, green_center;
	float proportional_speed;
	while (1)
	{
		camera_update();
		robot_center = get_object_center(ROBOT_MARKER, LARGEST_BLOB);
		green_center = get_object_center(GREEN, LARGEST_BLOB);
		
		if (robot_is_centered(robot_center, green_center))
		{
			break;
		}
		
		proportional_speed = set_speeds(robot_center, green_center);
		motor(LEFT_MOTOR, (int) (CONSTANT * proportional_speed));
		motor(RIGHT_MOTOR, (int) (CONSTANT));
		
		//face_green_pom();
		//forwards_to_green_pom();
		//break;
		
	}
}

float set_speeds(point2 robot_center, point2 green_center)
{
	int pixel_x, pixel_y;
	float proportional_speed, radius, x, y;
	
	pixel_x = green_center.x - robot_center.x;
	pixel_y = green_center.y - robot_center.y;
	
	x = CENTIMETERS_PER_PIXEL_X * pixel_x;
	y = CENTIMETERS_PER_PIXEL_Y * pixel_y;
	
	radius = ((x * x) + (y * y)) / (float) (2 * x);
	
	proportional_speed = (2 * radius + WHEEL_BASE) / (2 * radius - WHEEL_BASE);
	return proportional_speed;
}

int robot_is_centered(point2 robot_center, point2 green_center)
{
	if(robot_center.x >= green_center.x - GOOD_ENOUGH_TO_GRAB_X && robot_center.x <= green_center.x + GOOD_ENOUGH_TO_GRAB_X)
	{
		if (robot_center.y >= green_center.y - GOOD_ENOUGH_TO_GRAB_Y && robot_center.y <= green_center.y + GOOD_ENOUGH_TO_GRAB_Y)
		{
			return 1;
		}
	}
	return 0;
}

void face_green_pom()
{
	point2 robot_center, green_center;
	while (1)
	{
		robot_center = find_center(ROBOT_MARKER, LARGEST_BLOB, MINIMUM_ROBOT_MARKER_SIZE);
		green_center = find_center(GREEN, LARGEST_BLOB, MINIMUM_POM_SIZE);
		
		display_printf(0, 1, "robot, green - (%3i, %3i), (%3i, %3i)", robot_center.x, robot_center.y, green_center.x, green_center.y);
		display_printf(0, 2, "area, centroid - %5i, (%3i, %3i)", get_object_area(GREEN, LARGEST_BLOB), get_object_centroid(GREEN, LARGEST_BLOB).x, get_object_centroid(GREEN, LARGEST_BLOB).y);
		if (robot_center.x == -1 || green_center.x == -1)
		{
			continue;
		}
		if(robot_center.x >= green_center.x - GOOD_ENOUGH && robot_center.x <= green_center.x + GOOD_ENOUGH)
		{
			display_printf(0, 0, "Robot is centered on blob");
			break;
		}
		else if (robot_center.x < green_center.x - GOOD_ENOUGH)
		{
			motor(LEFT_MOTOR, ADJUST_LSPEED);
			motor(RIGHT_MOTOR, -ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 0, "RIGHT");
		}
		else
		{
			motor(LEFT_MOTOR, -ADJUST_LSPEED);
			motor(RIGHT_MOTOR, ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 0, "LEFT ");
		}
		msleep(LOOP_DELAY);
	}
}

void turn_to_green()
{
	bbox green_bbox;
	point2 robot_center, green_center;
	while (1)
	{
		robot_center = find_center(ROBOT_MARKER, LARGEST_BLOB, MINIMUM_ROBOT_MARKER_SIZE);
		green_center = find_center(GREEN, LARGEST_BLOB, MINIMUM_POM_SIZE);
		green_bbox = get_pile_bbox(GREEN);
		
		display_printf(0, 1, "robot, green - (%3i, %3i), (%3i, %3i)", robot_center.x, robot_center.y, green_center.x, green_center.y);
		display_printf(0, 2, "area, centroid - %5i, (%3i, %3i)", get_object_area(GREEN, LARGEST_BLOB), get_object_centroid(GREEN, LARGEST_BLOB).x, get_object_centroid(GREEN, LARGEST_BLOB).y);
		if (robot_center.y == -1 || green_center.y == -1)
		{
			continue;
		}
		if(green_bbox.back >= 75 - GOOD_ENOUGH_Y && green_bbox.back <= 75 + GOOD_ENOUGH_Y)
		{
			display_printf(0, 0, "Robot is centered on blob");
			break;
		}
		else if (green_bbox.back > 75 + GOOD_ENOUGH_Y)
		{
			motor(LEFT_MOTOR, ADJUST_LSPEED);
			motor(RIGHT_MOTOR, ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 0, "FORWARDS");
		}
		else
		{
			motor(LEFT_MOTOR, -ADJUST_LSPEED);
			motor(RIGHT_MOTOR, -ADJUST_RSPEED);
			msleep(ADJUST_TIME);
			off(LEFT_MOTOR);
			off(RIGHT_MOTOR);
			display_printf(0, 0, "BACKWARDS ");
		}
		msleep(LOOP_DELAY);
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


#define NORMAL_L_SPEED 2
#define NORMAL_R_SPEED 2
#define LP 0.17
#define RP 0.17

void proportional_move_to_grab()
{
	point2 robot_center, green_center;
	int lspeed = NORMAL_L_SPEED;
	int rspeed = NORMAL_R_SPEED;
	int xl_error, xr_error, y_error;
	bbox robot_bbox, green_bbox;
	int desired_left, desired_right, actual_left, actual_right;
	
	
	while (1)
	{
		robot_bbox = get_pile_bbox(ROBOT_MARKER);
		green_bbox = get_pile_bbox(GREEN);
		robot_center = find_center(ROBOT_MARKER, LARGEST_BLOB, MINIMUM_ROBOT_MARKER_SIZE);
		green_center = find_center(GREEN, LARGEST_BLOB, MINIMUM_POM_SIZE);
		
		desired_left = robot_center.x - ((robot_bbox.right - robot_bbox.left) / 2);
		desired_right = robot_center.x + ((robot_bbox.right - robot_bbox.left) / 2);
		
		actual_left = green_bbox.left;
		actual_right = green_bbox.right;
		
		xl_error = desired_left - actual_left;
		xr_error = desired_right - actual_right;
		//y_error = robot_center.y - green_center.y;
		
		rspeed = ((float) NORMAL_R_SPEED + 0.1 * xr_error) + 0.5;
		lspeed = ((float) NORMAL_L_SPEED + 0.1 * xl_error) + 0.5;
		
		if(robot_center.x >= green_center.x - GOOD_ENOUGH && robot_center.x <= green_center.x + GOOD_ENOUGH && robot_center.y >= green_center.y - GOOD_ENOUGH && robot_center.y <= green_center.y + GOOD_ENOUGH)
		{
			display_printf(0, 0, "Robot is centered on blob");
			break;
		}
		motor(LEFT_MOTOR, lspeed);
		motor(RIGHT_MOTOR, rspeed);
		msleep(20);
		display_printf(0, 1, "lspeed, rspeed - %i, %i", lspeed, rspeed);
	}
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

void PID()
{
	int rspeed = NORMAL_R_SPEED;
	int lspeed = NORMAL_L_SPEED;
	int l_error = 0;
	int r_error = 0;
	point2 robot_center, green_center;
	//int xl_error, xr_error, y_error;
	bbox robot_bbox, green_bbox;
	
	while (1)
	{
		robot_bbox = get_pile_bbox(ROBOT_MARKER);
		green_bbox = get_pile_bbox(GREEN);
		robot_center = find_center(ROBOT_MARKER, LARGEST_BLOB, MINIMUM_ROBOT_MARKER_SIZE);
		green_center = find_center(GREEN, LARGEST_BLOB, MINIMUM_POM_SIZE);
		
		l_error = robot_bbox.left - green_bbox.left;
		r_error = robot_bbox.right - green_bbox.right;
		
		rspeed = NORMAL_R_SPEED + RP * r_error;
		lspeed = NORMAL_L_SPEED + LP * l_error;
		
		if (rspeed < MIN_SPEED)
		{
			rspeed = MIN_SPEED;
		}
		if (lspeed < MIN_SPEED)
		{
			lspeed = MIN_SPEED;
		}
		if (rspeed > MAX_SPEED)
		{
			rspeed = MAX_SPEED;
		}
		if (lspeed > MAX_SPEED)
		{
			lspeed = MAX_SPEED;
		}
		if(robot_center.x >= green_center.x - GOOD_ENOUGH && robot_center.x <= green_center.x + GOOD_ENOUGH && robot_center.y >= green_center.y - GOOD_ENOUGH && robot_center.y <= green_center.y + GOOD_ENOUGH)
		{
			display_printf(0, 3, "Robot is centered on blob");
			break;
		}
		motor(LEFT_MOTOR, lspeed);
		motor(RIGHT_MOTOR, rspeed);
		display_printf(0, 0, "rspeed, lspeed: %4i, %4i", rspeed, lspeed);
		display_printf(0, 1, "rreading, lreading: %4i, %4i", green_bbox.right, green_bbox.left);
		msleep(20);
	}
	off(LEFT_MOTOR);
	off(RIGHT_MOTOR);
}

#endif
