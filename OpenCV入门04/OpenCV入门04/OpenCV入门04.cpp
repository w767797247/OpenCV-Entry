// OpenCV入门04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	Mat image0 = imread("945d48f764e49fad1909b1f3b108ed56.jpg", 2 | 4);
	Mat image1 = imread("945d48f764e49fad1909b1f3b108ed56.jpg", 0);
	Mat image2 = imread("945d48f764e49fad1909b1f3b108ed56.jpg", 199);
	imshow("[无损图]", image0);
	imshow("[灰度图]", image1);
	imshow("[色彩图]", image2);
	waitKey(0);
	return 0;
}

