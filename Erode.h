#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#pragma once
class Erode
{
public:
	static int ErodeExample() {
		Mat img = imread("erode/galaxy.jpg", IMREAD_GRAYSCALE);
		Mat dest;
		morphologyEx(img, dest, MORPH_TOPHAT, getStructuringElement(MORPH_RECT, Size(5, 5)));
		imshow("source", img);
		imshow("dest", dest);
	}
	static int NoiseReductionExample() {
		Mat img = imread("erode/American_Eskimo_dog.jpg", IMREAD_GRAYSCALE);
		Mat binaris, erodalt_mask, dilatalt_mask;
		threshold(img, binaris, 0, 255, THRESH_BINARY | THRESH_OTSU);
		erode(binaris, erodalt_mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(erodalt_mask, dilatalt_mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		imshow("source", img);
		imshow("bin", binaris);
		imshow("erode", erodalt_mask);
		imshow("dilate", dilatalt_mask);
	}
	static int CheeseExample() {
		Mat img = imread("erode/sajt.png", IMREAD_GRAYSCALE);
		Mat binaris,dilatalt,dest;
		threshold(img, binaris, 250, 255, THRESH_BINARY_INV);
		medianBlur(binaris, binaris, 5);
		dilate(binaris, dilatalt, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
		dest = dilatalt - binaris;
		imshow("korvonal", dest);

		// --- Lyukak eltávolítása
		Mat binaris2;
		copyMakeBorder(binaris, binaris2, 70, 70, 70, 70, BORDER_CONSTANT,0);

		dilate(binaris2, binaris2, getStructuringElement(MORPH_ELLIPSE, Size(64, 64)));
		erode(binaris2, binaris2, getStructuringElement(MORPH_ELLIPSE, Size(64, 64)));
		imshow("no-lyuk", binaris2);

	}

	static int DragonflyExample() {
		Mat img = imread("erode/szitakoto.jpg", IMREAD_GRAYSCALE);
		Mat binaris;
		threshold(img, binaris, 150, 255, THRESH_BINARY_INV);
		erode(binaris, binaris, getStructuringElement(MORPH_ELLIPSE, Size(7, 11)));
		dilate(binaris, binaris, getStructuringElement(MORPH_ELLIPSE, Size(7, 11)));
		Mat subPic = binaris(Rect(img.cols / 3, 0, img.cols - 1 - (img.cols / 3), img.rows));
		cout << countNonZero(subPic) << endl;
		imshow("step1", subPic);
	}
};

