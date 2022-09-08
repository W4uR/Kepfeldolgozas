#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("dog.jpg");
	imshow("kep", img);
	waitKey();

	return 0;
}