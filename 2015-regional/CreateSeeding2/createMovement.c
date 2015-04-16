#include "createMovement.h"
#include <stdint.h>
#include <kovan/create_codes.h>
#include "universal.h"

/* SIMPLE MOVE FUNCTIONS */

void create_drive_distance(int direction, float centimeters, float speed) {
	float overshoot = (.1 * speed) - 1;
	int millimeters = (int) ((centimeters - overshoot) * 10);
	create_drive_OI(speed * 10, direction);
	_wait_distance((millimeters * direction) - overshoot);
	create_halt();
	CBD();
	adjust_drive(direction, centimeters);
}

void create_spin_degrees(int direction, int degrees, int speed) {
	speed = (int) (speed * MILLIMETERS_PER_DEGREE);
	create_spin(speed, direction);
	_wait_degrees(direction * degrees);
	create_halt();
	CBD();
	adjust_spin(direction, degrees);
}

void create_drive_OI(int speed, int direction) {
	write_byte(OI_DRIVE_DIRECT);
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
}

void create_script_drive(int speed, int direction) {
	write_script_byte(OI_DRIVE_DIRECT);
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
	write_script_byte(get_high_byte(direction * speed));
	write_script_byte(get_low_byte(direction * speed));
}

void create_spin(int speed, int direction) {
	write_byte(OI_DRIVE);
    write_byte(get_high_byte(speed));
	write_byte(get_low_byte(speed));
    if(direction < 0) {
        write_byte(255);
        write_byte(255);
    }
    if(direction > 0) {
        write_byte(0);
        write_byte(1);
    }
}

void create_halt() {
	write_byte(OI_DRIVE_DIRECT);
	write_byte(0);
	write_byte(0);
	write_byte(0);
	write_byte(0);
}

/* ADVANCED MOVE FUNCTIONS */



/* WAIT FUNCTIONS */

void _wait_distance(int distance) {
	write_byte(OI_WAIT_DISTANCE);
	write_byte(get_high_byte(distance));
	write_byte(get_low_byte(distance));
}

void _wait_script_distance(int distance) {
	write_script_byte(OI_WAIT_DISTANCE);
	write_script_byte(get_high_byte(distance));
	write_script_byte(get_low_byte(distance));
}

void _wait_degrees(int degrees) {
	write_byte(OI_WAIT_ANGLE);
	write_byte(get_high_byte(degrees));
	write_byte(get_low_byte(degrees));
}

void wait_duration(float seconds) { // SECONDS CAN BE NO LARGER THAN 255  
	int mseconds = (int) (seconds * 10);
	write_byte(OI_WAIT_TIME);
	write_byte(mseconds); // SECONDS SHOULD NOT BE SPLIT INTO A HIGH BYTE AND A LOW BYTE
}

/* Other functions */

void create_block_done() {
	char buffer[1];
	write_byte(OI_SENSORS);
	write_byte(PACKET_OI_MODE);
	while (create_read_block(buffer, 1) == -1);
	//printf("create free\n");
}

void create_drive_until_bump(int direction, float speed) {
	create_drive_OI(speed * 10, direction);
	msleep(3000);
	//while ((!get_create_lbump()) && (!get_create_rbump()));
	while (1) {
		if (get_create_lbump() || get_create_rbump()) {
			break;
		}
		msleep(100);
	}
	create_halt();
	press_a_to_continue();
}

void create_drive_until_line(int speed, int direction) {
	int lcliff_reading;
	int rcliff_reading;
	create_drive_OI(speed, direction);
	while(1) {
		lcliff_reading = get_create_lcliff(0.05);
		rcliff_reading = get_create_rcliff(0.05);

		if (lcliff_reading || rcliff_reading) {
			create_halt();
			break;
		}
	}
	press_a_to_continue();
}

int create_get_sensor(int packet_number) {
	int data_bytes = 2;
	char buffer[4];
	write_byte(OI_SENSORS);
	write_byte(packet_number);
	if (packet_number == 17) { data_bytes = 1;}
	while (create_read_block(buffer, data_bytes) == 0);
	//printf("buffer 1, buffer 2 - %i, %i\n", buffer[0], buffer[1]);
	if (data_bytes == 1) {
		return buffer[0];
	}
	//printf("%i\n", (buffer[0] << 8));
	return (buffer[0] << 8) | buffer[1];
}

// Scripting functions

void play_script() {
	int i;
	printf("Loading Script\n");
	write_byte(OI_PLAY_SCRIPT);
	write_byte(create_script.length);

	for (i = 0; i < create_script.length++; i++) {
		write_byte(create_script.script[i]);
	}
	printf("Uploaded %i bytes.\n", create_script.length);
	printf("Okay to disconnect LINK or CBC\n");
}

void write_script_byte(int byte) {
	if (create_script.length < 100) {
		create_script.script[create_script.length++] = byte;
	}
	else {
		printf("SCRIPT EXCEEDS BUFFER\n");
	}
}
