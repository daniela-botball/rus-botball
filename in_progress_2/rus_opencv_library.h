// RUS C interface to functions, implemented in C++,
// that access OpenCV.

#ifndef _RUS_OPENCV_LIBRARY_H
#define _RUS_OPENCV_LIBRARY_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int CANNY_1, CANNY_2, HOUGH_1, HOUGH_2, HOUGH_3, HOUGH_4;

/*********************************************************************
 * int cv_find_pole(int lines[])
 *   Puts into the given array the XXX lines that may be edges of the pole.
 *   Returns the number of such lines.
 ********************************************************************/

EXTERNC int cv_find_pole(int lines[]);

/*********************************************************************
 * cv_show_image(OpenCV_Options option, int milliseconds_to_show)
 *   Shows, for the given number of milliseconds,
 *   the current image as one of the OpenCV_Options:
 *	RAW_IMAGE, GRAYSCALE, CANNY, HOUGHLINES
 *   Returns the number of lines in the image after HoughLines.
 ********************************************************************/

EXTERNC typedef enum {RAW_IMAGE, GRAYSCALE, CANNY, HOUGHLINES} OpenCV_Options;
EXTERNC int cv_show_image(OpenCV_Options option, int milliseconds_to_show);

#endif
