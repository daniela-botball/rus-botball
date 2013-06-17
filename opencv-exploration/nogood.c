// Created on Sat June 8 2013

#include <kovan/camera.hpp>

//#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/core/core.hpp>
//#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/core/core_c.h>

//#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/flann/miniflann.hpp>
//#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/contrib/contrib.hpp>
//#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/highgui/highgui.hpp>
/*
#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/imgproc/imgproc.hpp>
#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/core/core.hpp>
#include <C:/Program Files (x86)/KISS Platform 4.0.5/computer/prefix/usr/include/opencv2/core/core.hpp>
*/
int main()
{
	CvMat* x;
	x = cvLoadImageM("pole.jpg", 0);
	
	printf("Hello, World!\n");
	
	camera_open(LOW_RES);
	
	return 0;
}
