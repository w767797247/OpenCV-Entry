// OpenCV入门01.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("psb202GW0Y2.png");
	imshow("[原始图]", srcImage);
	Mat edge,grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	blur( grayImage, edge, Size(3,3));
	Canny(edge, edge, 3, 9, 3);
	imshow("[效果图]", edge);

	waitKey(0);
	return 0;
}



