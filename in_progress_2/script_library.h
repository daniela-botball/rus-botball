// Created: 2/22/2013

#ifndef _RUS_SCRIPT_LIBRARY_H_
#define _RUS_SCRIPT_LIBRARY_H_

#include <stdint.h>

#define write_script_byte serial_write_script_byte
#define write_byte create_write_byte
//#define get_high_byte(x) ((x & 0xFFFF) >> 8)
#define get_high_byte(x) ((x >> 8) & 0x00FF)
#define get_low_byte(x) (x & 0xFF)

#define PI 3.14159

#define MILLIMETERS_PER_DEGREE 2.36

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT 1
#define RIGHT -1

#define DRIVE_DIRECT 145
#define DRIVE 137
#define WAIT_DISTANCE 156
#define WAIT_ANGLE 157
#define WAIT_TIME 155
#define SENSORS 142
#define LOAD_SCRIPT 152

#define CLIFF_LEFT 28
#define CLIFF_FRONT_LEFT 29
#define CLIFF_FRONT_RIGHT 30
#define CLIFF_RIGHT 31
#define PACKET_OI_MODE 35
#define BUMP 7

struct create_script_buffer
{
	int script[100];
	int length;
} create_script;

void wait_duration(float seconds);
void _script_wait_degrees(int degrees);
void create_drive(int speed, int direction);
void create_spin(int speed, int direction);
void create_halt();
void create_drive_distance(float centimeters, float speed, int direction);
void create_spin_degrees(int degrees, int speed, int direction);
void create_block_done();
void create_drive_until_line(int speed, int direction);
int create_get_sensor(int packet_number);
void load_script();
void write_script_byte(int byte);
void create_script_drive(int speed, int direction);
void _script_wait_distance(int distance);
void create_script_arc(float radius, float speed, float distance);

/* SIMPLE MOVE FUNCTIONS */

void create_script_drive(int speed, int direction)
{
	write_script_byte(DRIVE_DIRECT);
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
}

void create_script_drive_direct(int rspeed, int lspeed)
{
	write_script_byte(DRIVE_DIRECT);
	write_script_byte(get_high_byte(rspeed));
	write_script_byte(get_low_byte(rspeed));
	write_script_byte(get_high_byte(lspeed));
	write_script_byte(get_low_byte(lspeed));
}

void create_script_spin(int speed, int direction)
{
	write_script_byte(DRIVE);
    write_script_byte(get_high_byte(speed));
	write_script_byte(get_low_byte(speed));
    if(direction < 0)
    {
        write_script_byte(255);
        write_script_byte(255);
    }
    if(direction > 0)
    {
        write_script_byte(0);
        write_script_byte(1);
    }
}

void create_script_halt()
{
	write_script_byte(DRIVE_DIRECT);
	write_script_byte(0);
	write_script_byte(0);
	write_script_byte(0);
	write_script_byte(0);
}

/* ADVANCED MOVE FUNCTIONS */

void create_arc()
{
	write_script_byte(137);
	write_script_byte(255);
	write_script_byte(56);
	write_script_byte(1);
	write_script_byte(244);
}

// moves the create robot in a straight manner with a given distance in centimeters, speed in centimeters per second, and direction (FORWARDS or BACKWARDS)
void create_script_drive_distance(int millimeters, float speed, int direction)
{
	create_script_drive(speed, direction);
	_script_wait_distance(millimeters * direction);
	create_script_halt();
}

void create_script_spin_degrees(int degrees, int speed, int direction)
{
	speed = (int) (speed * MILLIMETERS_PER_DEGREE);
	create_script_spin(speed, direction);
	_script_wait_degrees(direction * degrees);
	create_script_halt();
}

/* WAIT FUNCTIONS */

void _script_wait_distance(int distance)
{
	write_script_byte(WAIT_DISTANCE);
	write_script_byte(get_high_byte(distance));
	write_script_byte(get_low_byte(distance));
}

void _script_wait_degrees(int degrees)
{
	write_script_byte(WAIT_ANGLE);
	write_script_byte(get_high_byte(degrees));
	write_script_byte(get_low_byte(degrees));
}

void script_wait_duration(float seconds) // SECONDS CAN BE NO LARGER THAN 255
{
	//int mseconds = (int) (seconds * 10);
	write_script_byte(WAIT_TIME);
	write_script_byte(seconds); // SECONDS SHOULD NOT BE SPLIT INTO A HIGH BYTE AND A LOW BYTE
}

void script_wait_event(int packet)
{
	write_script_byte(158);
	write_script_byte(packet);
}
/* Other functions */

// Scripting functions

void load_script()
{
	int i;
	printf("Loading Script\n");
	write_byte(LOAD_SCRIPT);
	write_byte(create_script.length);
	
	for (i = 0; i <= create_script.length; i++)
	{
		write_byte(create_script.script[i]);
	}
	create_power_led(255, 255);
	create_play_led(1);
	create_advance_led(1);
	printf("Uploaded %i bytes.\n", create_script.length);
	printf("Okay to disconnect LINK or CBC\n");
}

void write_script_byte(int byte)
{
	if (create_script.length < 100)
	{
		create_script.script[create_script.length++] = byte;
	}
	else
	{
		printf("SCRIPT EXCEEDS BUFFER\n");
	}
}

#endif
