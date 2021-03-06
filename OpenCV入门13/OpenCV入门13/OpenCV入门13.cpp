// OpenCV入门13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool MultiChannelBlending();
bool ROI_AddImage();

int main()
{
	system("color 9F");

	if (ROI_AddImage()&& MultiChannelBlending())
	{
		cout << endl << "\n运行成功，得出了需要的图案~!";
	}
	waitKey(0);
    return 0;
}

bool MultiChannelBlending()
{
	Mat logoImage;
	Mat srcImage;
	vector<Mat> channels;
//蓝色通道
	Mat imageBlueChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("psb0ARLVX3L.png");

	if (!logoImage.data) { printf("读取logoImage错误~! \n"); return false; }
	if (!srcImage.data) { printf("读取srcImage错误~! \n"); return false; }

	split(srcImage, channels);

	imageBlueChannel = channels.at(0);

	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, 
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	merge(channels, srcImage);

	namedWindow("<1>动漫原画+logo蓝色通道");
	imshow("<1>动漫原画+logo蓝色通道", srcImage);

//绿色通道
	Mat imageGreenChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("psb0ARLVX3L.png");

	if (!logoImage.data) { printf("读取logoImage错误~! \n"); return false; }
	if (!srcImage.data) { printf("读取srcImage错误~! \n"); return false; }

	split(srcImage, channels);

	imageGreenChannel = channels.at(1);

	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	merge(channels, srcImage);

	namedWindow("<2>动漫原画+logo绿色通道");
	imshow("<2>动漫原画+logo绿色通道", srcImage);

//红色通道
	Mat imageRedChannel;

	logoImage = imread("logo.jpg", 0);
	srcImage = imread("psb0ARLVX3L.png");

	if (!logoImage.data) { printf("读取logoImage错误~! \n"); return false; }
	if (!srcImage.data) { printf("读取srcImage错误~! \n"); return false; }

	split(srcImage, channels);

	imageRedChannel = channels.at(2);

	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	merge(channels, srcImage);

	namedWindow("<3>动漫原画+logo红色通道");
	imshow("<3>动漫原画+logo红色通道", srcImage);

	return true;
}

bool ROI_AddImage()
{
	Mat logoImage = imread("logo.jpg", 1);
	Mat srcImage = imread("psb0ARLVX3L.png");

	if (!logoImage.data) { printf("读取logoImage错误~! \n"); return false; }
	if (!srcImage.data) { printf("读取srcImage错误~! \n"); return false; }

	Mat imageROI = srcImage(Rect(500, 250, logoImage.cols, logoImage.rows));

	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	namedWindow("<0>动漫原画+logo");
	imshow("<0>动漫原画+logo", srcImage);

	return true;
}