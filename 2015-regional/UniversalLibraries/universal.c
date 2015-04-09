int _ROBOT = -1;

void set_robot(int robot) {
	_ROBOT = robot;
}

void press_a_to_continue() {
	display_clear();
	printf("Press 'A' to continue\n");
	while (!a_button());
	while (a_button());
	msleep(500);
}
