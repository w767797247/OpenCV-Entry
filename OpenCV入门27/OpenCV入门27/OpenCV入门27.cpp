// OpenCV入门27.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

Mat g_srcImage, g_srcGrayImage, g_dstImage;

Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;

Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;

Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

static void on_Canny(int, void *);
static void on_Sobel(int, void *);
void Scharr();

int main(int argc,char** argv)
{
	system("color 2F");

	g_srcImage = imread("6d148550877909c80e4c6e039ba9aff4.jpg");

	namedWindow("原始图");
	imshow("原始图", g_srcImage);

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);

	namedWindow("Canny");
	namedWindow("Sobel");
	namedWindow("Scharr");

	createTrackbar("参数值", "Canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("参数值", "Sobel", &g_sobelKernelSize, 3, on_Sobel);

	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();

	while ((char(waitKey(1)) != 'q')) {}
    return 0;
}

void on_Canny(int, void *)
{
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));

	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	g_dstImage = Scalar::all(0);

	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	imshow("Canny", g_dstImage);
}
void on_Sobel(int, void *)
{
	Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X);

	Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);

	addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);

	imshow("Sobel", g_dstImage);
}
void Scharr()
{
	Scharr(g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);

	Scharr(g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);

	addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

	imshow("Scharr", g_dstImage);
}