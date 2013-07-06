// RUS functions that access OpenCV.
// They are implemented in C++ but with a pure C interface.


#include <opencv2/opencv.hpp>
#include "/kovan/archives/opencv/rus_opencv_library.h"
#include "/kovan/archives/opencv/camera_c_p.hpp"

using namespace cv;
using namespace std;
using namespace Private;

// Prototypes of functions internal to this library:
const Mat& cv_get_image();
vector<Vec4i> cv_find_lines();
void cv_show_lines(vector<Vec4i> lines, Mat image);

// Definitions of functions exposed in the interface
// (see the .h file for their prototypes):

int cv_find_pole(int lines_array[]) {
    vector<Vec4i> lines_vector;
    int k;

    lines_vector = cv_find_lines();

    for (k = 0; k < lines_vector.size(); ++k) {
        lines_array[(4 * k) + 0] = lines_vector[k][0];
        lines_array[(4 * k) + 1] = lines_vector[k][1];
        lines_array[(4 * k) + 2] = lines_vector[k][2];
        lines_array[(4 * k) + 3] = lines_vector[k][3];
    }
    return lines_vector.size();
}

int cv_show_image(OpenCV_Options option, int milliseconds_to_show) {
    Mat image, gray, edges;
    vector<Vec4i> lines;

    image = cv_get_image();
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, CANNY_1, CANNY_2);
    HoughLinesP(edges, lines, 1, CV_PI/HOUGH_1, HOUGH_2, HOUGH_3, HOUGH_4);

    switch (option) {
        case RAW_IMAGE:	{ imshow("Raw image", image); waitKey(milliseconds_to_show); destroyWindow("Raw image"); break; }
        case GRAYSCALE:	{ imshow("Grayscale", gray); waitKey(milliseconds_to_show); destroyWindow("Grayscale"); break; }
        case CANNY:	{ imshow("Canny", edges); waitKey(milliseconds_to_show); destroyWindow("Canny"); break; }
        case HOUGHLINES: { cv_show_lines(lines, image); waitKey(milliseconds_to_show); destroyWindow("HoughLines"); break; }
	default: {}
    }

    return lines.size();
}

// Definitions of functions internal to this library:

const Mat& cv_get_image() {
    return DeviceSingleton::instance()->rawImage();
}

vector<Vec4i> cv_find_lines() {
    Mat image, gray, edges;
    vector<Vec4i> lines;

    image = cv_get_image();
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, CANNY_1, CANNY_2);
    HoughLinesP(edges, lines, 1, CV_PI/HOUGH_1, HOUGH_2, HOUGH_3, HOUGH_4);

    return lines;
}

void cv_show_lines(vector<Vec4i> lines, Mat image) {
	int thickness;
	size_t k;
	Point point1, point2;
	Scalar color;
	Vec4i hough_line;

	thickness = 5; // pixels
	color = CV_RGB(255, 0, 0);

	cout << lines.size() << endl;
	for (k = 0; k < lines.size(); ++k)
	{
		hough_line = lines[k];
		point1 = Point(hough_line[0], hough_line[1]);
		point2 = Point(hough_line[2], hough_line[3]);
		line(image, point1, point2, color, thickness);
		cout << point1 << point2 << endl;
	}
	imshow("HoughLines", image);
}

