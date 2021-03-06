// OpenCV入门34.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int agrc, char** agrv)
{
	Mat src = imread("IMG_20180627_191846_HDR.jpg");
	imshow("原始图", src);
	
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

	src = src > 119;
	imshow("阈值图", src);

	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, index, color, CV_FILLED, 8, hierarchy);
	}

	imshow("效果图", dst);

	waitKey(0);
}

