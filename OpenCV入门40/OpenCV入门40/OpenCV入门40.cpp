// OpenCV入门40.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始图"
#define WINDOW_NAME2 "图像轮廓"

Mat g_srcImage, g_grayImage;
int g_nThresh = 100;
int g_nMaxThresh = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;

void on_ThreshChange(int, void*);

int main()
{
	system("color 1A");

	g_srcImage = imread("timg.jpg", 1);

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_NORMAL);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
    return 0;
}

void on_ThreshChange(int, void*)
{
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments>mu(g_vContours.size());

	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i], false);
	}
	vector<Point2f>mc(g_vContours.size());

	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int unsigned i = 0; i < g_vContours.size(); i++)
	{	
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
	    drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	namedWindow(WINDOW_NAME2, WINDOW_NORMAL);
	imshow(WINDOW_NAME2, drawing);

	printf("\t 输出内容：面积和轮廓长度\n");
	for (int unsigned i = 0; i < g_vContours.size(); i++)
	{
		printf(">通过m00计算出轮廓[%d]的面积：(M_00)=%.2f \n OpenCV函数计算出的面积=%.2f，长度：%.2f \n\n", i, mu[i].m00,
			contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}