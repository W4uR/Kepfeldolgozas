#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include "Edge.h"
#include "Erode.h"

using namespace std;
using namespace cv;



int main() {
	/*
	std::default_random_engine generator;
	std::normal_distribution<float> male_height(186.0f, 20.0f);
	std::normal_distribution<float> male_len(10.0f, 15.0f);
	std::normal_distribution<float> female_height(170.0f, 10.0f);
	std::normal_distribution<float> female_len(45.0f, 30.0f);

	Mat data(30, 2, CV_32F);//30 minta szám - 2 kéaszterszám - mindig float
	// férfiak adatai
	for (int i = 0; i < 15; ++i) {
		data.at<float>(i, 0) = male_height(generator);
		data.at<float>(i, 1) = male_len(generator);
	}
	// nõk adatai
	for (int i = 15; i < 30; ++i) {
		data.at<float>(i, 0) = female_height(generator);
		data.at<float>(i, 1) = female_len(generator);
	}
	TermCriteria term(TermCriteria::MAX_ITER | TermCriteria::EPS, 100, 1.0);
	Mat labels;
	kmeans(data, 2, labels, term, 3, KMEANS_RANDOM_CENTERS);

	Mat canvas(300, 300, CV_8UC3);
	canvas.setTo(255);
	// férfiak adatai
	for (int i = 0; i < 15; ++i) {
		int lbl = labels.at<int>(i);//Melyik klaszterbe került
		int shape = lbl ? MARKER_DIAMOND : MARKER_CROSS;
		drawMarker(canvas, Point(data.at<float>(i, 0), 280 - data.at<float>(i, 1)), Scalar(255, 0, 0), shape,10);
	}
	// nõk adatai
	for (int i = 15; i < 30; ++i) {
		int lbl = labels.at<int>(i);//Melyik klaszterbe került
		int shape = lbl ? MARKER_DIAMOND : MARKER_CROSS;
		drawMarker(canvas, Point(data.at<float>(i, 0), 280 - data.at<float>(i, 1)), Scalar(0, 0, 255), shape,10);
	}
	imshow("result", canvas);
	*/
	/*
	Mat img = imread("dog.jpg");
	Mat imgf,lab;
	img.convertTo(imgf, CV_32FC3, 1 / 255.0);
	cvtColor(imgf, lab, COLOR_BGR2Lab);
	Mat data = lab.reshape(1, img.rows * img.cols);
	cout << data.rows << endl << data.cols << endl;
	TermCriteria term(TermCriteria::MAX_ITER | TermCriteria::EPS, 500, 0.01);
	Mat labels, centers;
	kmeans(data, 2, labels, term, 3, KMEANS_RANDOM_CENTERS,centers);
	Mat centers_f2;
	Mat centers_f = centers.reshape(3, centers.rows);
	cvtColor(centers_f, centers_f2, COLOR_Lab2BGR);
	Mat center_color;
	centers_f2.convertTo(center_color, CV_8UC3, 255);
	cout << center_color << endl;
	Mat labels2 = labels.reshape(1, img.rows);
	Mat result = Mat::zeros(img.size(), CV_8UC3);
	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			int lbl = labels2.at<int>(i, j);
			result.at<Vec3b>(i, j) = center_color.at<Vec3b>(lbl);
		}
	}
	imshow("og", img);
	imshow("img",result);
	*/

	Mat data(18, 3, CV_32F);
	Mat img, bin;
	for (int i = 0; i < 18; i++)
	{
		img = imread("kekszek_vegyes/" + to_string(i + 1) + ".png", IMREAD_GRAYSCALE);
		threshold(img, bin, 100, 255, THRESH_BINARY_INV);
		medianBlur(bin, bin, 5);

		vector<vector<Point>> conts;
		findContours(bin, conts, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		vector<Point> convex_hull;
		cv::convexHull(conts[0], convex_hull);

		double area = contourArea(conts[0]);
		double perim = arcLength(conts[0], 1);

		double convexivity = arcLength(convex_hull, 1) / perim;
		double circularity = area / (perim * perim);

		Moments m = moments(bin, true);
		RotatedRect r = minAreaRect(conts[0]);
		data.at<float>(i, 0) = convexivity;//jellemzo #1
		data.at<float>(i, 1) = circularity;//jellemzo #2
		data.at<float>(i, 2) = r.size.width / r.size.height;//jellemzo #3

	}

	cout << data << endl;

	TermCriteria term(TermCriteria::MAX_ITER | TermCriteria::EPS, 1000, 0.01);
	Mat labels, centers;
	kmeans(data, 3, labels, term, 3, KMEANS_RANDOM_CENTERS, centers);

	for (size_t i = 0; i < 18; i++)
	{
		img = imread("kekszek_vegyes/" + to_string(i + 1) + ".png");
		int lbl = labels.at<int>(i);
		string name = to_string(lbl)+"/"+to_string(i + 1) + ".png";
		imwrite("kekszek_vegyes/"+name, img);
	}

	

	return 0;
}
