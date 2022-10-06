#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



using namespace std;
using namespace cv;

void vilagosit1(Mat source) { //Nem kell referencia mert a "Mat" csak egy fejléc az adatrész csak egy mutató
	source += 50;
}
void vilagosit1(Mat source, Mat& dest) {
	dest = source + 50;
}

void invertalas(Mat source,Mat& dest) {
	dest = 255 - source;
}

void narancsMasolo(const cv::Mat src, cv::Mat& dest) {

	//Vec3b orange_ish = fg.at<Vec3b>(fg.rows/2, fg.cols/2);
	Mat mask;
	inRange(src, Scalar(0, 0, 150), Scalar(200, 200, 255), mask);
	src.copyTo(dest, mask);
	/*
	for (int i = 0; i < fg.rows; i++)
	{
		for (int j = 0; j < fg.cols; j++)
		{
			Vec3b c = fg.at<Vec3b>(i, j);
			if (c[2] > c[1] && c[2] > c[0])
			{
				bg.at<Vec3b>(i, j) = c;
			}
		}
	}
	*/

}

void eloterMasolo(const cv::Mat fg, cv::Mat& bg) {
	resize(bg, bg, fg.size());
	Vec3b w{ 255,255,255 };
	for (int i = 0; i < fg.rows; i++)
	{
		for (int j = 0; j < fg.cols; j++)
		{
			Vec3b c = fg.at<Vec3b>(i, j);
			if (c!= w) // Ez biza nagyon sziguru
			{
				bg.at<Vec3b>(i, j) = c;
			}
		}
	}
}

void createHisto(const Mat img, Mat& hiszto) {
	//a hiszto az eredmeny, float típusú elemeket tartalmaz majd
	vector<Mat> kepek;
	kepek.push_back(img); // egy képet használunk
	vector<int> csatornak;
	csatornak.push_back(0); //a képnek a 0. csatornáját használjuk
	vector<int> hiszto_meretek;
	hiszto_meretek.push_back(256); //szürkeárnyalatok száma
	vector<float> hiszto_tartomanyok;
	hiszto_tartomanyok.push_back(0.0f); //hol kezdõdik a tartomány
	hiszto_tartomanyok.push_back(255.f); //meddig tart
	//accumlate: marad false (nullázza a hisztogrammot)
	calcHist(kepek, csatornak, noArray(), hiszto, hiszto_meretek,
		hiszto_tartomanyok, false);
}

int calc_th_value(const Mat src, float ratio = 0.1f) {
	int n_fg = src.rows * src.cols * ratio;
	Mat hist;
	createHisto(src, hist);
	int s = 0;
	for (int th = 0; th < 256; th++)
	{
		s += hist.at<float>(th);//CV_32F a típus
		if (s >= n_fg)
		{
			return th;
		}
	}
	return 255; //Nem szabadna ide eljutni
}



int main() {
	/*
	Mat img = imread("dog.jpg",cv::IMREAD_UNCHANGED);

	cout << "sor: " << img.rows << "   oszlop:" << img.cols << endl;

	Mat fekete = Mat::zeros(img.rows, img.cols, CV_8UC1);

	int t = img.type();
	if (t == CV_8UC1)
	{
		cout << "8bit szürkeskála" << endl;
	}
	else if (t == CV_8UC3) {
		cout << "24bit RGB";
	}
	else {
		cout << "egyéb";
	}
	imshow("kep", fekete);
	imshow("kep1", img);
	*/
	/*
	Mat img = imread("dog.jpg", cv::IMREAD_UNCHANGED);
	Mat dest;
	if (img.empty()) {
		cout << "Where pciture";
		exit(1);
	}
	invertalas(img,dest);
	imshow("kep1", img);
	imshow("kep2", dest);
	*/
	/*
	Mat h = imread("field.jpg", cv::IMREAD_UNCHANGED);
	Mat f = imread("boulder.jpg", cv::IMREAD_UNCHANGED);
	Mat h_resized;
	
	resize(h, h_resized, f.size());
	double a = 0.5;
	Mat final = a * h_resized + (1 - a) * f;
	
	imshow("hatter", h);
	imshow("eloter", f);
	imshow("eredmeny", final);
	*/
	/*
	Mat_<Vec3b> m(2, 3); //egy 3 csatornás kép készítése

	m(0, 0) = Vec3b(0, 0, 255);
	m(0, 1) = Vec3b(0, 255, 0);
	m(0, 2) = Vec3b(255, 0, 0);

	m(1, 0) = Vec3b(0, 0, 0);
	m(1, 1) = Vec3b(39, 127, 255);
	m(1, 2) = Vec3b(0, 255, 255);


	namedWindow("sample", WINDOW_NORMAL); //átméretezhetõ ablak
	resizeWindow("sample", 120, 80); //nagyítás
	imshow("sample", m); //megjelenítés
	
	Mat hatter = imread("background.jpg", cv::IMREAD_UNCHANGED);
	Mat eloter = imread("kurama.jpg", cv::IMREAD_UNCHANGED);

	eloterMasolo(eloter, hatter);
	Mat narancs = imread("orange1.jpg", cv::IMREAD_UNCHANGED);
	Mat fekete = Mat::zeros(narancs.size(), CV_8UC3);
	narancsMasolo(narancs, fekete);

	imshow("kep", fekete);
	*/

	/*
	Mat img, dest,blured;
	img = imread("threshold/madar.jpg", cv::IMREAD_COLOR);
	vector<Mat> chs;
	split(img, chs);// Csatornákra bontás
	//imshow("R", chs[2]);
	//imshow("G", chs[1]);
	//imshow("B", chs[0]);
	Mat blueMask;
	threshold(chs[0], blueMask, 120, 255, THRESH_BINARY);
	imshow("mask", blueMask);
	img.copyTo(dest, blueMask);
	imshow("madar", dest);
	//cout << threshold(img, dest, 110, 255, THRESH_TOZERO);
	//medianBlur(dest, blured, 3);
	//imshow("kutya", img);
	//imshow("csak kutya", dest);
	*/
	/*
	Mat img = imread("threshold/gray_buttons.jpg", IMREAD_GRAYSCALE);
	Mat mask, dest;
	inRange(img, 165, 213, mask);
	medianBlur(mask, mask, 7);
	img.copyTo(dest, mask);
	imshow("gomb1", img);
	imshow("gomb2", dest);
	*/
	/* VIDEO PALYER
	VideoCapture cap;
	cap.open("threshold/sas.avi");
	if (!cap.isOpened())
	{
		cout << "Nem nyithato meg!" << endl;
		exit(-1);
	}

	Mat img,gray,mask;
	while (1)
	{
		cap >> img;
		if (img.empty())
		{
			break;
		}
		cvtColor(img, gray, COLOR_BGR2GRAY);
		inRange(gray, 100, 155, mask);
		medianBlur(mask, mask, 7);
		img.setTo(0, mask);

		imshow("video", img);
		waitKey(33);
	}
	*/
	/* KÜSZÖBKERESÉS
	Mat img = imread("threshold/sejtek.png", IMREAD_GRAYSCALE);
	Mat dest;
	int x = 0, y = 0;
	for (int th = 20; th < 245; th+=20)
	{
		threshold(img, dest, th, 255, THRESH_BINARY_INV);
		string name = "img_" + to_string(th);
		imshow(name, dest);
		namedWindow(name, WINDOW_NORMAL);
		moveWindow(name, x, y);
		x += img.cols / 2;
		if (x > 1000) {
			y += img.rows / 2;
			x = 0;
		}
	}
	*/
	/*
	Mat img = imread("threshold/scanned3.png", IMREAD_GRAYSCALE);
	Mat dest;
	
	int th = calc_th_value(img, 0.1f);
	threshold(img, dest, th, 255, THRESH_BINARY_INV);
	imshow("szoveg", dest);
	*/

	//ADAPTÍV KÜSZÖBÖLÉS
	Mat dest, img = imread("threshold/zh.jpg",IMREAD_GRAYSCALE);
	imshow("zh", img);
	int sugar= 20,C=0;
	createTrackbar("sugar", "zh", &sugar, 25);
	createTrackbar("C", "zh", &C, 50);
	int q, meret;
	while ((q=waitKey(1))!='q')
	{
		meret = max(2 * sugar + 1, 3);
		adaptiveThreshold(img, dest, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, meret, C-25);
		imshow("zh",dest);
	}
	waitKey(0);

	return 0;
}