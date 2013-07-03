
#include "rus_camera_interface.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Camera::Device _CAMERA;
VideoCapture* _CAMERA_VIDEO_CAPTURE;
Mat _IMAGE;

extern int cv_find_pole();

void rus_camera_open() {
    if (! _CAMERA.isOpen()) {
        _CAMERA.open();
        _CAMERA_VIDEO_CAPTURE = _CAMERA.videoCapture();
    }
}
	
void rus_camera_close() {
    if (_CAMERA.isOpen()) {
        _CAMERA.close();
        _CAMERA_VIDEO_CAPTURE = NULL;
    }
}

int rus_camera_update() {
    bool status;

    if (_CAMERA.isOpen()) {
        status = _CAMERA_VIDEO_CAPTURE->read(_IMAGE);
        return status? 1 : 0;
    } else {
        return false;
    }
}

int find_pole() {
    cv_find_pole();

    return 1;
}

