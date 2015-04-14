// Created on Mon June 30 2014

#define FINGER_HIGH 2000
#define FINGER_LOW 1100

#define FINGER1_UP 1606
#define FINGER1_DOWN 1048
#define FINGER2_UP 1500
#define FINGER2_DOWN 817
#define FINGER1 3
#define FINGER2 1

#define NOTE_HOLD 500
#define NOTE_DURATION (2000 - NOTE_HOLD)

#define QUARTER_NOTE bpm/1

int find_finger_position(int port, char* position);
void set_fingers(int positions[]);
void play_sequence(int up[], int down[]);

void play_note1();
void play_note2();
void play_note1_and_2();
void test1();
void play_hot_cross_buns();
void play_note();
//void play_fast_notes(int n, int up_position);

int main()
{
	int up[4];
	int down[4];
	int k;
	int bpm;
	
	bpm = 60;
	
	for (k = 0; k < 4; ++k) {
		set_servo_position(k, 1024);
	}
	enable_servos();
	
	for (k = 0; k < 4; ++k) {
		down[k] = find_finger_position(k, "DOWN");
		up[k] = find_finger_position(k, "UP");
	}
	
	printf("Press A to continue.\n");
	while (! a_button()) {}
	printf("HANDS OFF!\n");
	while (a_button()) {}
	msleep(1000);
	
	set_fingers(up);
	
	printf("Press A to continue.\n");
	while (! a_button()) {}
	printf("HANDS OFF!\n");
	while (a_button()) {}
	msleep(1000);
	
	//play_note(0, QUARTER_NOTE, up, down);
	play_hot_cross_buns(up, down);
	//play_sequence(up, down);
	

	disable_servos();
	
	return 0;
}

void set_fingers(int positions[]) {
	int k;
	
	for (k = 0; k < 4; ++k) {
		set_servo_position(k, positions[k]);
	}
}

void play_sequence(int up[], int down[]) {
	int k;
	
	for (k = 0; k < 4; ++k ) {
		set_servo_position(k, down[k]);
		msleep(1000);
		set_servo_position(k, up[k]);
		msleep(1000);
	}
}
		
void test1() {
	set_servo_position(FINGER1, FINGER1_UP);
	set_servo_position(FINGER2, FINGER2_UP);

	enable_servos();
	
	set_a_button_text("Play 1");
	set_b_button_text("Play 2");
	set_c_button_text("Play both");
	
	while (1) {
		if (a_button()) {
			play_note1();
		}
		if (b_button()) {
			play_note2();
		}
		if (c_button()) {
			play_note1_and_2();
		}
	}
}

void play_note1() {
	set_servo_position(FINGER1, FINGER1_DOWN);
	while (a_button()) ;
	set_servo_position(FINGER1, FINGER1_UP);
}

void play_note2() {
	set_servo_position(FINGER2, FINGER2_DOWN);
	while (b_button()) ;
	set_servo_position(FINGER2, FINGER2_UP);
}

void play_note1_and_2() {
	set_servo_position(FINGER1, FINGER1_DOWN);
	set_servo_position(FINGER2, FINGER2_DOWN);
	while (c_button()) ;
	set_servo_position(FINGER1, FINGER1_UP);
	set_servo_position(FINGER2, FINGER2_UP);
}

void play_hot_cross_buns(int up[], int down[]) {
	int k;
	k = 2;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 1;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 0;
	set_servo_position(k, down[k]);
	msleep(2000);
	set_servo_position(k, up[k]);
	k = 2;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 1;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 0;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	msleep(1000);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	k = 1;
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	set_servo_position(k, down[k]);
	msleep(250);
	set_servo_position(k, up[k]);
	msleep(250);
	k = 2;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 1;
	set_servo_position(k, down[k]);
	msleep(1000);
	set_servo_position(k, up[k]);
	k = 0;
	set_servo_position(k, down[k]);
	msleep(2000);
	set_servo_position(k, up[k]);
}

/*void play_note(pitch, length, int up[], int down[]) {
	int k;
	k = 0;
	set_servo_position(pitch, down);
	msleep(length);
	set_servo_position(pitch, up[k]);
	
}
/*

/*
void play_fast_notes(int n, int up_position) {
	int k;
	
	for (k = 0; k < n; ++k) {
		set_servo_position(FINGER1, FINGER1_DOWN);
		msleep(NOTE_HOLD);
		set_servo_position(FINGER, up_position);
		msleep(NOTE_DURATION);
	}
}
*/

// 444, 669 829 989 164 304 334 524.

int find_finger_position(int port, char* position) {
	int delta = 5;
	int milliseconds_per_iteration = (int) (1000.0 * ((1.0 / (1000.0 / 5.0)) * delta));
	
	printf("Press and hold A to move finger DOWN.\n");
	printf("Press and hold B to move finger UP.\n");
	printf("Press C when finger %i is in %s position.\n", port, position);
	
	while (1) {
		if (a_button()) {
			set_servo_position(port,get_servo_position(port) - delta);
		} else if (b_button()) {
			set_servo_position(port, get_servo_position(port) + delta);
		} else if (c_button()) {
			printf("%s position for finger %i is %i.\n", position, port, get_servo_position(port));
			printf("HANDS OFF!\n");
			while (c_button()) {}
			msleep(500);
			return get_servo_position(port);
		}
		msleep(milliseconds_per_iteration);
	}
}
