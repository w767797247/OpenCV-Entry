// OpenCV入门14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void *);

int g_nContrstValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

int main()
{
	g_srcImage = imread("图5.13 原始图.jpg");
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~!"); return false; }
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrstValue = 80;
	g_nBrightValue = 80;

	//namedWindow("效果图窗口", 1);

	createTrackbar("对比度：", "效果图窗口", &g_nContrstValue, 300, on_ContrastAndBright);
	createTrackbar("亮度：", "效果图窗口", &g_nBrightValue, 200, on_ContrastAndBright);

	on_ContrastAndBright(g_nContrstValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	while (char(waitKey(1)) != 'q') {}
    return 0;
}

static void on_ContrastAndBright(int, void *)
{
	namedWindow("原始图窗口", 1);

	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>((g_nContrstValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}

	imshow("原始图窗口", g_srcImage);
	imshow("效果图窗口", g_dstImage);
}
