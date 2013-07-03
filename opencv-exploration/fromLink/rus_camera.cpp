
#include "rus_camera_interface.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void cv_find_pole();
void show_lines(vector<Vec4i> lines, Mat image);

extern Mat _IMAGE;

void cv_find_pole() {
    Mat gray, edges;
    vector<Vec4i> lines;

    cvtColor(_IMAGE, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 80, 120);
    HoughLinesP(edges, lines, 1, CV_PI/180, 70, 1, 30);

    show_lines(lines, _IMAGE);
}

void show_lines(vector<Vec4i> lines, Mat image) {
	int thickness;
	size_t k;
	Point point1, point2;
	Scalar color;
	Vec4i hough_line;

	thickness = 1; // pixels
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
//	imshow("After Hough", image);
//	waitKey();
}


