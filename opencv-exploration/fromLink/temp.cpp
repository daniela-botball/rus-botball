
#include "/kovan/archives/rus_camera_interface.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Camera::Device _CAMERA;
VideoCapture* _CAMERA_VIDEO_CAPTURE;
Mat _IMAGE;

int main(int argc, char* argv[]) {
    cout << "starting cpp" << endl;

    rus_camera_open();
    rus_camera_update();

    imshow("testing", _IMAGE);
    waitKey();

    rus_camera_close();

    cout << "ending cpp" << endl;
    return 1;
}

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
    imshow("Camera image", _IMAGE);
    waitKey(5000);
    return 1;
}

