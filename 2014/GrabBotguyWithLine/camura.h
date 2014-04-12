// Created on Sun March 30 2014
#ifndef _CAMERA_H_
#define _CAMERA_H_

//Precondition: camera must already be open
int center_on_blob(int desired_x, int color,float time ) {
	int actual_x;
	while (1) {
		camera_update();
		actual_x = get_object_center(color, 0).x;
		printf("%i\n");
		msleep(4000);
		if (actual_x  > desired_x) {
			//GO_RIGHT
		}
		if (actual_x < desired_x) {
			//GO_LEFT
		}
		if (actual_x < desired_x+5 && actual_x > desired_x-5+){
			//STOP
		}
	}
}



#endif
