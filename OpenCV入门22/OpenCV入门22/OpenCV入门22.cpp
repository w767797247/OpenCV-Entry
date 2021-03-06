// OpenCV入门22.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"

Mat g_srcImage, g_dstImage, g_tmpImage;

int main()
{
	g_srcImage = imread("IMG_20170807_153822.jpg");

	namedWindow(WINDOW_NAME, WINDOW_NORMAL);
	imshow(WINDOW_NAME, g_srcImage);

	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key = 0;

	while (1)
	{
		key = waitKey(9);

		switch (key)
		{
		case 27:
			return 0;
			break;
		case'q':
			return 0;
			break;
		case 'a':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf(">检测到按键【A】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸*2\n");
			break;
		case'w':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf(">检测到按键【w】被按下，开始进行基于【resize】函数的图片放大：图片尺寸*2\n");
			break;
		case'1':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf(">检测到按键【1】被按下，开始进行基于【resize】函数的图片放大：图片尺寸*2\n");
			break;
		case'3':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf(">检测到按键【3】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸*2\n");
			break;
		case'd':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf(">检测到按键【d】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n");
			break;
		case's':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf(">检测到按键【s】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break;
		case'2':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2),(0,0),(0,0),2);
			printf(">检测到按键【2】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break;
		case'4':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf(">检测到按键【4】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n");
			break;
		}
		imshow(WINDOW_NAME, g_dstImage);
		g_tmpImage = g_dstImage;
	}
    return 0;
}

