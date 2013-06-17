// Created on Sat June 8 2013

#include <iostream>
#include <kovan/camera.hpp>


using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello, World!" << endl;
	
	Camera::Device camera;
	camera.open();
	// Already opened, no need to do anything else.
	cv::VideoCapture *cap = camera.videoCapture();
	
	camera.close();
	return 0;
}
