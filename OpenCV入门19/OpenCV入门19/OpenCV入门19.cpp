// OpenCV入门19.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumer = 0;
int g_nStructElementSize = 3;

void Process();
void on_TrackbarNumChange(int, void *);
void on_ElementSizeChange(int, void *);

int main()
{
	system("color5E");
	g_srcImage = imread("IMG_20180621_121917_HDR.jpg");

	namedWindow("原图",WINDOW_NORMAL);
	imshow("原图", g_srcImage);

	namedWindow("效果图", WINDOW_NORMAL);
	
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("效果图", g_dstImage);

	createTrackbar("腐蚀/膨胀", "效果图",&g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "效果图", &g_nStructElementSize, 21, on_ElementSizeChange);

	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), 
		Point(g_nStructElementSize, g_nStructElementSize));

	if (g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("效果图", g_dstImage);
}

void on_TrackbarNumChange(int, void *)
{
	Process();
}
void on_ElementSizeChange(int, void *)
{
	Process();
}