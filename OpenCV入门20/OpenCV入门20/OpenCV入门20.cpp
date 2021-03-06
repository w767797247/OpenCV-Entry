// OpenCV入门20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackNum = 0;

static void on_OpenClose(int, void *);
static void on_ErodeDilate(int, void *);
static void on_TopBlackHat(int, void *);
static void ShowHelpText();

int main()
{
	g_srcImage = imread("IMG_20170416_173321_HDR.jpg");

	namedWindow("原始图",2);
	imshow("原始图", g_srcImage);

	namedWindow("开运算/闭运算", 2);
	namedWindow("腐蚀/膨胀", 2);
	namedWindow("顶帽/黑帽", 2);

	g_nErodeDilateNum = 9;
	g_nOpenCloseNum = 9;
	g_nTopBlackNum = 2;

	createTrackbar("迭代值", "开运算/闭运算", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值", "腐蚀/膨胀", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "顶帽/黑帽", &g_nTopBlackNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);
   
	while (1)
	{
		int c;

		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackNum, 0);

		c = waitKey(0);

		if ((char)c == 'q' || (char)c == 27)
			break;
		if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;
		else if ((char)c == 50)
			g_nElementShape = MORPH_CROSS;
		else if ((char)c == 51)
			g_nElementShape = MORPH_RECT;
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;
	}

	return 0;
}

static void on_OpenClose(int, void *)
{
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 10), 
		Point(Absolute_offset, Absolute_offset));

	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
	imshow("开运算/闭运算", g_dstImage);
}
static void on_ErodeDilate(int, void *)
{
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 10),
		Point(Absolute_offset, Absolute_offset));

	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_ERODE, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_DILATE, element);
	imshow("腐蚀/膨胀", g_dstImage);
}
static void on_TopBlackHat(int, void *)
{
	int offset = g_nTopBlackNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 10),
		Point(Absolute_offset, Absolute_offset));

	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("顶帽/黑帽", g_dstImage);
}