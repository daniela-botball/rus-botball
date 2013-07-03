// Created on Wed May 22 2013

int main()
{
	if(!drone_connect()) {
		printf("Drone connection failed!\n");
		return 1;
	}
	
	printf("Connected to a version %d drone\n", get_drone_version());
	
	drone_camera_open(FRONT_CAMERA);
	
	if(get_channel_count() != 1) {
		printf("Invalid channel configuration\n");
		drone_disconnect();
		return 1;
	}
	
	
	printf("Takeoff!\n");
	drone_takeoff();
	msleep(2000);
	/*
	while(!a_button()) {
		camera_update();
		if(get_object_count(0) < 1) {
			drone_hover();
			continue;
		}
		const double offset = (get_object_center(0, 0).x - 160) / 160.0;
		const double heightOffset = -(get_object_center(0, 0).y - 120) / 120.0;
		printf("offset = %lf, heightOffset = %lf\n", offset, heightOffset);
		drone_move(-offset / 40.0, -0.05, heightOffset / 10.0, offset / 2.0);
	}
	*/
	drone_land();
	msleep(2000);
	
	camera_close();
	
	drone_disconnect();
	return 0;
}
