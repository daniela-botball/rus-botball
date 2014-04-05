// Created: 2/22/2013

#ifndef _CREATEMOVEMENT_H_
#define _CREATEMOVEMENT_H_

#include <stdint.h>
#include <kovan/create_codes.h>

#define write_byte create_write_byte
#define CBD create_block_done

#define get_high_byte(x) ((x >> 8) & 0x00FF)
#define get_low_byte(x) (x & 0xFF)

#define MILLIMETERS_PER_DEGREE 2.36

#define CLIFF_LEFT 28
#define CLIFF_FRONT_LEFT 29
#define CLIFF_FRONT_RIGHT 30
#define CLIFF_RIGHT 31
#define PACKET_OI_MODE 35

struct create_script_buffer
{
	int script[100];
	int length;
} create_script;

void wait_duration(float seconds);
void _wait_degrees(int degrees);
void _wait_distance(int distance);
void create_drive(int speed, int direction);
void create_spin(int speed, int direction);
void create_halt();
void create_drive_distance(float centimeters, float speed, int direction);
void create_spin_degrees(int degrees, int speed, int direction);
void create_block_done();
void create_drive_until_line(int speed, int direction);
int create_get_sensor(int packet_number);
void play_script();
void write_script_byte(int byte);
void create_script_drive(int speed, int direction);
void _wait_script_distance(int distance);

/* SIMPLE MOVE FUNCTIONS */

void create_drive(int speed, int direction)
{
	write_byte(OI_DRIVE_DIRECT);
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
}

void create_script_drive(int speed, int direction)
{
	write_script_byte(OI_DRIVE_DIRECT);
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
}

void create_spin(int speed, int direction)
{
	write_byte(OI_DRIVE);
    write_byte(get_high_byte(speed));
	write_byte(get_low_byte(speed));
    if(direction < 0)
    {
        write_byte(255);
        write_byte(255);
    }
    if(direction > 0)
    {
        write_byte(0);
        write_byte(1);
    }
}

void create_halt()
{
	write_byte(OI_DRIVE_DIRECT);
	write_byte(0);
	write_byte(0);
	write_byte(0);
	write_byte(0);
}

/* ADVANCED MOVE FUNCTIONS */

// moves the create robot in a straight manner with a given distance in centimeters, speed in centimeters per second, and direction (FORWARDS or BACKWARDS) 
void create_drive_distance(float centimeters, float speed, int direction)
{
	float overshoot = (.1 * speed) - 1;
	int millimeters = (int) ((centimeters - overshoot) * 10);
	create_drive(speed * 10, direction);
	_wait_distance((millimeters * direction) - overshoot);
	create_halt();
	CBD();
}

void create_spin_degrees(int degrees, int speed, int direction)
{
	speed = (int) (speed * MILLIMETERS_PER_DEGREE);
	create_spin(speed, direction);
	_wait_degrees(direction * degrees);
	create_halt();
	CBD();
}

/* WAIT FUNCTIONS */

void _wait_distance(int distance)
{
	write_byte(OI_WAIT_DISTANCE);
	write_byte(get_high_byte(distance));
	write_byte(get_low_byte(distance));
}

void _wait_script_distance(int distance)
{
	write_script_byte(OI_WAIT_DISTANCE);
	write_script_byte(get_high_byte(distance));
	write_script_byte(get_low_byte(distance));
}

void _wait_degrees(int degrees)
{
	write_byte(OI_WAIT_ANGLE);
	write_byte(get_high_byte(degrees));
	write_byte(get_low_byte(degrees));
}

void wait_duration(float seconds) // SECONDS CAN BE NO LARGER THAN 255
{
	int mseconds = (int) (seconds * 10);
	write_byte(OI_WAIT_TIME);
	write_byte(mseconds); // SECONDS SHOULD NOT BE SPLIT INTO A HIGH BYTE AND A LOW BYTE
}

/* Other functions */

void create_block_done()
{
	char buffer[1];
	write_byte(OI_SENSORS);
	write_byte(PACKET_OI_MODE);
	while (create_read_block(buffer, 1) == -1);
	//printf("create free\n");
}

void create_drive_until_line(int speed, int direction)
{
	int lcliff_reading;
	int rcliff_reading;
	create_drive(speed, direction);
	while(1)
	{
		lcliff_reading = get_create_lcliff(0.05);
		rcliff_reading = get_create_rcliff(0.05);
		
		if (lcliff_reading || rcliff_reading)
		{
			create_halt();
			break;
		}
	}
}
/*
int create_get_sensor(int packet_number)
{
	uint8_t buffer[2];
	write_byte(OI_SENSORS);
	write_byte(packet_number);
	while (create_read_block(buffer, 2) == -1);
	printf("buffer 1, buffer 2 - %i, %i\n", buffer[0], buffer[1]);
	printf("%i\n", (buffer[0] << 8));
	return (buffer[0] << 8) | buffer[1];
}
*/
// Scripting functions

void play_script()
{
	int i;
	printf("Loading Script\n");
	write_byte(OI_PLAY_SCRIPT);
	write_byte(create_script.length);
	
	for (i = 0; i < create_script.length++; i++)
	{
		write_byte(create_script.script[i]);
	}
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

#define NORMAL_LSPEED 80
#define NORMAL_RSPEED 80
#define DESIRED_LREADING 400
#define DESIRED_RREADING 400
#define LKP 0.2
#define RKP 0.2
#define MIN_SPEED 10
#define MAX_SPEED 100
#define LREFLECTANCE 1
#define RREFLECTANCE 0
#define STOPPING_SENSOR 2
#define STOPPING_THRESHOLD 100

#endif


