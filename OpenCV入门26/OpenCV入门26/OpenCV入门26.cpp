// OpenCV入门26.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>	
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat src,src_gray,dst,abs_dst;

    src = imread("21_1920x1200.jpg");

	imshow("原始图", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	convertScaleAbs(dst, abs_dst);

	imshow("效果图z", abs_dst);
	waitKey(0);
	return 0;
}
