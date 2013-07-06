// Created on Fri July 5 2013

#define WAIST_SERVO_PORT 0
#define SPINE_SERVO_PORT 2
#define NECK_SERVO_PORT 1

float _WAIST_DURATION;
int _WAIST_POSITION_END;
float _SPINE_DURATION;
int _SPINE_POSITION_END;
float _NECK_DURATION;
int _NECK_POSITION_END;

void servo_move_for(int servo, float time_duration, int pos_end);

int main() {
	set_servo_position(WAIST_SERVO_PORT, 1000);
	set_servo_position(SPINE_SERVO_PORT, 1000);
	set_servo_position(NECK_SERVO_PORT, 1000);
	enable_servos();
	
	//servo_move_for(WAIST_SERVO_PORT, 5.0, 1500);
	
	disable_servos();
	
	return 0;
}

// moves the given servo for the specified
// duration (time) to the specified end position
void servo_move_for(int servo, float time_duration, int pos_end) {
	int pos_start = get_servo_position(servo);
	int pos_current = pos_start;
	float time_start = seconds();
	float time_elapsed = seconds() - time_start;
	while (time_elapsed <= time_duration) {
		pos_current = pos_start + (pos_end - pos_start) * time_elapsed / time_duration;
		set_servo_position(0, pos_current);
		printf("[%.2f] setting servo[%d] to pos. %d\n", time_elapsed, 0, pos_current);
		time_elapsed = seconds() - time_start;
	}
	set_servo_position(0, pos_end);
} // end servo_move_for()

void waist_move_for() {
	servo_move_for(WAIST_SERVO_PORT, _WAIST_DURATION, _WAIST_POSITION_END);
}

void spine_move_for() {
	servo_move_for(SPINE_SERVO_PORT, _SPINE_DURATION, _SPINE_POSITION_END);
}

void neck_move_for() {
	servo_move_for(NECK_SERVO_PORT, _NECK_DURATION, _NECK_POSITION_END);
}

// moves the "waist", "spine", and "neck" servos for the specified
// duration to the specified positions
void actor_move_for(float time_duration, int l_vel, int r_vel,
int waist_pos_end, int spine_pos_end, int neck_pos_end) {
	thread waist_thread, spine_thread, neck_thread;
	
	waist_thread = create_thread(waist_move_for);
	spine_thread = create_thread(spine_move_for);
	neck_thread = create_thread(neck_move_for);
	
	_WAIST_DURATION = time_duration;
	_SPINE_DURATION = time_duration;
	_NECK_DURATION = time_duration;
	
	_WAIST_POSITION_END = waist_pos_end;
	_SPINE_POSITION_END = spine_pos_end;
	_NECK_POSITION_END = neck_pos_end;
	
	thread_start(waist_thread);
	thread_start(spine_thread);
	thread_start(neck_thread);
}
