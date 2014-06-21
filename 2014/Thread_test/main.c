// Created on Tue June 10 2014

int main() {
	move_and_pick_up_poms();
	return 0;
}

void run_tread() {
	motor(2, 100);
	motor(0, 100);
}

void move_forwards() {
	motor(1, 100);
	motor(3, 100);
}

void move_and_pick_up_poms() {
	thread tread_thread;
	thread move_thread;
	tread_thread = thread_create(run_tread);
	move_thread = thread_create(move_forwards);
	thread_start(tread_thread);
	thread_start(move_thread);
	msleep(10000);
	thread_destroy(tread_thread);
	thread_destroy(move_thread);
}
