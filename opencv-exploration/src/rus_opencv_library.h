// RUS C interface to functions, implemented in C++,
// that access OpenCV.

#ifndef _RUS_OPENCV_LIBRARY_H
#define _RUS_OPENCV_LIBRARY_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void rus_camera_open();
EXTERNC void rus_camera_close();
EXTERNC int rus_camera_update();
EXTERNC int find_pole();

/*********************************************************************
 * cv_find_pole_x()
 *   Returns the x-value of the center of the pole that is nearest
 *   the center of the picture, or -1 if no pole is visible.
 ********************************************************************/
EXTERNC int cv_find_pole_x();

#endif
