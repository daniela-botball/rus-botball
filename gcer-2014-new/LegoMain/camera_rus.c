#include "camera_rus.h"
#include "utilities.h"
#include "ui.h"
#include "tournamentFunctions.h"

// Using the following variable because camera_close does not work correctly.
//   -- So we keep track of whether the camera is open ourselves,
//      to avoid re-opening it (which causes an error).
int _CAMERA_IS_OPEN = FALSE;

void initialize_camera() {
	int i;
	int number_of_times_to_update = 20; // FIX ME
	int result;
	
	printf("Intializing camera.  If this hangs,\n");
	printf("check that the camera is plugged in.\n");
	
	printf("%i\n", LOW_RES);
	if (! _CAMERA_IS_OPEN) {
		_CAMERA_IS_OPEN = TRUE;
		while (camera_open() == 0) {} // Keep trying until it succeeds.void go_to_pom_pile()
	}
	
	for (i = 0; i < number_of_times_to_update; i++) {
		result = camera_update();
		printf("Result of update %3i is %i\n", i, result);
	}
	
	while (camera_update() == 0) { // Keep trying until it succeeds.
		printf("Initializing: camera update fails.\n");
	}
}

int has_big_enough_blob(int colors[], int minimum_sizes[], int number_of_colors_to_check) {
	// Determines whether there is a blob of any one of the given colors
	// whose area is at least the corresponding minimum_size.
	// Returns the first such color found, or -1 if no color has a big enough blob.
	// Precondition: A picture has been taken. (This does NOT take a picture.)
	
	int k;
	int area;
	rectangle bbox;
	
	printf("Color/area/ulx/uly/lrx/lry:\n");
	for (k = 0; k < number_of_colors_to_check; ++k) {
		printf("%1i", k);
		if (get_object_count(colors[k]) <= 0) {
			printf("  No %i object\n", k);
			} else {
			area = get_object_area(colors[k], 0);
			bbox = transform_bbox1(get_object_bbox(colors[k], 0));
			printf(" %5i %3i %3i %3i %3i", area, bbox.ulx, bbox.uly, bbox.ulx + bbox.width, bbox.uly + bbox.height);
			
			if (area < minimum_sizes[k]) {
				printf(" TOO SMALL\n");
				} else {
				printf(" FOUND big enough %i!\n", colors[k]);
				return colors[k];
			}
		}
	}
	return -1;
}

void show_blobs(int colors[], int number_of_colors_to_show) {
	// Repeatedly shows stats on all the blobs of the requested colors.
	// Does as many blobs (starting with the biggest) as the screen permits (roughly).
	int line;
	int j, k;
	int lines_to_use = DISPLAY_PRINTF_LINES_ON_LINK - 1; // One for header.
	float s;
	initialize_camera();
	
	display_clear();
	display_printf(0, 0, "Col Center Ctroid Area Conf UL_x_y LR_x_y");
	
	// FIXME: Add code that allows one to pause/change the refresh rate.
	// FIXME: Use ALL lines if ALL blobs will fit (avoiding multiple "no blobs").
	// FIXME: Show something meaningful if a requested color model does not exist.
	s = seconds();
	while (1) {
		camera_update();
		if (seconds() - s >= SECONDS_PER_DISPLAY) {
			s = seconds();
			line = 1;
			for (k = 0; k < number_of_colors_to_show; ++k) {
				for (j = 0; j <  lines_to_use / number_of_colors_to_show; ++j) {
					show_blob_numbers(colors[k], j, line);
					++ line;
				}
			}
		}
	}
}

// Displays all the statistics available in the KISS library about
// the given blob in the given color model.
// Displays the data at the given line number.
void show_blob_numbers(int color_model, int blob, int line) {
	if (get_object_count(color_model) < blob + 1) {
		display_printf(0, line, "%1i %-40s", color_model, "No more blobs...........................");
		} else {
		display_printf(0, line, "%1i %3i %3i %3i %3i %4i %3.1f %3i %3i %3i %3i",
		color_model,
		get_object_center(color_model, blob).x,
		get_object_center(color_model, blob).y,
		get_object_centroid(color_model, blob).x,
		get_object_centroid(color_model, blob).y,
		get_object_area(color_model, blob),
		get_object_confidence(color_model, blob),
		get_object_bbox(color_model, blob).ulx,
		get_object_bbox(color_model, blob).uly,
		get_object_bbox(color_model, blob).ulx + get_object_bbox(color_model, blob).width,
		get_object_bbox(color_model, blob).uly + get_object_bbox(color_model, blob).height);
	}
}


rectangle get_pile_bbox(int colors[], int number_of_colors_to_check) {
	// Tries to return the bbox around a "pile" of the given colors.
	// Returns a rectangle.
	// Preconditions: A picture has been taken. (This does NOT take a picture.)
	//                There is exactly one pile.
	//
	// FIXME: This implementation is a lousy one:
	//        1. Identify the biggest blob (among all the colors).
	//           Put it into the result.
	//        2. Add to the result any blobs that intersect,
	//           or almost intersect, the current result.
	//        3. Repeat step 2 until no blobs are added at that step.
	
	int k, j;
	int old = 0;
	int count;
	int still_adding_boxes;
	rectangle pile_bbox, this_bbox;
	BLOB blob;
	
	blob = biggest_blob(colors, number_of_colors_to_check);
	pile_bbox = get_object_bbox(blob.color, blob.index);
	printf("(%3i, %3i), %3i, %3i\n", pile_bbox.ulx, pile_bbox.uly, pile_bbox.width, pile_bbox.height);
	//press_a_to_continue();
	while (1) {
		count = 0;
		for (k = 0; k < number_of_colors_to_check; ++k) {
			for (j = 0; j < get_object_count(colors[k]); ++j) {
				this_bbox = get_object_bbox(colors[k], j);
				if (almost_intersects(this_bbox, pile_bbox, NEARLY_TOUCHING)) {
					printf("Adding box - j,k: %i, %i\n", j, k);
					pile_bbox = box_containing(pile_bbox, this_bbox);
					count++;
				}
			}
		}
		//press_a_to_continue();
		if (old == count) {
			break;
		} else {
			old = count;
		}
	}
	printf("(%3i, %3i), %3i, %3i\n", pile_bbox.ulx, pile_bbox.uly, pile_bbox.width, pile_bbox.height);
	return pile_bbox;	
}

BLOB biggest_blob(int colors[], int number_of_colors_to_check) {
	// Returns the biggest blob among all the given colors. Color of -1 means no blob
	int k;
	int biggest_area = -1;
	BLOB biggest_blob = {-1, 0};
	
	for (k = 0; k < number_of_colors_to_check; ++k) {
		if (get_object_count(colors[k]) > 0 && get_object_area(colors[k], 0) > biggest_area) {
			biggest_area = get_object_area(colors[k], 0);
			biggest_blob.color = k;
		}
	}
	
	return biggest_blob;
}

int almost_intersects(rectangle r1, rectangle r2, int nearly_touching) {
	// Returns TRUE if r1 and r2 intersect,
	// or come within NEARLY_TOUCHING of intersecting.
	int top1, top2, bottom1, bottom2;
	int left1, left2, right1, right2;
	
	top1 = r1.uly;
	top2 = r2.uly;
	bottom1 = r1.uly - r1.height;
	bottom2 = r2.uly - r2.height;
	
	if (top1 < bottom2 - nearly_touching || top2 < bottom1 - nearly_touching) {
		return FALSE;
	}
	
	left1 = r1.ulx;
	left2 = r2.ulx;
	right1 = r1.ulx + r1.width;
	right2 = r2.ulx + r2.width;
	
	if (right1 < left2 - nearly_touching || right2 < left1 - nearly_touching) {
		return FALSE;
	}
	
	return TRUE;
}

rectangle box_containing(rectangle r1, rectangle r2) {
	// Returns the smallest rectangle that contains both r1 and r2.
	int top1, top2, bottom1, bottom2;
	int left1, left2, right1, right2;
	int top, bottom, left, right;
	rectangle r;
	
	top1 = r1.uly;
	top2 = r2.uly;
	bottom1 = r1.uly - r1.height;
	bottom2 = r2.uly - r2.height;
	
	left1 = r1.ulx;
	left2 = r2.ulx;
	right1 = r1.ulx + r1.width;
	right2 = r2.ulx + r2.width;
	
	top = top1 > top2 ? top1 : top2;
	bottom = bottom1 < bottom2 ? bottom1 : bottom2;
	left = left1 < left2 ? left1 : left2;
	right = right1 > right2 ? right1 : right2;
	
	r.ulx = left;
	r.uly = top;
	r.width = right - left;
	r.height = top - bottom;
	
	return r;
}

// FIXME: Choose better names for the following functions.

rectangle transform_bbox1(rectangle bbox) {
	// Camera is "face up and forward" in the typical way.
	// But we want (0,0) in LOWER left corner.
	rectangle new_bbox;
	
	new_bbox.height = bbox.height;
	new_bbox.width = bbox.width;
	new_bbox.ulx = bbox.ulx;
	new_bbox.uly = CAMERA_MAX_Y - bbox.uly;
	
	return new_bbox;
}

rectangle transform_bbox2(rectangle bbox) {
	// Camera is turned on its side.
	// As if turned left 90 degrees from "face up and forward".
	
	rectangle new_bbox;
	
	new_bbox.height = bbox.width;
	new_bbox.width = bbox.height;
	new_bbox.uly = bbox.ulx;
	new_bbox.ulx = bbox.uly;
	
	return new_bbox;
}
