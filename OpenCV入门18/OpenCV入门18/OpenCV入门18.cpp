// OpenCV入门18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6;
int g_nMeanBlurValue = 10;
int g_nGaussianBlurValue = 6;
int g_nMedianBlurValue = 10;
int g_nBilateralFilterValue = 10;

static void on_BoxFilter(int, void *);
static void on_MeanBlur(int, void *);
static void on_GaussianBlur(int, void *);
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void *);

int main()
{
	system("color5E");

	g_srcImage = imread("瑜哥.jpg", 1);
	if (!g_srcImage.data) { printf("读取srcImage错误~!\n"); return false; }

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	namedWindow("【<0>原图】",CV_WINDOW_NORMAL);
	imshow("【<0>原图】", g_srcImage);

	namedWindow("【<1>方框滤波】", CV_WINDOW_NORMAL);
	createTrackbar("内核值：", "【<1>方框滤波】", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	namedWindow("【<2>均值滤波】", CV_WINDOW_NORMAL);
	createTrackbar("内核值：", "【<2>均值滤波】", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	namedWindow("【<3>高斯滤波】", CV_WINDOW_NORMAL);
	createTrackbar("内核值：", "【<3>高斯滤波】", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	namedWindow("【<4>中值滤波】", CV_WINDOW_NORMAL);
	createTrackbar("内核值：", "【<4>中值滤波】", &g_nMedianBlurValue, 40, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	namedWindow("【<5>双边滤波】", CV_WINDOW_NORMAL);
	createTrackbar("内核值：", "【<5>双边滤波】", &g_nBilateralFilterValue, 40, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);

	cout << endl << "\t,请调整滚动条观察图像效果~\n\n" << "\t按下“q”键时，程序退出~!\n";

	while(char(waitKey(1)) != 'q') {}
	return 0;
}

static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("【<1>方框滤波】", g_dstImage1);
}
static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1),Point(-1,-1));
	imshow("【<2>均值滤波】", g_dstImage2);
}
static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue*2 + 1, g_nGaussianBlurValue*2 + 1),0,0);
	imshow("【<3>高斯滤波】", g_dstImage3);
}
static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue * 2 + 1);
	imshow("【<4>中值滤波】", g_dstImage4);
}
static void on_BilateralFilter(int, void *)
{
	bilateralFilter(g_srcImage, g_dstImage5, g_nMedianBlurValue, g_nMedianBlurValue * 2 , g_nMedianBlurValue/2);
	imshow("【<5>双边滤波】", g_dstImage5);
}