// Created: 2/22/2013

#ifndef _CREATEMOVEMENT_H_
#define _CREATEMOVEMENT_H_

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
#define CURRENT 23

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

#endif
