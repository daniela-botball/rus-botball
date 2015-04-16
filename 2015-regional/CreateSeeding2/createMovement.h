// Created: 2/22/2013

#ifndef _CREATEMOVEMENT_H_
#define _CREATEMOVEMENT_H_

// The next 4 really belong in the (generic) MOVEMENT library
// The next 4 have been reversed for the purpose of this year's create robot. Normally, FORWARDS is 1 and BACKWARDS is -1. LEFT is -1 and RIGHT is 1
#define FORWARDS -1
#define BACKWARDS 1
#define LEFT 1
#define RIGHT -1

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

// These codes might need to be in octal?? Left and Right are per Create, regardless of drive direction.
#define WHEEL_DROP 1
#define FRONT_WHEEL_DROP 2
#define LEFT_WHEEL_DROP 3
#define RIGHT_WHEEL_DROP 4
#define BUMP 0x05
#define LEFT_BUMP 0x06
#define RIGHT_BUMP 7
#define VIRTUAL_WALL 8
#define WALL 9
#define CLIFF 10
#define LEFT_CLIFF 11
#define FRONT_LEFT_CLIFF 12
#define FRONT_RIGHT_CLIFF 13
#define RIGHT_CLIFF 14
#define HOME_BASE 15
#define ADVANCE_BUTTON 16
#define PLAY_BUTTON 17
#define DIGITAL_INPUT_0 18
#define DIGITAL_INPUT_1 19
#define DIGITAL_INPUT_2 20
#define DIGITAL_INPUT_3 21
#define OI_MODE_IS_PASSIVE 22

struct create_script_buffer {
	int script[100];
	int length;
} create_script;

void create_drive_until_event(int direction, float speed, int event);

void _wait_duration(float seconds);
void _wait_degrees(int degrees);
void _wait_distance(int distance);
void create_drive_OI(int speed, int direction);
void create_spin(int speed, int direction);
void create_halt();
void create_drive_distance(int direction, float centimeters, float speed);
void create_spin_degrees(int direction, int degrees, int speed);

void create_drive_until_bump(int direction, float speed);
void create_drive_until_line(int speed, int direction);

void create_block_done();
int create_get_sensor(int packet_number);
void play_script();
void write_script_byte(int byte);
void create_script_drive(int speed, int direction);
void _wait_script_distance(int distance);

#endif
