#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
#pragma once
class Edge
{
	public:
	static int CircleExample() {
		Mat img = imread("edge/go2.png");
		imshow("img", img);

		Mat gray;
		cvtColor(img, gray, COLOR_BGR2GRAY);

		vector<Vec3f> circles;
		HoughCircles(gray, circles, HOUGH_GRADIENT, 2, 10, 80, 50, 22, 27);
		for (Vec3f c : circles) {

			circle(img, Point(c[0], c[1]), c[2], gray.at<uchar>(Point(c[0], c[1])) < 128 ? Scalar(0, 255, 0) : Scalar(255, 0, 0), 2);
		}
		imshow("img", img);

	}
};

