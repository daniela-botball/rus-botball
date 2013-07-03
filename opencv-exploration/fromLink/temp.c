#include <stdio.h>
#include </usr/include/opencv2/opencv.h>

int main() {
    printf("hello\n");

    camera_open(LOW_RES);
    camera_update();
    printf("Area: %i\n", get_object_area(0, 0));

    CvMat* x;
    Mat y;

    return 1;
}
