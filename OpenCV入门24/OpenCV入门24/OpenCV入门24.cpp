// OpenCV入门24.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("切嗣papa.jpg");
	Mat src1 = src.clone();

	namedWindow("原始图", WINDOW_NORMAL);
	imshow("原始图", src);

	Mat dst, edge, gray;
	dst.create(src1.size(), src1.type());
	cvtColor(src1, gray, COLOR_BGR2GRAY);
	blur( gray,edge, Size(3, 3));
	Canny(edge, edge, 10, 100, 3);
	dst = Scalar::all(0);
	src1.copyTo(dst, edge);

	namedWindow("效果图2", WINDOW_NORMAL);
	imshow("效果图2", dst);

	waitKey(0);
    return 0;
}

