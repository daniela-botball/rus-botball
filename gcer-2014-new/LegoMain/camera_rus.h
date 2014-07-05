#ifndef _CAMERA_RUS_H_
#define _CAMERA_RUS_H_

#define CAMERA_MAX_X 159
#define CAMERA_MAX_Y 119

#define MSECONDS_PER_DISPLAY 500
#define NEARLY_TOUCHING 20

void initialize_camera();
int has_big_enough_blob(int colors[], int minimum_sizes[], int number_of_colors_to_check);

rectangle get_pile_bbox(int colors[], int number_of_colors_to_check);
rectangle biggest_blob(int colors[], int number_of_colors_to_check);
rectangle box_containing(rectangle r1, rectangle r2);
int almost_intersects(rectangle r1, rectangle r2, int nearly_touching);
	
void show_blobs(int colors[], int number_of_colors_to_show);
void show_blob_numbers(int color_model, int blob, int line);

rectangle transform_bbox1(rectangle bbox);
rectangle transform_bbox2(rectangle bbox);

#endif
