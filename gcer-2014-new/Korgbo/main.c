// Created on Mon June 30 2014

#define FINGER_HIGH 2000
#define FINGER_LOW 1100
#define FINGER_UP 1300
#define FINGER_DOWN 950
#define FINGER 0

#define NOTE_HOLD 500
#define NOTE_DURATION (2000 - NOTE_HOLD)

void play_note();
void play_fast_notes(int n, int up_position);

int main()
{	
	set_servo_position(FINGER, FINGER_UP);
	enable_servos();
	
	set_a_button_text("Play note");
	set_b_button_text("Play quiet");
	set_c_button_text("Play loud");
	
	while (1) {
		if (a_button()) {
			play_note();
		}
		if (b_button()) {
			play_fast_notes(5, FINGER_HIGH);
		}
		if (c_button()) {
			play_fast_notes(5, FINGER_LOW);
		}
	}
	
	return 0;
}

void play_note() {
	set_servo_position(FINGER, FINGER_DOWN);
	while (a_button()) ;
	set_servo_position(FINGER, FINGER_UP);
}

void play_fast_notes(int n, int up_position) {
	int k;
	
	for (k = 0; k < n; ++k) {
		set_servo_position(FINGER, FINGER_DOWN);
		msleep(NOTE_HOLD);
		set_servo_position(FINGER, up_position);
		msleep(NOTE_DURATION);
	}
}
