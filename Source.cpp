#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Edge.h"
#include "Erode.h"

using namespace std;
using namespace cv;




int main() {
	
	//Edge::CircleExample();
	//Erode::ErodeExample();
	//Erode::NoiseReductionExample();
	//Erode::CheeseExample();
	Erode::DragonflyExample();
	waitKey(0);

	return 0;
}