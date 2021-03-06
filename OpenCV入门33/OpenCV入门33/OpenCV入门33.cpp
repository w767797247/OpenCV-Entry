// OpenCV入门33.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat src, dst;
	src = imread("吾王saber.jpg");

	cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("原始图", src);

	equalizeHist(src, dst);
	imshow("效果图", dst);

	waitKey(0);
    return 0;
}

